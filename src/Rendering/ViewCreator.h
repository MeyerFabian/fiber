/*	ViewCreator.h
*
*		The ViewCreator can create new Views on the fly when the View is specified before.
*
*	Fabian
*/

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
	void ImagePlaneViewSpecifier(vtkSmartPointer<vtkAlgorithmOutput> alg,int dim[3]);
	BoxView* createBoxView();
	ImagePlaneView* createImagePlaneView();
private:
	vtkSmartPointer<vtkAlgorithmOutput> alg; 
	vtkSmartPointer<vtkSmartVolumeMapper> mapper;
	vtkSmartPointer<vtkProp> prop;
	int dim[3];
};

#endif // VIEW_H
