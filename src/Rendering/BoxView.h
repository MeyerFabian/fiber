/*	BoxView.h
*
*		Adds a BoxWidget which holds a volume in it. The Widget can be used to easily 
*		clip the volume to allow better visibility when unnecessary information are clipped out.
*	
*	Fabian
*/
#ifndef BOXVIEW_H
#define BOXVIEW_H
#include "vtkSmartPointer.h"
#include "vtkImageResample.h"
#include "vtkRenderer.h"
#include "vtkBoxWidget.h"
#include "vtkProperty.h"
#include "vtkRenderWindowInteractor.h"
#include "view.h"
#include "vtkCommand.h"
#include "vtkSmartVolumeMapper.h"
#include "vtkPlanes.h"
#include "vtkAlgorithmOutput.h"
#include "vtkProp.h"

class BoxView : public View
{
public:
    BoxView(vtkSmartPointer<vtkAlgorithmOutput> alg,vtkSmartPointer<vtkSmartVolumeMapper> mapper, vtkSmartPointer<vtkProp> prop);
    ~BoxView();


protected:
    vtkSmartPointer<vtkBoxWidget> box = vtkSmartPointer<vtkBoxWidget>::New();
    void activate(vtkSmartPointer<vtkRenderer> renderer, vtkSmartPointer<vtkRenderWindowInteractor> rendint);
	void deactivate(vtkSmartPointer<vtkRenderer> renderer);
private:
    vtkSmartPointer<vtkProp> prop;

};

#endif // BOXVIEW_H
