/*	ImagePlaneView.h
*
*		Adds 3 ImagePlaneWidgets that can be dragged around the volume and are restricted to it.
*		The Widgets cannot be rotated, which is desirable:
*		Every Plane is exactly parallel to two axis at any time.
*		The Slices are displayed on the ImagePlaneWidget and allow to orientate the fiber in the volume.
*	
*		Fabian
*/
#ifndef IMAGEPLANEVIEW_H
#define IMAGEPLANEVIEW_H
#include "vtkSmartPointer.h"
#include "vtkAlgorithmOutput.h"
#include "vtkRenderer.h"
#include "vtkImagePlaneWidget.h"
#include "vtkProperty.h"
#include "vtkRenderWindowInteractor.h"
#include "view.h"

class ImagePlaneView : public View
{
public:
    ImagePlaneView(vtkSmartPointer<vtkAlgorithmOutput> alg, int dim[3]);
    ~ImagePlaneView();

protected:
    vtkSmartPointer<vtkImagePlaneWidget> iplane[3];
    const int length = 3;
    void activate(vtkSmartPointer<vtkRenderer> renderer, vtkSmartPointer<vtkRenderWindowInteractor> rendint);
	void deactivate(vtkSmartPointer<vtkRenderer> renderer);


};

#endif // IMAGEPLANEVIEW_H
