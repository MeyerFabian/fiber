#include "ViewCreator.h"

ViewCreator::ViewCreator()
{

}
ViewCreator::~ViewCreator(){

}
void ViewCreator::BoxViewSpecifier(vtkSmartPointer<vtkAlgorithmOutput> alg, vtkSmartPointer<vtkSmartVolumeMapper> mapper, vtkSmartPointer<vtkProp> prop){
	this->alg = alg;
	this->prop = prop;
	this->mapper = mapper;
}
void ViewCreator::ImagePlaneViewSpecifier(vtkSmartPointer<vtkAlgorithmOutput> alg){
	this->alg = alg;
}

BoxView* ViewCreator::createBoxView(){
	return new BoxView(alg, mapper, prop);
}
ImagePlaneView* ViewCreator::createImagePlaneView(){
	return new ImagePlaneView(alg);
}