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
    virtual void setActive(vtkSmartPointer<vtkRenderer> renderer, vtkSmartPointer<vtkRenderWindowInteractor> rendint){}
};

#endif // VIEW_H
