#include "FiberTracker.h"

//////////////////////////////////////////
// FIBERTRACKING MAINPART ////////////////
//////////////////////////////////////////

FiberTracker::FiberTracker(vtkSmartPointer<vtkImageReader2> imgreader)
{
	this->reader = imgreader;

	fiberlines = new std::vector<vtkSmartPointer<vtkPoints> >();

	tensorComp = new TensorComputations();
	pointLocator = vtkSmartPointer<vtkPointLocator>::New();
	//vtkImageData* input = this->reader->GetOutput();

	pointLocator->SetDataSet(this->reader->GetOutput());
	pointLocator->BuildLocator();

	cout << "found data with " << imgreader->GetOutput()->GetPointData()->GetScalars()->GetNumberOfComponents() << " components per point" << endl;
	//imgreader->GetOutput()->GetPointData()->GetScalars()->SetNumberOfComponents(9);

	this->stepSize = 1.0;
	this->f = 1.0;
	this->g = 0.2;
}


FiberTracker::~FiberTracker()
{
	fiberlines->clear();
	delete fiberlines;
	//delete ?
}

vtkVector3d addVec(vtkVector3d vec1, vtkVector3d vec2);
vtkVector3d substractVec(vtkVector3d vec1, vtkVector3d vec2);
vtkVector3d multiplyVec(vtkVector3d vec1, double scalar);

void FiberTracker::Init(){

}


void FiberTracker::Update(vtkVector3d boxWidgetPos, vtkVector3d boxWidgetExtents, int seedPointsPerAxis){
	//cout << "FiberTracking Update called"<<endl;
	//cout << "Position: (" << boxWidgetPos.GetX() << "," << boxWidgetPos.GetY() << "," << boxWidgetPos.GetZ() << ")" << endl;
	//cout << "Size: (" << boxWidgetExtents.GetX() << "," << boxWidgetExtents.GetY() << "," << boxWidgetExtents.GetZ() << ")" << endl;
	
	fiberlines->clear();
	vtkVector3d startPoint;

	double x, y, z;
	int fiberLineCounter = 0;

	for (int i = 0; i < seedPointsPerAxis; i++){
		for (int j = 0; j < seedPointsPerAxis; j++){
			for (int k = 0; k < seedPointsPerAxis; k++){
				
				x = boxWidgetPos.GetX() + (double)i / (double)seedPointsPerAxis * boxWidgetExtents.GetX();
				y = boxWidgetPos.GetY() + (double)j / (double)seedPointsPerAxis * boxWidgetExtents.GetY();
				z = boxWidgetPos.GetZ() + (double)k / (double)seedPointsPerAxis * boxWidgetExtents.GetZ();
				startPoint.Set(x, y, z);

				TrackFiber(startPoint, fiberLineCounter);
				fiberLineCounter++;
			}
		}
	}
	
	
}

