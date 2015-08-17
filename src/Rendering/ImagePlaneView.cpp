#include "ImagePlaneView.h"

ImagePlaneView::ImagePlaneView(vtkSmartPointer<vtkAlgorithmOutput> alg):
    View()
{

    for(int i = 0; i<length; i++){
      iplane[i]=  vtkSmartPointer<vtkImagePlaneWidget>::New();
      iplane[i]->SetInputConnection(alg);
      iplane[i]->RestrictPlaneToVolumeOn();
      double color[3] = {0,1,0};
      iplane[i]->GetPlaneProperty()->SetColor(color);
      iplane[i]->SetPlaneOrientation(i);
      iplane[i]->SetMarginSizeX(0);
      iplane[i]->SetMarginSizeY(0);
      iplane[i]->UpdatePlacement();


  }

}

ImagePlaneView::~ImagePlaneView(){
}

void ImagePlaneView::setActive(vtkSmartPointer<vtkRenderer> renderer, vtkSmartPointer<vtkRenderWindowInteractor> rendint){
    for(int i = 0; i<length; i++){
    iplane[i]->SetInteractor(rendint);
    iplane[i]->SetDefaultRenderer(renderer);
    iplane[i]->On();
    }
}

/*
vtkSmartPointer<vtkRenderWindowInteractor> ImagePlaneView::GetRenderWindowInteractor(){
    return this->rwi;
}

vtkSmartPointer<vtkAlgorithmOutput> ImagePlaneView::GetAlgorithmOutput(){
    return this->ao;
}
vtkSmartPointer<vtkRenderer> ImagePlaneView::GetRenderer(){
    return this->renderer;
}
*/
