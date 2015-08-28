#include "vtkVector.h"
#include "vtkVectorDot.h"
#include "TensorComputations/TensorComputations.h"
#include "vtkPointLocator.h"

#pragma once
class FiberTracker
{
public:
	FiberTracker();
	~FiberTracker();
	void Init();
	void Update(vtkVector3d boxWidgetPos, vtkVector3d boxWidgetExtents, int seedPointsPerAxis);
};

