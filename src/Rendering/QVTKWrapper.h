#ifndef QVTKWRAPPER_H
#define QVTKWRAPPER_H
#include "vtkSmartPointer.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkInteractorStyle.h"
#include "QVTKWidget.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "View.h"
#include "ViewCreator.h"
#include  "qobject.h"

enum ViewMode{IMAGEPLANE,BOX};
class QVTKWrapper : public QObject
{
	Q_OBJECT
public:
    QVTKWrapper(QVTKWidget*, ViewCreator*);
    ~QVTKWrapper();
    vtkSmartPointer<vtkRenderer> GetRenderer();
    vtkSmartPointer<vtkRenderWindow> GetRenderWindow();
    vtkSmartPointer<vtkRenderWindowInteractor> GetInteractor();
    vtkSmartPointer<vtkInteractorStyle> GetInteractorStyle();
    QVTKWidget* GetQVTKWidget();
    void render();
    View* getView();
    void setView(View* view);
public slots:
	void switchToBoxView();
	void switchToImagePlaneView();

protected:
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkRenderWindow> renWin;
    vtkSmartPointer<vtkRenderWindowInteractor> iren;
    vtkSmartPointer<vtkInteractorStyle> istyle;
    QVTKWidget* qvtkwidget;
    View* view = NULL;
	ViewMode activeView = IMAGEPLANE;
	ViewCreator* vc=NULL;
};

#endif // QVTKWRAPPER_H
