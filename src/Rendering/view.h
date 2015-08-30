/*	View.h
*
*		Used for Abstraction between different views, right now ImagePlaneView.h
*		and BoxView.h inherit it: More Views are possible. 
*		The class is created to make the process of adding other views easier.
*
*	Fabian
*/
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
