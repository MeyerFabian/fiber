#include "Fiber.h"

Fiber::Fiber(vtkSmartPointer<vtkRenderer> renderer){
	this->renderer = renderer;
	actors = std::vector<vtkSmartPointer<vtkActor> >();
}

Fiber::~Fiber(){
}

// Adds all the Fiberlines to the renderer as actors
void Fiber::activate(){
	for (std::vector<vtkSmartPointer<vtkActor> >::size_type t = 0; t < actors.size(); t++){
		renderer->AddViewProp(actors.at(t));

	}

	//cout << "FiberLines Activate called" << endl;
}

// Generates the actual Fiberlines, which are PolyLines. Method can be optimized a lot probably.
void Fiber::update(std::vector<vtkSmartPointer<vtkPoints> >* fiberlines){
	//cout << "FiberLines Update called" << endl;

	//Deactivate all Lines that are currently displayed,
	deactivate();
	//so we can clear the vector and start over.
	actors.clear();

	size_t numberOfPoints=0;
	for (std::vector<vtkSmartPointer<vtkPoints> >::size_type t = 0; t < fiberlines->size(); t++){

		// Create a cell array to store the line in and add the line to it
		vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();

		// Create a polydata to store everything in
		vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();

		//Create a new Line
		vtkSmartPointer<vtkPolyLine> polyLine = vtkSmartPointer<vtkPolyLine>::New();

		//Set the points that create this line
		numberOfPoints = fiberlines->at(t)->GetNumberOfPoints();
		polyLine->GetPointIds()->SetNumberOfIds(numberOfPoints);
		for (size_t i = 0; i < numberOfPoints; i++){
			polyLine->GetPointIds()->SetId(i, i);
		}

		cells->InsertNextCell(polyLine);

		// Add the points to the dataset
		polyData->SetPoints(fiberlines->at(t));
		// Add the lines to the dataset
		polyData->SetLines(cells);

		// Setup actor and mapper
		vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
		mapper->SetInputData(polyData);
		vtkSmartPointer<vtkActor> actor1 =vtkSmartPointer<vtkActor>::New();
		actor1->SetMapper(mapper);
		actors.push_back(actor1);

	}

	//Render the lines
	activate();
	
}

//Removes all actors(lines) from the Renderer
void Fiber::deactivate(){
	for (std::vector<vtkSmartPointer<vtkActor> >::size_type t = 0; t < actors.size(); t++){
		renderer->RemoveViewProp(actors.at(t));
	}
}	
