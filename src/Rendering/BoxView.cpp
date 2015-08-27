#include "BoxView.h"

// Callback for moving the planes from the box widget to the mapper

class vtkBoxWidgetCallback : public vtkCommand
{
public:
  static vtkBoxWidgetCallback *New()
    { return new vtkBoxWidgetCallback; }
  virtual void Execute(vtkObject* caller, unsigned long, void*)
    {
      vtkSmartPointer<vtkBoxWidget> widget = reinterpret_cast<vtkBoxWidget * >(caller);
      if (this->Mapper)
        {
        vtkSmartPointer<vtkPlanes> planes = vtkSmartPointer<vtkPlanes>::New();
        widget->GetPlanes(planes);
        this->Mapper->SetClippingPlanes(planes);
        this->Mapper->Update();
        }
    }
  void SetMapper(vtkSmartPointer<vtkSmartVolumeMapper> m)
    { this->Mapper = m; }

protected:
  vtkBoxWidgetCallback()
    { this->Mapper = 0; }

  vtkSmartPointer<vtkSmartVolumeMapper> Mapper;
};

BoxView::BoxView(vtkSmartPointer<vtkAlgorithmOutput> alg,  vtkSmartPointer<vtkSmartVolumeMapper> mapper, vtkSmartPointer<vtkProp> vol):
    View()
{

    box->SetPlaceFactor(1.01);
    box->SetInputConnection(alg);
    box->InsideOutOn();
    box->PlaceWidget();
    vtkBoxWidgetCallback *callback = vtkBoxWidgetCallback::New();
    callback->SetMapper(mapper);
    box->AddObserver(vtkCommand::InteractionEvent, callback);
    callback->Delete();
    box->GetSelectedFaceProperty()->SetOpacity(0.0);
    this->prop = vol;


}

BoxView::~BoxView(){
}

void BoxView::activate(vtkSmartPointer<vtkRenderer> renderer, vtkSmartPointer<vtkRenderWindowInteractor> rendint){

	renderer->AddVolume(prop);
    box->SetInteractor(rendint);
    box->SetDefaultRenderer(renderer);

    box->EnabledOn();
}
void BoxView::deactivate(vtkSmartPointer<vtkRenderer> renderer){
	renderer->RemoveAllViewProps();
	box->EnabledOff();
	
}