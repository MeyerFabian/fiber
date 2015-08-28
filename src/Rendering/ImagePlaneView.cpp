#include "ImagePlaneView.h"

ImagePlaneView::ImagePlaneView(vtkSmartPointer<vtkAlgorithmOutput> alg, int dim[3]):
    View()
{
    for(int i = 0; i<length; i++){
      iplane[i]=  vtkSmartPointer<vtkImagePlaneWidget>::New();
      iplane[i]->SetInputConnection(alg);
      iplane[i]->RestrictPlaneToVolumeOn();
      double color[3] = {1,0,0};
	  color[i] = 1;
      iplane[i]->GetPlaneProperty()->SetColor(color);
      iplane[i]->SetPlaneOrientation(i);
      iplane[i]->SetMarginSizeX(0);
      iplane[i]->SetMarginSizeY(0);
	  iplane[i]->SetSliceIndex(dim[i]/2);
      iplane[i]->UpdatePlacement();


  }

}

ImagePlaneView::~ImagePlaneView(){
}

void ImagePlaneView::activate(vtkSmartPointer<vtkRenderer> renderer, vtkSmartPointer<vtkRenderWindowInteractor> rendint){
    for(int i = 0; i<length; i++){
    iplane[i]->SetInteractor(rendint);
    iplane[i]->SetDefaultRenderer(renderer);
    iplane[i]->On();
    }
}

void ImagePlaneView::deactivate(vtkSmartPointer<vtkRenderer> renderer){
	for (int i = 0; i<length; i++){
		iplane[i]->Off();
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