void FiberTracker::TrackFiber(vtkVector3d startPoint, int fiberLineNr){
	vtkVector3d one;
	one.Set(1, 1, 1);
	bool prntInfo = false;

	// ------------- Initialize

	currentPos.Set(startPoint.GetX(), startPoint.GetY(), startPoint.GetZ());

	double curPos[3];
	curPos[0] = currentPos.GetX();
	curPos[1] = currentPos.GetY();
	curPos[2] = currentPos.GetZ();

	//this->reader->Update(); //??

	vtkIdType pointID = pointLocator->FindClosestPoint(curPos);//pointer?

	vtkSmartPointer<vtkMatrix3x3> tensors = tensorComp->GetTensorsFromNIFTI(this->reader, pointID);//normaler statt Smartpointer??//global definieren??
	vtkSmartPointer<vtkMatrix3x3> eigenvectorMatrix = tensorComp->GetEigenvectorsFromTensor(tensors);

	if (prntInfo){
		cout << "Starting ID: " << pointID << endl;
		cout << "Current 1. Tensor: " << tensors->GetElement(1, 0) << " | " << tensors->GetElement(1, 1) << " | " << tensors->GetElement(1, 2) << endl;
		cout << "Current 1. Eigenvec: " << eigenvectorMatrix->GetElement(0, 0) << " | " << eigenvectorMatrix->GetElement(0, 1) << " | " << eigenvectorMatrix->GetElement(0, 2) << endl;
		cout << "=========================" << endl;
	}

	vtkVector3d eigenvectors[3];
	eigenvectors[0].Set(eigenvectorMatrix->GetElement(0, 0), eigenvectorMatrix->GetElement(0, 1), eigenvectorMatrix->GetElement(0, 2));	//Reihenfolge?!
	eigenvectors[1].Set(eigenvectorMatrix->GetElement(1, 0), eigenvectorMatrix->GetElement(1, 1), eigenvectorMatrix->GetElement(1, 2));
	eigenvectors[2].Set(eigenvectorMatrix->GetElement(2, 0), eigenvectorMatrix->GetElement(2, 1), eigenvectorMatrix->GetElement(2, 2));

	int random = rand() % 3 + 1;	// In the range 1 to 3	//#ToDo: Make vector-norm dependent!

	if (random == 1)
		currentDir = eigenvectors[0];
	else if (random == 2)
		currentDir = eigenvectors[1];
	else if (random == 3)
		currentDir = eigenvectors[2];
	else
		cout << "ERROR" << endl;

	// -----------------

	int invalidStepsTaken = 0;

	//create new fiberline
	fiberlines->push_back(vtkSmartPointer<vtkPoints>::New());
	fiberlines->at(fiberLineNr)->InsertNextPoint(curPos);


	while (invalidStepsTaken < 70){		//#ToDo: Abbruchbed. verbessern

		pointID = pointLocator->FindClosestPoint(curPos);

		//Perform step
		currentPos = addVec(currentPos, multiplyVec(currentDir.Normalized(), this->stepSize));

		//Get current corresponding pointID

		curPos[0] = currentPos.GetX();
		curPos[1] = currentPos.GetY();
		curPos[2] = currentPos.GetZ();
		vtkIdType newPointID = pointLocator->FindClosestPoint(curPos);

		//Check if entering new voxel
		if (newPointID != pointID){
			//Determine next direction with smallest angle to incoming direction
			tensors = tensorComp->GetTensorsFromNIFTI(this->reader, newPointID);
			eigenvectorMatrix = tensorComp->GetEigenvectorsFromTensor(tensors);

			if (prntInfo){
				cout << "Current Pos: " << curPos[0] << " | " << curPos[1] << " | " << curPos[2] << endl;
				cout << "new PointID: " << newPointID << endl;
				cout << "Current 2. Tensor: " << tensors->GetElement(1, 0) << " | " << tensors->GetElement(1, 1) << " | " << tensors->GetElement(1, 2) << endl;
				cout << "Current 2. Eigenvec: " << eigenvectorMatrix->GetElement(0, 0) << " | " << eigenvectorMatrix->GetElement(0, 1) << " | " << eigenvectorMatrix->GetElement(0, 2) << endl;
				cout << "--------------------------" << endl;
			}

			eigenvectors[0].Set(eigenvectorMatrix->GetElement(0, 0), eigenvectorMatrix->GetElement(0, 1), eigenvectorMatrix->GetElement(0, 2));	//Reihenfolge?!
			eigenvectors[1].Set(eigenvectorMatrix->GetElement(1, 0), eigenvectorMatrix->GetElement(1, 1), eigenvectorMatrix->GetElement(1, 2));
			eigenvectors[2].Set(eigenvectorMatrix->GetElement(2, 0), eigenvectorMatrix->GetElement(2, 1), eigenvectorMatrix->GetElement(2, 2));

			float angles[3];
			angles[0] = eigenvectors[0].Dot(currentDir);
			angles[1] = eigenvectors[1].Dot(currentDir);
			angles[2] = eigenvectors[2].Dot(currentDir);

			//find next direction = eigenvector with smallest angle
			float smallestAngle = angles[0];
			v_n = eigenvectors[0];
			for (int i = 1; i < 3; i++){
				if (angles[i] < smallestAngle){
					smallestAngle = angles[i];
					v_n = eigenvectors[i];
				}
			}
			v_nPlus1 = addVec(multiplyVec(v_n, this->f), multiplyVec(addVec(multiplyVec(currentDir, (1.0 - this->g)), multiplyVec(v_n, this->g)), (1.0 - f)));		//Tracking formula //Gives out next direction
			currentDir = v_nPlus1;

			// Add point to renderer
			fiberlines->at(fiberLineNr)->InsertNextPoint(curPos);

		}

		else{

			if (prntInfo)
				cout << "did not enter new Voxel" << endl;

			//Perform further step
			currentPos = addVec(currentPos, multiplyVec(currentDir.Normalized(), this->stepSize));

			invalidStepsTaken++;
		}

		//delete ...?;
	}
	emit updateFibers(fiberlines);
}


//Custom Vector classes
vtkVector3d addVec(vtkVector3d vec1, vtkVector3d vec2){
	vtkVector3d returnVec;
	returnVec.Set(vec1.GetX() + vec2.GetX(), vec1.GetY() + vec2.GetY(), vec1.GetZ() + vec2.GetZ());
	return returnVec;
}

vtkVector3d substractVec(vtkVector3d vec1, vtkVector3d vec2){
	vtkVector3d returnVec;
	returnVec.Set(vec1.GetX() - vec2.GetX(), vec1.GetY() - vec2.GetY(), vec1.GetZ() - vec2.GetZ());
	return returnVec;
}

vtkVector3d multiplyVec(vtkVector3d vec1, double scalar){
	vtkVector3d returnVec;
	returnVec.Set(vec1.GetX() *scalar, vec1.GetY() *scalar, vec1.GetZ() *scalar);
	return returnVec;


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