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
#include "SelectionBox.h"
#include "../Tracking/Fibertracker.h"
#include "../GUI/Connector.h"
class Connector;
enum ViewMode{IMAGEPLANE,BOX};
class QVTKWrapper : public QObject
{
	Q_OBJECT
public:
    QVTKWrapper(QVTKWidget*, ViewCreator*,Connector* conn);
    ~QVTKWrapper();
    vtkSmartPointer<vtkRenderer> GetRenderer();
    vtkSmartPointer<vtkRenderWindow> GetRenderWindow();
    vtkSmartPointer<vtkRenderWindowInteractor> GetInteractor();
	vtkSmartPointer<vtkInteractorStyle> GetInteractorStyle();
	SelectionBox* GetSelectionBox();
    QVTKWidget* GetQVTKWidget();
    void render();
    View* getView();
    void setView(View* view);
	ViewMode getViewMode();
	void deactivateView();
public slots:
	void switchToBoxView();
	void switchToImagePlaneView(); 
	void addSelectionBox();
	void Update(vtkVector3d, vtkVector3d, int);

protected:
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkRenderWindow> renWin;
    vtkSmartPointer<vtkRenderWindowInteractor> iren;
    vtkSmartPointer<vtkInteractorStyle> istyle;
    QVTKWidget* qvtkwidget;
    View* view = NULL;
	ViewMode activeView = IMAGEPLANE;
	ViewCreator* vc=NULL;
	FiberTracker* ft = NULL;
	SelectionBox* sb = NULL;
	Connector* conn = NULL;
};

#endif // QVTKWRAPPER_H
