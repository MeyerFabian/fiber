/*	FiberTracker.h
*
*		The FiberTracker performs the actual tracking of the fibers in the NIFTI dataset.
*		To do so, the FiberTracker gets the pointer to the dataset from the QVTKWrapper.
*		Several parameters can be set by the user such as stepSize, seedPointsPerAxis etc.
*		For the computation of the tracking formula, requests are sent to the TensorComputations class,
*		which sends back the local tensor and eigenvectors.
*		The final points of the fiberline are stored in a vtkPoints array so that they can be rendered.
*		These vtkPoints arrays are stored in a fiberlines array, because more than one fiberline at a time
*		should be renderable.
*
*	Valentin
*/

#ifndef FIBERTRACKER_H
#define FIBERTRACKER_H
#include "vtkVector.h"
#include "vtkVectorDot.h"
#include "../TensorComputations/TensorComputations.h"
#include "vtkPointLocator.h"
#include <qobject.h>
#include "vtkPoints.h"
#include <vector>

class FiberTracker : public QObject
{
	Q_OBJECT
public:
	FiberTracker(vtkSmartPointer<vtkImageReader2> imgreader);
	~FiberTracker();
	void Init();
	void Update(vtkVector3d boxWidgetPos, vtkVector3d boxWidgetExtents, int seedPointsPerAxis);
	double g;
	double stepSize;
protected:
	vtkSmartPointer<vtkImageReader2> reader;
private:
	double f;
	void TrackFiber(vtkVector3d startPoint, int fiberLineNr);
signals:
	void updateFibers(std::vector<vtkSmartPointer<vtkPoints> >* fiberlines);
private:
	std::vector<vtkSmartPointer<vtkPoints> >* fiberlines;
	vtkSmartPointer<vtkPointLocator> pointLocator;
	TensorComputations* tensorComp;
	vtkVector3d currentPos;
	vtkVector3d currentDir;	//= next step direction = incoming direction = V_n-1
	vtkVector3d v_n;
	vtkVector3d v_nPlus1;
};

#endif