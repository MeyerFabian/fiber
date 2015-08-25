#ifndef QVTKWRAPPER_H
#define QVTKWRAPPER_H
#include "vtkSmartPointer.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkInteractorStyle.h"
#include "QVTKWidget.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "View.h"

enum ViewMode{IMAGEPLANE,BOX};
class QVTKWrapper
{
public:
    QVTKWrapper(QVTKWidget*);
    ~QVTKWrapper();
    vtkSmartPointer<vtkRenderer> GetRenderer();
    vtkSmartPointer<vtkRenderWindow> GetRenderWindow();
    vtkSmartPointer<vtkRenderWindowInteractor> GetInteractor();
    vtkSmartPointer<vtkInteractorStyle> GetInteractorStyle();
    QVTKWidget* GetQVTKWidget();
    void render();
    View* getView();
    void setView(View* view);

	void QVTKWrapper::switchToBoxView();
	void QVTKWrapper::switchToImagePlaneView();

protected:
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkRenderWindow> renWin;
    vtkSmartPointer<vtkRenderWindowInteractor> iren;
    vtkSmartPointer<vtkInteractorStyle> istyle;
    QVTKWidget* qvtkwidget;
    View* view = NULL;
	ViewMode activeView = IMAGEPLANE;
};

#endif // QVTKWRAPPER_H
