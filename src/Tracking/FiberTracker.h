#ifndef FIBERTRACKER_H
#define FIBERTRACKER_H
#include "vtkVector.h"
#include "vtkVectorDot.h"
#include "../TensorComputations/TensorComputations.h"
#include "vtkPointLocator.h"

class FiberTracker
{
public:
	FiberTracker();
	~FiberTracker();
	void Init();
	void Update(vtkVector3d boxWidgetPos, vtkVector3d boxWidgetExtents, int seedPointsPerAxis);
};

#endif