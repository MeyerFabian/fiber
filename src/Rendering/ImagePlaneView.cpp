#include "ImagePlaneView.h"

ImagePlaneView::ImagePlaneView(vtkSmartPointer<vtkRenderer> renderer, vtkSmartPointer<vtkRenderWindowInteractor> rendint, vtkSmartPointer<vtkAlgorithmOutput> alg)
{
    for(int i = 0; i<3; i++){
      iplane[i]=  vtkSmartPointer<vtkImagePlaneWidget>::New();
      iplane[i]->SetInteractor(rendint);
      iplane[i]->SetInputConnection(alg);
      iplane[i]->RestrictPlaneToVolumeOn();
      double color[3] = {0,1,0};
      iplane[i]->GetPlaneProperty()->SetColor(color);
      iplane[i]->SetPlaneOrientation(i);
      iplane[i]->SetMarginSizeX(0);
      iplane[i]->SetMarginSizeY(0);
      iplane[i]->SetDefaultRenderer(renderer);
      iplane[i]->UpdatePlacement();

      iplane[i]->On();
  }

}

ImagePlaneView::~ImagePlaneView(){
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
