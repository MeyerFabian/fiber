#include "ImagePlaneView.h"
//Initilaizes 3 ImagePlaneWidgets, which display a slice of the volume on the plane.
ImagePlaneView::ImagePlaneView(vtkSmartPointer<vtkAlgorithmOutput> alg, int dim[3]):
    View()
{
    for(int i = 0; i<length; i++){

      iplane[i]=  vtkSmartPointer<vtkImagePlaneWidget>::New();

	  //Restrict the Planes to the Volume.
      iplane[i]->SetInputConnection(alg);
      iplane[i]->RestrictPlaneToVolumeOn();
	  
	  //Set the outline Colors of the Widgets.
      double color[3] = {1,0,0};
	  color[i] = 1;
      iplane[i]->GetPlaneProperty()->SetColor(color);

	  //Align Planes with axis and disable Rotation.
	  iplane[i]->SetPlaneOrientation(i);
      iplane[i]->SetMarginSizeX(0);
      iplane[i]->SetMarginSizeY(0);

	  //Set Position of the Widgets to their corresponding mid.
	  iplane[i]->SetSliceIndex(dim[i]/2);

      iplane[i]->UpdatePlacement();


  }

}

ImagePlaneView::~ImagePlaneView(){
}


//Registers the Widgets at the renderer and interactor to render it and enable interaction.
void ImagePlaneView::activate(vtkSmartPointer<vtkRenderer> renderer, vtkSmartPointer<vtkRenderWindowInteractor> rendint){
    
	for(int i = 0; i<length; i++){
		iplane[i]->SetInteractor(rendint);
		iplane[i]->SetDefaultRenderer(renderer);
		iplane[i]->On();
    }
}

//Deactivates the Widgets,(because we want to switch views probably).
void ImagePlaneView::deactivate(vtkSmartPointer<vtkRenderer> renderer){
	for (int i = 0; i<length; i++){
		iplane[i]->Off();
	}
}
