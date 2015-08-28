#include "SelectionBox.h"

class vtkBoxUpdate : public vtkCommand
{
public:
	static vtkBoxUpdate *New()
	{
		return new vtkBoxUpdate;
	}
	virtual void Execute(vtkObject* caller, unsigned long, void*)
	{
		this->sb->update();
	}
	void SetSelectionBox(SelectionBox* sb){
		this->sb = sb;
	}

protected:
	vtkBoxUpdate()
	{
		this->sb = 0;
	}
private:
	SelectionBox* sb;
};

SelectionBox::SelectionBox(){

}

SelectionBox::~SelectionBox(){
}

void SelectionBox::activate(vtkSmartPointer<vtkRenderer> renderer, vtkSmartPointer<vtkRenderWindowInteractor> rendint){

	box->SetPriority(5.0);
        box->PlaceWidget(68.5, 78.5, 116.5, 126.5, 77, 87);
	box->HandlesOff();
	box->SetRotationEnabled(0);
	box->OutlineCursorWiresOff();
	box->OutlineFaceWiresOff();
	vtkBoxUpdate *callback = vtkBoxUpdate::New();
	callback->SetSelectionBox(this);
	box->AddObserver(vtkCommand::InteractionEvent, callback);
	callback->Delete();
	box->SetInteractor(rendint);
	box->SetDefaultRenderer(renderer);
	box->EnabledOn();
	update();
}
void SelectionBox::update(){
	cout << "SelectionBoxUpdate called" << endl;
	vtkSmartPointer<vtkPolyData> points= vtkSmartPointer<vtkPolyData>::New();
	box->GetPolyData(points);
	//points->Print(cout);
	double* bounds = points->GetBounds();
	
	boxWidgetPos.SetX(*(bounds));
	boxWidgetPos.SetY(*(bounds+2));
	boxWidgetPos.SetZ(*(bounds+5));

	boxWidgetExtents.SetX(*(bounds+1) - *(bounds));
	boxWidgetExtents.SetY(*(bounds+3)-*(bounds + 2));
	boxWidgetExtents.SetZ(*(bounds+5)-*(bounds + 4));
	int seedPointsperAxis = 1000;
	emit SelectionBoxChanged(boxWidgetPos, boxWidgetExtents, seedPointsperAxis);
		
}
void SelectionBox::deactivate(vtkSmartPointer<vtkRenderer> renderer){
	box->EnabledOff();
}	
