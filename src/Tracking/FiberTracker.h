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
<<<<<<< HEAD
protected:
	vtkSmartPointer<vtkImageReader2> reader;
private:
	double stepSize;
	double f;
	double g;
=======
signals:
	void updateFibers(std::vector<vtkSmartPointer<vtkPoints> >* fiberlines);
private:
	std::vector<vtkSmartPointer<vtkPoints> >* fiberlines;
>>>>>>> 3a1a47ad5c59b1f47a88fc09c527738885eaef38
};

#endif