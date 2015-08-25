#ifndef VIEWCREATOR_H
#define VIEWCREATOR_H

#include "vtkSmartPointer.h"
#include "vtkAlgorithmOutput.h"
#include "vtkSmartVolumeMapper.h"
#include "vtkProp.h"
#include "view.h"
#include "BoxView.h"
#include "ImagePlaneView.h"
class ViewCreator
{
public:
    ViewCreator();
	~ViewCreator();
	void BoxViewSpecifier(vtkSmartPointer<vtkAlgorithmOutput> alg, vtkSmartPointer<vtkSmartVolumeMapper> mapper, vtkSmartPointer<vtkProp> prop);
	void ImagePlaneViewSpecifier(vtkSmartPointer<vtkAlgorithmOutput> alg);
	BoxView* createBoxView();
	ImagePlaneView* createImagePlaneView();
private:
	vtkSmartPointer<vtkAlgorithmOutput> alg; 
	vtkSmartPointer<vtkSmartVolumeMapper> mapper;
	vtkSmartPointer<vtkProp> prop;
};

#endif // VIEW_H
