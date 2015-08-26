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
    ImagePlaneView(vtkSmartPointer<vtkAlgorithmOutput> alg);
    ~ImagePlaneView();
    /*
    vtkSmartPointer<vtkRenderWindowInteractor> GetRenderWindowInteractor();
    vtkSmartPointer<vtkAlgorithmOutput> GetAlgorithmOutput();
    vtkSmartPointer<vtkRenderer> GetRenderer();
    */

protected:
    vtkSmartPointer<vtkImagePlaneWidget> iplane[3];
    const int length = 3;
    void activate(vtkSmartPointer<vtkRenderer> renderer, vtkSmartPointer<vtkRenderWindowInteractor> rendint);
	void deactivate(vtkSmartPointer<vtkRenderer> renderer);
	/*
    vtkSmartPointer<vtkRenderWindowInteractor> rwi;
    vtkSmartPointer<vtkAlgorithmOutput> ao;
    vtkSmartPointer<vtkRenderer> renderer;
    */

};

#endif // IMAGEPLANEVIEW_H
