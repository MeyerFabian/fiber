#include "QVTKWrapper.h"

QVTKWrapper::QVTKWrapper(QVTKWidget* qvtk )
{
    renderer = vtkSmartPointer<vtkRenderer>::New();
    renWin = vtkSmartPointer<vtkRenderWindow>::New();
    renWin->AddRenderer(renderer);
    iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    iren->SetRenderWindow(renWin);
    istyle = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    iren->SetInteractorStyle(istyle);
    this-> qvtkwidget =qvtk;
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
    view->setActive(this->renderer,this->iren);
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

void QVTKWrapper::switchToBoxView(){

}

void QVTKWrapper::switchToImagePlaneView(){

}