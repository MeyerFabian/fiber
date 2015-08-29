#ifndef FIBER_H
#define FIBER_H
#include "vtkSmartPointer.h"
#include "vtkRenderer.h"
#include "vtkRenderWindowInteractor.h"
#include <qobject.h>
#include "vtkPoints.h"
#include <vector>
#include "vtkPolyLine.h"
#include "vtkCellArray.h"
#include "vtkPolyData.h"
#include "vtkPolyDataMapper.h"
class Fiber : public QObject 
{
	Q_OBJECT
public:
	Fiber();
	~Fiber();


public:    
	void activate(vtkSmartPointer<vtkRenderer> renderer, vtkSmartPointer<vtkRenderWindowInteractor> rendint);
	void deactivate(vtkSmartPointer<vtkRenderer> renderer);
public slots:
void update(std::vector<vtkSmartPointer<vtkPoints> >*);
private:
	std::vector< vtkSmartPointer<vtkActor>> actors;
	
};

#endif // FIBER_H
