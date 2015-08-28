#include "WindowHandler.h"

WindowHandler::WindowHandler(int argc, char *argv[], Connector* conn, Ui::MainWindow* uimw)
{
	this->conn = conn;
	this->uimw = uimw;
	this->argc = argc;
	for (int i = 0; i < argc; i++){
		this->argv[i] = argv[i];
	}

	vc = new ViewCreator();
	window1 = new QVTKWrapper(uimw->qvtkwidget, vc);
}
WindowHandler::~WindowHandler(){
	delete view1;
	delete vc;
	delete window1;
	delete tensorComp;
}
void WindowHandler::init(vtkSmartPointer<vtkImageReader2> reader){


	// Parse the parameters
	int count = 1;
	char *dirname = NULL;
	double opacityWindow = 0.02;
	double opacityLevel = 0.01;
	int blendType = 0;
	int clip = 0;
	double reductionFactor = 1.0;
	double frameRate = 10.0;
	char *fileName = 0;
	int fileType = 0;
	int view = 1;

	bool independentComponents = true;

	while (count < argc)
	{
		if (!strcmp(argv[count], "?"))
		{
			exit(EXIT_SUCCESS);
		}
		else if (!strcmp(argv[count], "-MIP"))
		{
			opacityWindow = atof(argv[count + 1]);
			opacityLevel = atof(argv[count + 2]);
			blendType = 0;
			count += 3;
		}
		else if (!strcmp(argv[count], "-CompositeRamp"))
		{
			opacityWindow = atof(argv[count + 1]);
			opacityLevel = atof(argv[count + 2]);
			blendType = 1;
			count += 3;
		}
		else if (!strcmp(argv[count], "-CompositeShadeRamp"))
		{
			opacityWindow = atof(argv[count + 1]);
			opacityLevel = atof(argv[count + 2]);
			blendType = 2;
			count += 3;
		}
		else if (!strcmp(argv[count], "-RGB_Composite"))
		{
			blendType = 6;
			count += 1;
		}
		else if (!strcmp(argv[count], "-FrameRate"))
		{
			frameRate = atof(argv[count + 1]);
			if (frameRate < 0.01 || frameRate > 60.0)
			{
				cout << "Invalid frame rate - use a number between 0.01 and 60.0" << endl;
				cout << "Using default frame rate of 10 frames per second." << endl;
				frameRate = 10.0;
			}
			count += 2;
		}
		else if (!strcmp(argv[count], "-ReductionFactor"))
		{
			reductionFactor = atof(argv[count + 1]);
			if (reductionFactor <= 0.0 || reductionFactor >= 1.0)
			{
				cout << "Invalid reduction factor - use a number between 0 and 1 (exclusive)" << endl;
				cout << "Using the default of no reduction." << endl;
				reductionFactor = 1.0;
			}
			count += 2;
		}
		else if (!strcmp(argv[count], "-DependentComponents"))
		{
			independentComponents = false;
			count += 1;
		}
	}

	
	// Read the data
	vtkSmartPointer<vtkImageData> input = 0;

	input = reader->GetOutput();

	
	int dim[3];
	input->GetDimensions(dim);
	
	// Verify that we actually have a volume

	if (dim[0] < 2 ||
		dim[1] < 2 ||
		dim[2] < 2)
	{
		cout << "Error loading data!" << endl;
		exit(EXIT_FAILURE);
	}
	
	
	//////////////////////////////////////////
	// FIBERTRACKING MAINPART ////////////////
	//////////////////////////////////////////
	/*
	//#Valle: Get tensors from data


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

	vtkSmartPointer<vtkMatrix3x3> tensors = tensorComp->GetTensorsFromNIFTI(reader, pointID);
	vtkSmartPointer<vtkMatrix3x3> eigenvectors = tensorComp->GetEigenvectorsFromTensor(tensors);

	//Valle: Call main traverse function
	//TrackFibers(startpoint, input, tensors);
	}
	}
	}


	// -------------- Global/GUI Parameters/variables
	double stepSize = 1;
	double f = 0;
	double g = 0;
	vtkVector3d one;
	one.Set(1, 1, 1);
	vtkVector3d startPoint;
	startPoint.Set(0,0,0);																	//in structured coordinates for point ID

	vtkVector3d currentPos;
	vtkVector3d currentDir;																	//= next step direction = incoming direction = V_n-1

	// ------------- Initialize

	currentPos.Set(startPoint.GetX(), startPoint.GetY(), startPoint.GetZ());
	int ijk[3];
	ijk[1] = startPoint.GetX();
	ijk[1] = startPoint.GetY();
	ijk[1] = startPoint.GetZ();
	vtkIdType pointID = input->ComputeCellId(ijk);											//oder input->FindCell(FindCell(currentPos); ??

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

	while (counter<50){		//#ToDo: Abbruchbed. einsetzen

	double curPos[3];
	curPos[0] = currentPos.GetX();
	curPos[1] = currentPos.GetY();
	curPos[2] = currentPos.GetZ();
	pointID = pointLocator->FindClosestPoint(curPos);
	//Perform step
	currentPos = addVec(currentPos,multiplyVec(currentDir.Normalized(), stepSize));

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


	/////////////////////////////////////////
	

	*/



	vtkSmartPointer<vtkImageResample> resample = vtkSmartPointer<vtkImageResample>::New();
	if (reductionFactor < 1.0)
	{
		resample->SetInputConnection(reader->GetOutputPort());
		resample->SetAxisMagnificationFactor(0, reductionFactor);
		resample->SetAxisMagnificationFactor(1, reductionFactor);
		resample->SetAxisMagnificationFactor(2, reductionFactor);
	}

	// Create our volume and mapper
	vtkSmartPointer<vtkVolume> volume = vtkSmartPointer<vtkVolume>::New();
	vtkSmartPointer<vtkSmartVolumeMapper> mapper = vtkSmartPointer<vtkSmartVolumeMapper>::New();


	// Add a box widget if the clip option was selected


	vc->BoxViewSpecifier(reader->GetOutputPort(), mapper, volume);
	vc->ImagePlaneViewSpecifier(reader->GetOutputPort(),dim);

	conn->addBoxView(window1);
	conn->addImagePlaneView(window1);
	window1->deactivateView();
	if (window1->getViewMode()==BOX)
	{
		
		view1 = vc->createBoxView();
		
		window1->setView(view1);
	}

	// Add a Imageplane widget if the imageplane option was selected
	if (window1->getViewMode() == IMAGEPLANE)
	{
		view1 = vc->createImagePlaneView();
		window1->setView(view1);
	}

	if (reductionFactor < 1.0)
	{
		mapper->SetInputConnection(resample->GetOutputPort());
	}
	else
	{
		mapper->SetInputConnection(reader->GetOutputPort());
	}


	// Set the sample distance on the ray to be 1/2 the average spacing
	double spacing[3];
	if (reductionFactor < 1.0)
	{
		resample->GetOutput()->GetSpacing(spacing);
	}
	else
	{
		input->GetSpacing(spacing);
	}

	//  mapper->SetSampleDistance( (spacing[0]+spacing[1]+spacing[2])/6.0 );
	//  mapper->SetMaximumImageSampleDistance(10.0);


	// Create our transfer function
	vtkSmartPointer<vtkColorTransferFunction> colorFun = vtkSmartPointer<vtkColorTransferFunction>::New();
	vtkSmartPointer<vtkPiecewiseFunction> opacityFun = vtkSmartPointer<vtkPiecewiseFunction>::New();

	// Create the property and attach the transfer functions
	vtkSmartPointer<vtkVolumeProperty> property = vtkSmartPointer<vtkVolumeProperty>::New();
	property->SetIndependentComponents(independentComponents);
	property->SetColor(colorFun);
	property->SetScalarOpacity(opacityFun);
	property->SetInterpolationTypeToLinear();

	// connect up the volume to the property and the mapper
	volume->SetProperty(property);
	volume->SetMapper(mapper);

	// Depending on the blend type selected as a command line option,
	// adjust the transfer function
	switch (blendType)
	{
		// MIP
		// Create an opacity ramp from the window and level values.
		// Color is white. Blending is MIP.
	case 0:
		colorFun->AddRGBSegment(0.0, 1.0, 1.0, 1.0, 255.0, 1.0, 1.0, 1.0);
		opacityFun->AddSegment(opacityLevel - 0.5*opacityWindow, 0.0,
			opacityLevel + 0.5*opacityWindow, 1.0);
		mapper->SetBlendModeToMaximumIntensity();
		break;

		// CompositeRamp
		// Create a ramp from the window and level values. Use compositing
		// without shading. Color is a ramp from black to white.
	case 1:
		colorFun->AddRGBSegment(opacityLevel - 0.5*opacityWindow, 0.0, 0.0, 0.0,
			opacityLevel + 0.5*opacityWindow, 1.0, 1.0, 1.0);
		opacityFun->AddSegment(opacityLevel - 0.5*opacityWindow, 0.0,
			opacityLevel + 0.5*opacityWindow, 1.0);
		mapper->SetBlendModeToComposite();
		property->ShadeOff();
		break;

		// CompositeShadeRamp
		// Create a ramp from the window and level values. Use compositing
		// with shading. Color is white.
	case 2:
		colorFun->AddRGBSegment(0.0, 1.0, 1.0, 1.0, 255.0, 1.0, 1.0, 1.0);
		opacityFun->AddSegment(opacityLevel - 0.5*opacityWindow, 0.0,
			opacityLevel + 0.5*opacityWindow, 1.0);
		mapper->SetBlendModeToComposite();
		property->ShadeOn();
		break;


		// RGB_Composite
		// Use compositing and functions set to highlight red/green/blue regions
		// in RGB data. Not for use on single component data
	case 6:
		opacityFun->AddPoint(0, 0.0);
		opacityFun->AddPoint(5.0, 0.0);
		opacityFun->AddPoint(30.0, 0.05);
		opacityFun->AddPoint(31.0, 0.0);
		opacityFun->AddPoint(90.0, 0.0);
		opacityFun->AddPoint(100.0, 0.3);
		opacityFun->AddPoint(110.0, 0.0);
		opacityFun->AddPoint(190.0, 0.0);
		opacityFun->AddPoint(200.0, 0.4);
		opacityFun->AddPoint(210.0, 0.0);
		opacityFun->AddPoint(245.0, 0.0);
		opacityFun->AddPoint(255.0, 0.5);

		mapper->SetBlendModeToComposite();
		property->ShadeOff();
		property->SetScalarOpacityUnitDistance(1.0);
		break;
	default:
		vtkGenericWarningMacro("Unknown blend type.");
		break;
	}

	window1->render();

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
