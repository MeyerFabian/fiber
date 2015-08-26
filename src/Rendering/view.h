#ifndef VIEW_H
#define VIEW_H
#include "vtkRenderer.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSmartPointer.h"

class View
{
public:
    View();
    ~View();
    virtual void activate(vtkSmartPointer<vtkRenderer> renderer, vtkSmartPointer<vtkRenderWindowInteractor> rendint){}
	virtual void deactivate(vtkSmartPointer<vtkRenderer> renderer){}
};

#endif // VIEW_H
