/*	QVTKWrapper.h
*
*		QVTKWrapper is the Connection from the QTGui to the VTKRenderWindow.
*		It uses several Methods that are called back by the GUI to render
*		various properties, actors, widgets and even initialize the
*		FiberTracking, when said so by the GUI.
*	
*	Fabian
*/

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
#include "Fiber.h"
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
	void SetImageReader(vtkSmartPointer<vtkImageReader2> imgreader);
	SelectionBox* GetSelectionBox();
	FiberTracker* GetFiberTracker(); 
	Fiber* GetFiber();
    QVTKWidget* GetQVTKWidget();
    void render();
    View* getView();
    void setView(View* view);
	ViewMode getViewMode();
	void deactivateView();
public slots:
	void switchToBoxView();
	void switchToImagePlaneView(); 
	void addMainAlgorithm();
	void Update(vtkVector3d, vtkVector3d, int);

protected:
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkRenderWindow> renWin;
    vtkSmartPointer<vtkRenderWindowInteractor> iren;
    vtkSmartPointer<vtkInteractorStyle> istyle;
	vtkSmartPointer<vtkImageReader2> reader;
    QVTKWidget* qvtkwidget;
    View* view = NULL;
	ViewMode activeView = IMAGEPLANE;
	ViewCreator* vc=NULL;
	FiberTracker* ft = NULL;
	Fiber *fl = NULL;
	SelectionBox* sb = NULL;
	Connector* conn = NULL;
};

#endif // QVTKWRAPPER_H
