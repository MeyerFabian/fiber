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
	window1 = new QVTKWrapper(uimw->qvtkwidget, vc,conn);
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

	// Passing through the image data to the FiberTracker class
	window1->SetImageReader(reader);

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
	conn->addMainAlgorithm(window1);
	window1->deactivateView();


	if (window1->getViewMode() == BOX)
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


