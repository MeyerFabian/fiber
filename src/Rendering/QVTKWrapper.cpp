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

QVTKWidget* QVTKWrapper::GetQVTKWidget(){
    return this->qvtkwidget;
}
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
void QVTKWrapper::switchToBoxView(){
	//CAN BE DONE WAY MORE EFFICIENT BY STORING PREVIOUS VIEWS, MIGHT CONSIDER DOING IT LATER ON
	view->deactivate(this->renderer);
	delete view;
	activeView = BOX;
	setView(vc->createBoxView());
	if (view != NULL){
		view->activate(this->renderer, this->iren);
	}
}

void QVTKWrapper::switchToImagePlaneView(){
	//CAN BE DONE WAY MORE EFFICIENT BY STORING PREVIOUS VIEWS, MIGHT CONSIDER DOING IT LATER ON
	view->deactivate(this->renderer);
	delete view;
	activeView = IMAGEPLANE;
	setView(vc->createImagePlaneView());
	if (view != NULL){
		view->activate(this->renderer, this->iren);
	}
}


void QVTKWrapper::deactivateView(){
	if (view != NULL){
		view->deactivate(this->renderer);
	}
}

void QVTKWrapper::addMainAlgorithm(){
	if (sb != NULL){
		sb->deactivate(this->renderer);
	}
	delete sb;
	sb = new SelectionBox();
	ft = new FiberTracker();
	conn->addFiberTracker(this);
	fl = new Fiber();
	conn->addFiberLines(this);
	sb->activate(this->renderer, this->iren);
	fl->activate(this->renderer, this->iren);
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
void QVTKWrapper::Update(vtkVector3d boxWidgetPos, vtkVector3d boxWidgetExtents, int seedPointsPerAxis){
	ft->Update(boxWidgetPos, boxWidgetExtents, seedPointsPerAxis);
}