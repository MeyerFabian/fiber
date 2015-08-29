#include "Fiber.h"

Fiber::Fiber(){

}

Fiber::~Fiber(){
}

void Fiber::activate(vtkSmartPointer<vtkRenderer> renderer, vtkSmartPointer<vtkRenderWindowInteractor> rendint){
	/*
	box->SetPriority(5.0);
        box->PlaceWidget(68.5, 78.5, 116.5, 126.5, 77, 87);
	box->HandlesOff();
	box->SetRotationEnabled(0);
	box->OutlineCursorWiresOff();
	box->OutlineFaceWiresOff();
	box->AddObserver(vtkCommand::InteractionEvent, callback);
	callback->Delete();
	box->SetInteractor(rendint);
	box->SetDefaultRenderer(renderer);
	box->EnabledOn();
	update();
	*/
}
void Fiber::update(std::vector<vtkSmartPointer<vtkPoints> >* fiberlines){
	cout << "FiberLines Update called" << endl;
		
}
void Fiber::deactivate(vtkSmartPointer<vtkRenderer> renderer){
	/*
	box->EnabledOff();
	*/
}	
