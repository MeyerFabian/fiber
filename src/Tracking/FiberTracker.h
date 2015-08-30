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
protected:
	vtkSmartPointer<vtkImageReader2> reader;
private:
	double stepSize;
	double f;
	double g;
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