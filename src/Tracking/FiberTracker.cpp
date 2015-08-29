#include "FiberTracker.h"

//////////////////////////////////////////
// FIBERTRACKING MAINPART ////////////////
//////////////////////////////////////////

FiberTracker::FiberTracker()
{
	fiberlines = new std::vector<vtkSmartPointer<vtkPoints> >();
}


FiberTracker::~FiberTracker()
{
	fiberlines->clear();
	delete fiberlines;
}


void FiberTracker::Init(){}

/*
	DESIRED INPUT:
	----------------
	double stepSize;
	double f;
	double g;
	vector3 startpoint = boxWidgetPos;
	vector3 boxWidgetExtents
	int seedPointsPerAxis

*/

void FiberTracker::Update(vtkVector3d boxWidgetPos, vtkVector3d boxWidgetExtents, int seedPointsPerAxis){
	cout << "FiberTracking Update called"<<endl;
	cout << "Position: (" << boxWidgetPos.GetX() << "," << boxWidgetPos.GetY() << "," << boxWidgetPos.GetZ() << ")" << endl;
	cout << "Size: (" << boxWidgetExtents.GetX() << "," << boxWidgetExtents.GetY() << "," << boxWidgetExtents.GetZ() << ")" << endl;
	/*
	for (std::vector<vtkSmartPointer<vtkPoints> >::size_type t = 0; t < fiberlines->size(); t++){
		fiberlines->at(t)->Delete();
	}
	*/
	fiberlines->clear();
	
	//Line 1
	fiberlines->push_back(vtkSmartPointer<vtkPoints>::New());
		//Point 1
	double p00[3] = { boxWidgetPos.GetX(), boxWidgetPos.GetY(), boxWidgetPos.GetZ() };
		fiberlines->at(0)->InsertNextPoint(p00);
		//Point 2
		double p01[3] = { 5.0, 0.0, 0.0 };
		fiberlines->at(0)->InsertNextPoint(p01);
		//Point 3
		double p02[3] = { 5.0, 10.0, 0.0 };
		fiberlines->at(0)->InsertNextPoint(p02);
		//Point 4
		double p03[3] = { 6.0, 50.0, 0.0 };
		fiberlines->at(0)->InsertNextPoint(p03);
		//Point 5
		double p04[3] = { 7.0, 70.0, 0.0 };
		fiberlines->at(0)->InsertNextPoint(p04);
		
	//Line 2
	fiberlines->push_back(vtkSmartPointer<vtkPoints>::New());
		//Point 1
	double p10[3] = { boxWidgetPos.GetX(), boxWidgetPos.GetY(), boxWidgetPos.GetZ() };
		fiberlines->at(1)->InsertNextPoint(p00);
		//Point 2
		double p11[3] = { 50.0, 0.0, 0.0 };
		fiberlines->at(1)->InsertNextPoint(p11);
		//Point 3
		double p12[3] = { 50.0, 20.0, 0.0 };
		fiberlines->at(1)->InsertNextPoint(p12);
		//Point 4
		double p13[3] = { 70.0, 20.0, 0.0 };
		fiberlines->at(1)->InsertNextPoint(p13);
		//Point 5
		double p14[3] = { 80.0, 0.0, 0.0 };
		fiberlines->at(1)->InsertNextPoint(p14);
		
	/*
	tensorComp = new TensorComputations();

	// -------------- Global/GUI Parameters/variables
	double stepSize = 1;
	double f = 0;
	double g = 0;
	vtkVector3d one;
	one.Set(1, 1, 1);
	vtkVector3d startPoint;
	startPoint.Set(0, 0, 0);																	//in structured coordinates for point ID

	vtkVector3d currentPos;
	vtkVector3d currentDir;																	//= next step direction = incoming direction = V_n-1

	// ------------- Initialize

	currentPos.Set(startPoint.GetX(), startPoint.GetY(), startPoint.GetZ());
	double ijk[3];
	ijk[0] = startPoint.GetX();
	ijk[1] = startPoint.GetY();
	ijk[2] = startPoint.GetZ();
	//vtkIdType pointID = input->ComputeCellId(ijk);											//oder input->FindCell(FindCell(currentPos); ??
	//vtkIdType pointID = input->FindPoint(ijk);
	//vtkIdType pointID = input->FindCell(ijk,);
	int abc[3];
	abc[0] = 1;
	abc[1] = 1;
	abc[2] = 1;
	vtkIdType pointID = input->ComputeCellId(abc);

	vtkSmartPointer<vtkMatrix3x3> tensors = tensorComp->GetTensorsFromNIFTI(reader, pointID);
	vtkSmartPointer<vtkMatrix3x3> eigenvectorMatrix = tensorComp->GetEigenvectorsFromTensor(tensors);

	vtkVector3d eigenvectors[3];
	eigenvectors[0].Set(eigenvectorMatrix->GetElement(0, 0), eigenvectorMatrix->GetElement(0, 1), eigenvectorMatrix->GetElement(0, 2));	//Reihenfolge?!
	eigenvectors[1].Set(eigenvectorMatrix->GetElement(1, 0), eigenvectorMatrix->GetElement(1, 1), eigenvectorMatrix->GetElement(1, 2));
	eigenvectors[2].Set(eigenvectorMatrix->GetElement(2, 0), eigenvectorMatrix->GetElement(2, 1), eigenvectorMatrix->GetElement(2, 2));

	int random = rand() % 3 + 1;	// In the range 1 to 3	//#ToDo: Make vector-norm dependent!

	if (random == 1)
		currentDir = eigenvectors[0].Normalized();
	else if (random == 2)
		currentDir = eigenvectors[1].Normalized();
	else if (random == 3)
		currentDir = eigenvectors[2].Normalized();
	else
		cout << "ERROR" << endl;

	// -----------------

	int counter = 0;	//TEMP
	vtkSmartPointer<vtkPointLocator> pointLocator = vtkSmartPointer<vtkPointLocator>::New();

	while (counter < 50){		//#ToDo: Abbruchbed. einsetzen

		double curPos[3];
		curPos[0] = currentPos.GetX();
		curPos[1] = currentPos.GetY();
		curPos[2] = currentPos.GetZ();
		pointID = pointLocator->FindClosestPoint(curPos);

		cout << "Current Pos: " << curPos[0] << " | " << curPos[1] << " | " << curPos[2] << endl;
		//Perform step
		currentPos = addVec(currentPos, multiplyVec(currentDir.Normalized(), stepSize));

		//Get current corresponding pointID

		curPos[0] = currentPos.GetX();
		curPos[1] = currentPos.GetY();
		curPos[2] = currentPos.GetZ();
		vtkIdType newPointID = pointLocator->FindClosestPoint(curPos);

		//Check if entering new voxel
		if (newPointID != pointID){
			//Determine next direction with smallest angle to incoming direction
			tensors = tensorComp->GetTensorsFromNIFTI(reader, newPointID);
			eigenvectorMatrix = tensorComp->GetEigenvectorsFromTensor(tensors);

			cout << "Current 1. Tensor: " << tensors->GetElement(0, 0) << " | " << tensors->GetElement(0, 1) << " | " << tensors->GetElement(0, 2) << endl;
			cout << "Current 1. Eigenvec: " << eigenvectorMatrix->GetElement(0, 0) << " | " << eigenvectorMatrix->GetElement(0, 1) << " | " << eigenvectorMatrix->GetElement(0, 2) << endl;
			cout << "--------------------------" << endl;

			float angles[3];
			angles[0] = eigenvectors[0].Dot(currentDir);
			angles[1] = eigenvectors[1].Dot(currentDir);
			angles[2] = eigenvectors[2].Dot(currentDir);

			//find next direction = eigenvector with smallest angle
			float smallestAngle = angles[0];
			vtkVector3d v_n = eigenvectors[0];
			for (int i = 1; i < 3; i++){
				if (angles[i] < smallestAngle){
					smallestAngle = angles[i];
					v_n = eigenvectors[i];
				}
			}
			vtkVector3d v_nPlus1 = addVec(multiplyVec(v_n, f), multiplyVec(addVec(multiplyVec(currentDir, (1 - g)), multiplyVec(v_n, g)), (1 - f)));		//Tracking formula //Gives out next direction
			currentDir = v_nPlus1;
		}
		else{
			//?
		}

		// Add point and tangent vector to renderer
		//HyperstreamBSplineRenderer.Append(currentPos, currentDir, streamlineID);

		counter++;
		//delete ...;
	}
	*/
	emit updateFibers(fiberlines);
}



/////////////////////////////////////////

/*

//TESTING/COMPUTING FULL DATASET

tensorComp = new TensorComputations();

for (int z = 0; z < dim[2]; z++)
{
for (int y = 0; y < dim[1]; y++)
{
for (int x = 0; x < dim[0]; x++)
{
int ijk[3];
ijk[0] = x;
ijk[1] = y;
ijk[2] = z;
vtkIdType pointID = input->ComputeCellId(ijk);	//korrekte Methode??


//vtkSmartPointer<vtkMatrix3x3> tensors = tensorComp->GetTensorsFromNIFTI(reader, pointID);
//vtkSmartPointer<vtkMatrix3x3> eigenvectors = tensorComp->GetEigenvectorsFromTensor(tensors);

//Valle: Call main traverse function
//TrackFibers(startpoint, input, tensors);
}
}
}

*/