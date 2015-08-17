#ifndef IMAGEPLANEVIEW_H
#define IMAGEPLANEVIEW_H
#include "vtkSmartPointer.h"
#include "vtkAlgorithmOutput.h"
#include "vtkRenderer.h"
#include "vtkImagePlaneWidget.h"
#include "vtkProperty.h"
#include "vtkRenderWindowInteractor.h"

class ImagePlaneView
{
public:
    ImagePlaneView(vtkSmartPointer<vtkRenderer> renderer,vtkSmartPointer<vtkRenderWindowInteractor> rend, vtkSmartPointer<vtkAlgorithmOutput> alg);
    ~ImagePlaneView();
    /*
    vtkSmartPointer<vtkRenderWindowInteractor> GetRenderWindowInteractor();
    vtkSmartPointer<vtkAlgorithmOutput> GetAlgorithmOutput();
    vtkSmartPointer<vtkRenderer> GetRenderer();
    */

protected:
    vtkSmartPointer<vtkImagePlaneWidget> iplane[3];
    /*
    vtkSmartPointer<vtkRenderWindowInteractor> rwi;
    vtkSmartPointer<vtkAlgorithmOutput> ao;
    vtkSmartPointer<vtkRenderer> renderer;
    */

};

#endif // IMAGEPLANEVIEW_H
