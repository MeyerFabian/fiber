#include "ViewCreator.h"

ViewCreator::ViewCreator()
{

}
ViewCreator::~ViewCreator(){

}

// Specifies the inputs of new BoxViews.
void ViewCreator::BoxViewSpecifier(vtkSmartPointer<vtkAlgorithmOutput> alg, vtkSmartPointer<vtkSmartVolumeMapper> mapper, vtkSmartPointer<vtkProp> prop){
	this->alg = alg;
	this->prop = prop;
	this->mapper = mapper;
}

// Specifies the inputs of new ImagePlanes.
void ViewCreator::ImagePlaneViewSpecifier(vtkSmartPointer<vtkAlgorithmOutput> alg, int dim[3]){
	this->alg = alg;
	for (int i = 0; i < 3; i++){
		this->dim[i] = dim[i];
	}
}

// Call the constructor of a BoxView with the inputs.
BoxView* ViewCreator::createBoxView(){
	return new BoxView(alg, mapper, prop);
}

// Call the constructor of a ImagePlaneView with the inputs.
ImagePlaneView* ViewCreator::createImagePlaneView(){
	return new ImagePlaneView(alg,dim);
}