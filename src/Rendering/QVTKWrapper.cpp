#include "QVTKWrapper.h"

QVTKWrapper::QVTKWrapper(QVTKWidget* qvtk ,ViewCreator* vc, Connector* conn)
{
    renderer = vtkSmartPointer<vtkRenderer>::New();
    renWin = vtkSmartPointer<vtkRenderWindow>::New();
    renWin->AddRenderer(renderer);
    iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    iren->SetRenderWindow(renWin);
    istyle = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    iren->SetInteractorStyle(istyle);
    this-> qvtkwidget =qvtk;
	this->vc = vc;
	this->conn = conn;
}

QVTKWrapper::~QVTKWrapper(){
}

vtkSmartPointer<vtkRenderer> QVTKWrapper::GetRenderer(){
    return this->renderer;
}

vtkSmartPointer<vtkRenderWindow> QVTKWrapper::GetRenderWindow(){
    return this->renWin;
}

vtkSmartPointer<vtkRenderWindowInteractor> QVTKWrapper::GetInteractor(){
    return this->iren;
}

vtkSmartPointer<vtkInteractorStyle> QVTKWrapper::GetInteractorStyle(){
    return this->istyle;
}

void QVTKWrapper::SetImageReader(vtkSmartPointer<vtkImageReader2> imgreader){
	this->reader = imgreader;
}

QVTKWidget* QVTKWrapper::GetQVTKWidget(){
    return this->qvtkwidget;
}

// the RenderWindow is updated with the current rendered image from the Renderer and the connection
// between VTKs RenderWindow and the QTRenderWindow (QVTKWidget) is made.
void QVTKWrapper::render(){
    if(view != NULL){
		view->activate(this->renderer,this->iren);
	}
    renWin->AddRenderer(renderer);
    qvtkwidget->SetRenderWindow(renWin);

    renWin->Render();
}

void QVTKWrapper::setView(View* v){
    this->view = v;
}

View* QVTKWrapper::getView(){
    return this->view;
}
ViewMode QVTKWrapper::getViewMode(){
	return this->activeView;
}

// Lets us switch between different views on the fly.
void QVTKWrapper::switchToBoxView(){
	//CAN BE DONE WAY MORE EFFICIENT BY STORING PREVIOUS VIEWS, MIGHT CONSIDER DOING IT LATER ON
	
	//Deactivates the View, which was enabled before (we dont actually care, which type it had)
	view->deactivate(this->renderer);
	delete view;

	//And activates and registers the new view.
	activeView = BOX;
	setView(vc->createBoxView());
	if (view != NULL){
		view->activate(this->renderer, this->iren);
	}
}

void QVTKWrapper::switchToImagePlaneView(){
	view->deactivate(this->renderer);
	delete view;
	activeView = IMAGEPLANE;
	setView(vc->createImagePlaneView());
	if (view != NULL){
		view->activate(this->renderer, this->iren);
	}
}

//Deactivates the view directly, may be called when we open a file although there is already one open.
void QVTKWrapper::deactivateView(){
	if (view != NULL){
		view->deactivate(this->renderer);
	}
}

// Adds SelectionBox, FiberLines and Tracking Algorithm to the QVTKWrapper.
void QVTKWrapper::addMainAlgorithm(){
	// Check if already activated, then delete the old information. 
	// (e.g. reset: click another time on the Fiber Tracking button)
	if (sb != NULL){
		sb->deactivate(this->renderer);
	}
	if (fl != NULL){
		fl->deactivate();
	}
	delete sb;
	delete ft;

	//Add the various parts to the Wrapper and enable the Connections from the GUI or between them.
	sb = new SelectionBox();
	ft = new FiberTracker(this->reader);
	conn->addFiberTracker(this);
	fl = new Fiber(this->renderer);
	conn->addFiberLines(this);

	//Render the Scene one time after everything is added, so the change is displayed immediately.
	sb->activate(this->renderer, this->iren);
	GetRenderWindow()->Render();
}
SelectionBox* QVTKWrapper::GetSelectionBox(){
	return sb;
}
FiberTracker* QVTKWrapper::GetFiberTracker(){
	return ft;
}
Fiber* QVTKWrapper::GetFiber(){
	return fl;
}

// Passes an update of the SelectionBox to the Fibertracker.
void QVTKWrapper::Update(vtkVector3d boxWidgetPos, vtkVector3d boxWidgetExtents, int seedPointsPerAxis){
	ft->Update(boxWidgetPos, boxWidgetExtents, seedPointsPerAxis);
}