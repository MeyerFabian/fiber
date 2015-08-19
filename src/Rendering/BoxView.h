#ifndef BOXVIEW_H
#define BOXVIEW_H
#include "vtkSmartPointer.h"
#include "vtkImageResample.h"
#include "vtkRenderer.h"
#include "vtkBoxWidget.h"
#include "vtkProperty.h"
#include "vtkRenderWindowInteractor.h"
#include "view.h"
#include "vtkCommand.h"
#include "vtkSmartVolumeMapper.h"
#include "vtkPlanes.h"
#include "vtkAlgorithmOutput.h"
#include "vtkProp.h"

class BoxView : public View
{
public:
    BoxView(vtkSmartPointer<vtkAlgorithmOutput> alg,vtkSmartPointer<vtkSmartVolumeMapper> mapper, vtkSmartPointer<vtkProp> prop);
    ~BoxView();


protected:
    vtkSmartPointer<vtkBoxWidget> box = vtkSmartPointer<vtkBoxWidget>::New();
    void setActive(vtkSmartPointer<vtkRenderer> renderer, vtkSmartPointer<vtkRenderWindowInteractor> rendint);
private:
    vtkSmartPointer<vtkProp> prop;

};

#endif // BOXVIEW_H
