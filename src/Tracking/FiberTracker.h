#ifndef FIBERTRACKER_H
#define FIBERTRACKER_H
#include "vtkVector.h"
#include "vtkVectorDot.h"
#include "../TensorComputations/TensorComputations.h"
#include "vtkPointLocator.h"

class FiberTracker
{
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
};

#endif