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
	Fiber(vtkSmartPointer<vtkRenderer> renderer);
	~Fiber();


public:    
	void activate();
	void deactivate();
public slots:
void update(std::vector<vtkSmartPointer<vtkPoints> >*);
private:
	std::vector< vtkSmartPointer<vtkActor>> actors;
	vtkSmartPointer<vtkRenderer> renderer;
	
};

#endif // FIBER_H
