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
	FiberTracker();
	~FiberTracker();
	void Init();
	void Update(vtkVector3d boxWidgetPos, vtkVector3d boxWidgetExtents, int seedPointsPerAxis);
signals:
	void updateFibers(std::vector<vtkSmartPointer<vtkPoints> >* fiberlines);
private:
	std::vector<vtkSmartPointer<vtkPoints> >* fiberlines;
};

#endif