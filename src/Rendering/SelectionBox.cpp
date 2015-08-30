#include "SelectionBox.h"


// CallBack whenever the SelectionBox is interacted with,
// so we can send its updated position and size to the FiberTracking algorithm.
class vtkBoxUpdate : public vtkCommand
{
public:
	static vtkBoxUpdate *New()
	{
		return new vtkBoxUpdate;
	}
	virtual void Execute(vtkObject* caller, unsigned long, void*)
	{
		//Executes the update of a SelectionBox.
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

// One Time Call at the beginning of the algorithm to activate the Widget. 
// This also enables switching views, while the selectionBox is still in place and can be moved around.
void SelectionBox::activate(vtkSmartPointer<vtkRenderer> renderer, vtkSmartPointer<vtkRenderWindowInteractor> rendint){
	
	//Set the priority of the Selection Box higher than any other widget. 
	//So the picker always selects the Box and not any other widgets before or behind it.
	box->SetPriority(5.0);

	//Set the initial Position of the box (here somewhat interesting point).
    box->PlaceWidget(68.5, 78.5, 116.5, 126.5, 77, 87);
	
	//Handles for Scaling off, because they occlude the box in a lot of cases.
	box->HandlesOff();

	//Rotation disabled.
	box->SetRotationEnabled(0);

	//Simplify the Box, so view is less occluded.
	box->OutlineCursorWiresOff();
	box->OutlineFaceWiresOff();

	//Register Observer and Callback for our update to the Fibertracker.
	vtkBoxUpdate *callback = vtkBoxUpdate::New();
	callback->SetSelectionBox(this);
	box->AddObserver(vtkCommand::InteractionEvent, callback);
	callback->Delete();

	//Specify interactor and renderer.
	box->SetInteractor(rendint);
	box->SetDefaultRenderer(renderer);
	box->EnabledOn();

	//Call the update method one time, so we do an initial tracking iteration right at the start.
	update();
}
void SelectionBox::update(){
	cout << "SelectionBoxUpdate called" << endl;

	//Convert the Widget to Polydata, so we can read out its position and size.
	vtkSmartPointer<vtkPolyData> points= vtkSmartPointer<vtkPolyData>::New();
	box->GetPolyData(points);

	//We actually take the bounds of the Box, which will be the same than the box
	//, because there is not rotation.
	double* bounds = points->GetBounds();
	boxWidgetPos.SetX(*(bounds));
	boxWidgetPos.SetY(*(bounds+2));
	boxWidgetPos.SetZ(*(bounds+5));


	//Calculate its extents.
	boxWidgetExtents.SetX(*(bounds+1) - *(bounds));
	boxWidgetExtents.SetY(*(bounds+3)-*(bounds + 2));
	boxWidgetExtents.SetZ(*(bounds+5)-*(bounds + 4));

	int seedPointsperAxis = 10;
	//Signal the FiberTracker that our SelectionBox was updated.
	emit SelectionBoxChanged(boxWidgetPos, boxWidgetExtents, seedPointsperAxis);
		
}

//Deactivates the SelectionBox, when we start over.
void SelectionBox::deactivate(vtkSmartPointer<vtkRenderer> renderer){
	box->EnabledOff();
}	
