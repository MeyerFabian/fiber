#ifndef FIBER_H
#define FIBER_H
#include "vtkSmartPointer.h"
#include "vtkRenderer.h"
#include "vtkRenderWindowInteractor.h"
#include <qobject.h>
#include "vtkPoints.h"
#include <vector>

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

	
};

#endif // FIBER_H
