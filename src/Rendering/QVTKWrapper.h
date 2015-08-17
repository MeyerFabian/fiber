#ifndef QVTKWRAPPER_H
#define QVTKWRAPPER_H
#include "vtkSmartPointer.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkInteractorStyle.h"
#include "QVTKWidget.h"

class QVTKWrapper
{
public:
    QVTKWrapper();
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkRenderWindow> renWin;
    vtkSmartPointer<vtkRenderWindowInteractor> iren;
    vtkSmartPointer<vtkInteractorStyle> istyle;
    vtkSmartPointer<QVTKWidget> qvtkwidget;
};

#endif // QVTKWRAPPER_H
