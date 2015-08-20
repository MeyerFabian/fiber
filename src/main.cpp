
#include <QMainWindow>
#include "GUI/ui_mainwindow.h"
/*=========================================================================

  Program:   Visualization Toolkit
  Module:    GPURenderDemo.cxx

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// VTK includes

#include "vtkBoxWidget.h"
#include "vtkCamera.h"
#include "vtkCommand.h"
#include "vtkColorTransferFunction.h"
#include "vtkDICOMImageReader.h"
#include "vtkImageData.h"
#include "vtkImageResample.h"
#include "vtkMetaImageReader.h"
#include "vtkPiecewiseFunction.h"
#include "vtkPlanes.h"
#include "vtkProperty.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkVolume.h"
#include "vtkVolumeProperty.h"
#include "vtkXMLImageDataReader.h"
#include "vtkSmartVolumeMapper.h"
#include "vtkNIFTIImageReader.h"
#include "vtkSmartPointer.h"
#include "vtkImagePlaneWidget.h"
#include "vtkInteractorStyleUser.h"
#include "vtkPointData.h"
#include "vtkDoubleArray.h"
#include "vtkCellData.h"

#include <QVTKWidget.h>
#include "Rendering/QVTKWrapper.h"
#include "Rendering/ImagePlaneView.h"
#include "Rendering/BoxView.h"

#define VTI_FILETYPE 1
#define MHA_FILETYPE 2
#define NIFTI_FILETYPE 3

void PrintUsage()
{
  cout << "Usage: " << endl;
  cout << endl;
  cout << "  GPURenderDemo <options>" << endl;
  cout << endl;
  cout << "where options may include: " << endl;
  cout << endl;
  cout << "  -NIFTI <filename>" << endl;
  cout << "  -DependentComponents" << endl;
  cout << "  -MIP <window> <level>" << endl;
  cout << "  -CompositeRamp <window> <level>" << endl;
  cout << "  -CompositeShadeRamp <window> <level>" << endl;
  cout << "  -FrameRate <rate>" << endl;
  cout << "  -DataReduction <factor>" << endl;
  cout << endl;
  cout << "the data is located or the -NIFTI option to specify the path of a .nii or .nii.gz file." << endl;
  cout << endl;
  cout << "By default, the program assumes that the file has independent components," << endl;
  cout << "use -DependentComponents to specify that the file has dependent components." << endl;
  cout << endl;
  cout << "Use the -Imageplane option to display an ImagePlaneView of the volume." << endl;
  cout << "Use the -FrameRate option with a desired frame rate (in frames per second)" << endl;
  cout << "which will control the interactive rendering rate." << endl;
  cout << "Use the -DataReduction option with a reduction factor (greater than zero and" << endl;
  cout << "less than one) to reduce the data before rendering." << endl;
  cout << "Use one of the remaining options to specify the blend function" << endl;
  cout << "and transfer functions. The -MIP option utilizes a maximum intensity" << endl;
  cout << "projection method, while the others utilize compositing. The" << endl;
  cout << "-CompositeRamp option is unshaded compositing, while the other" << endl;
  cout << "compositing options employ shading." << endl;
  cout << endl;
  cout << "Note: MIP, CompositeRamp, CompositeShadeRamp" << endl;
  cout << "MIP, CompositeRamp," << endl;
  cout << "and RGB_Composite are appropriate for RGB data." << endl;
  cout << endl;
  cout << "Example: fiber -NIFTI datasets/dti30/dti30.nii -MIP 4096 1024" << endl;
  cout << endl;
  int i = 0;
  cin >> i;
}




int main(int argc, char *argv[])
{
      QApplication a(argc, argv);

      QMainWindow mainWindow;
      Ui::MainWindow* uimw = new Ui::MainWindow();
      uimw->setupUi(&mainWindow);

      QVTKWrapper* window1 = new QVTKWrapper(uimw->qvtkwidget);
      // Parse the parameters

      int count = 1;
      char *dirname = NULL;
      double opacityWindow = 4096;
      double opacityLevel = 2048;
      int blendType = 0;
      int clip = 0;
      double reductionFactor = 1.0;
      double frameRate = 10.0;
      char *fileName=0;
      int fileType=0;
      int imageplane=0;

      bool independentComponents=true;

      while ( count < argc )
        {
        if ( !strcmp( argv[count], "?" ) )
          {
          PrintUsage();
          exit(EXIT_SUCCESS);
          }

          else if ( !strcmp( argv[count], "-NIFTI" ) )
            {
            fileName = new char[strlen(argv[count+1])+1];
            fileType = NIFTI_FILETYPE;
            sprintf( fileName, "%s", argv[count+1] );
            count += 2;
            }
        else if ( !strcmp( argv[count], "-Clip") )
          {
          clip = 1;
          count++;
          }
          else if ( !strcmp( argv[count], "-Imageplane") )
            {
          imageplane = 1;
            count++;
            }
        else if ( !strcmp( argv[count], "-MIP" ) )
          {
          opacityWindow = atof( argv[count+1] );
          opacityLevel  = atof( argv[count+2] );
          blendType = 0;
          count += 3;
          }
        else if ( !strcmp( argv[count], "-CompositeRamp" ) )
          {
          opacityWindow = atof( argv[count+1] );
          opacityLevel  = atof( argv[count+2] );
          blendType = 1;
          count += 3;
          }
        else if ( !strcmp( argv[count], "-CompositeShadeRamp" ) )
          {
          opacityWindow = atof( argv[count+1] );
          opacityLevel  = atof( argv[count+2] );
          blendType = 2;
          count += 3;
          }
        else if ( !strcmp( argv[count], "-RGB_Composite" ) )
          {
          blendType = 6;
          count += 1;
          }
        else if ( !strcmp( argv[count], "-FrameRate") )
          {
          frameRate = atof( argv[count+1] );
          if ( frameRate < 0.01 || frameRate > 60.0 )
            {
            cout << "Invalid frame rate - use a number between 0.01 and 60.0" << endl;
            cout << "Using default frame rate of 10 frames per second." << endl;
            frameRate = 10.0;
            }
          count += 2;
          }
        else if ( !strcmp( argv[count], "-ReductionFactor") )
          {
          reductionFactor = atof( argv[count+1] );
          if ( reductionFactor <= 0.0 || reductionFactor >= 1.0 )
            {
            cout << "Invalid reduction factor - use a number between 0 and 1 (exclusive)" << endl;
            cout << "Using the default of no reduction." << endl;
            reductionFactor = 1.0;
            }
          count += 2;
          }
         else if ( !strcmp( argv[count], "-DependentComponents") )
          {
          independentComponents=false;
          count += 1;
          }
        else
          {
          cout << "Unrecognized option: " << argv[count] << endl;
          cout << endl;
          PrintUsage();
          exit(EXIT_FAILURE);
          }
        }

      if ( !dirname && !fileName)
        {
        cout << "Error: you must specify a directory of DICOM data or a .vti file or a .mha!" << endl;
        cout << endl;
        PrintUsage();
        exit(EXIT_FAILURE);
        }

      // Read the data
      vtkSmartPointer<vtkAlgorithm> reader=0;
      vtkSmartPointer<vtkImageData> input=0;
      if ( fileType == NIFTI_FILETYPE ){
          vtkSmartPointer<vtkNIFTIImageReader> niftreader = vtkSmartPointer<vtkNIFTIImageReader>::New();
          niftreader->SetFileName(fileName);
          niftreader->Update();

		  std::cout << "File dimension: " << niftreader->GetFileDimensionality() << std::endl;
          input=niftreader->GetOutput();

          reader=niftreader;
        }
      else
        {
        cout << "Error! Not NII!" << endl;
        exit(EXIT_FAILURE);
        }
	  int dim[3];
	  input->GetDimensions(dim);

	  std::cout << "Dims: " << " x: " << dim[0] << " y: " << dim[1] << " z: " << dim[2] << std::endl;
	  std::cout << "Number of points: " << input->GetNumberOfPoints() << std::endl;
	  std::cout << "Number of cells: " << input->GetNumberOfCells() << std::endl;

	  
      std::cout << "Data dimension: " << input->GetDataDimension()<<std::endl;
	  
	  vtkFieldData* fielddata = input->GetFieldData();
	  int fc = fielddata->GetNumberOfComponents();
	  std::cout << "Number of Components(fielddata): " << fc << endl;
	  int ft = fielddata->GetNumberOfTuples();
	  std::cout << "Number of Tuples(fielddata): " << ft << endl;

	  vtkPointData* pointdata = input->GetPointData();
	  int pc = pointdata->GetNumberOfComponents();
	  std::cout << "Number of Components(pointdata): " << pc << endl;
	  int pt = pointdata->GetNumberOfTuples();
	  std::cout << "Number of Tuples(pointdata): " << pt << endl;

	  vtkDataArray* dataarray = pointdata->GetArray(0);
	  int dc = dataarray->GetNumberOfComponents();
	  std::cout << "Number of Components(dataarray): " << dc << endl;
	  int dt = dataarray->GetNumberOfTuples();
	  std::cout << "Number of Tuples(dataarray): " << dt << endl;

	  vtkCellData* celldata = input->GetCellData();
	  int cc = celldata->GetNumberOfComponents();
	  std::cout << "Number of Components(dataarray): " << cc << endl;
	  int ct = celldata->GetNumberOfTuples();
	  std::cout << "Number of Tuples(dataarray): " << ct << endl;

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
				  vtkIdType pointId = input->ComputePointId(ijk);

				  double* tensor = dataarray->GetTuple(pointId);
				  cout << *(tensor)<<endl;
				  //vtkSmartPointer<vtkCell> currentCell = vtkSmartPointer<vtkCell>::New();
				  //currentCell = input->GetCell(currentCellId);

			  }
		  }
      }
	  //vtkDoubleArray* tensors = reinterpret_cast<vtkDoubleArray *>( pointdata->GetNumberOfArrays());
	  //vtkIdType idtype = tensors->GetNumberOfComponents();
	  //std::cout << idtype;
	  //std::cout << tensors->GetNumberOfTuples();
      /*
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
				  vtkIdType currentCellId = input->ComputeCellId(ijk);

				  //vtkSmartPointer<vtkCell> currentCell = vtkSmartPointer<vtkCell>::New();


				  double cellVector[4];

				  input->GetPoint(currentCellId, cellVector);
				  std::cout << cellVector[3] << endl;// << cellVector[1] << cellVector[2] << std::endl;
			  }
		  }
	  }
      */
	  ///////////#Valle


      // Verify that we actually have a volume

      if ( dim[0] < 2 ||
           dim[1] < 2 ||
           dim[2] < 2 )
        {
        cout << "Error loading data!" << endl;
        exit(EXIT_FAILURE);
        }

      vtkSmartPointer<vtkImageResample> resample = vtkSmartPointer<vtkImageResample>::New();
      if ( reductionFactor < 1.0 )
        {
        resample->SetInputConnection( reader->GetOutputPort() );
        resample->SetAxisMagnificationFactor(0, reductionFactor);
        resample->SetAxisMagnificationFactor(1, reductionFactor);
        resample->SetAxisMagnificationFactor(2, reductionFactor);
        }

      // Create our volume and mapper
      vtkSmartPointer<vtkVolume> volume = vtkSmartPointer<vtkVolume>::New();
      vtkSmartPointer<vtkSmartVolumeMapper> mapper = vtkSmartPointer<vtkSmartVolumeMapper>::New();


	  ///////////#Valle

	  //vtkSmartPointer<vtkStructuredGrid> grid = vtkSmartPointer<vtkStructuredGrid>::New();

<<<<<<< .merge_file_a08504
	  std::cout << "Dims: " << " x: " << dim[0] << " y: " << dim[1] << " z: " << dim[2] << std::endl;
	  std::cout << "Number of points: " << input->GetNumberOfPoints() << std::endl;
	  std::cout << "Number of cells: " << input->GetNumberOfCells() << std::endl;

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
				  vtkIdType currentCellId = input->ComputeCellId(ijk);

				  //vtkSmartPointer<vtkCell> currentCell = vtkSmartPointer<vtkCell>::New();
				  //currentCell = input->GetCell(currentCellId);

				  double cellVector[3];
				  input->GetPoint(currentCellId, cellVector);
				  vtkSmartPointer<vtkPointData> pointData = vtkSmartPointer<vtkPointData>::New();
				  pointData = input->GetPointData();
				  std::cout << cellVector[0] << cellVector[1] << cellVector[2] << std::endl;
				  std::cout << "----------  New Data" << std::endl;
			  }
		  }
	  }

	  ///////////#Valle

=======
>>>>>>> .merge_file_a02312


      View* view1 =NULL;

      // Add a box widget if the clip option was selected


      if (clip)
        {
          if ( reductionFactor < 1.0 )
            {
              view1 =new BoxView(resample->GetOutputPort(),mapper,volume);
            }
          else
            {
              view1 =new BoxView(reader->GetOutputPort(),mapper,volume);
            }
              window1->setView(view1);
        }

    // Add a Imageplane widget if the imageplane option was selected
        if(imageplane)
        {
        view1 =new ImagePlaneView(reader->GetOutputPort());
            window1->setView(view1);


        }

      if ( reductionFactor < 1.0 )
        {
        mapper->SetInputConnection( resample->GetOutputPort() );
        }
      else
        {
        mapper->SetInputConnection( reader->GetOutputPort() );
        }


      // Set the sample distance on the ray to be 1/2 the average spacing
      double spacing[3];
      if ( reductionFactor < 1.0 )
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
      property->SetColor( colorFun );
      property->SetScalarOpacity( opacityFun );
      property->SetInterpolationTypeToLinear();

      // connect up the volume to the property and the mapper
      volume->SetProperty( property );
      volume->SetMapper( mapper );

      // Depending on the blend type selected as a command line option,
      // adjust the transfer function
      switch ( blendType )
        {
        // MIP
        // Create an opacity ramp from the window and level values.
        // Color is white. Blending is MIP.
        case 0:
          colorFun->AddRGBSegment(0.0, 1.0, 1.0, 1.0, 255.0, 1.0, 1.0, 1.0 );
          opacityFun->AddSegment( opacityLevel - 0.5*opacityWindow, 0.0,
                                  opacityLevel + 0.5*opacityWindow, 1.0 );
          mapper->SetBlendModeToMaximumIntensity();
          break;

        // CompositeRamp
        // Create a ramp from the window and level values. Use compositing
        // without shading. Color is a ramp from black to white.
        case 1:
          colorFun->AddRGBSegment(opacityLevel - 0.5*opacityWindow, 0.0, 0.0, 0.0,
                                  opacityLevel + 0.5*opacityWindow, 1.0, 1.0, 1.0 );
          opacityFun->AddSegment( opacityLevel - 0.5*opacityWindow, 0.0,
                                  opacityLevel + 0.5*opacityWindow, 1.0 );
          mapper->SetBlendModeToComposite();
          property->ShadeOff();
          break;

        // CompositeShadeRamp
        // Create a ramp from the window and level values. Use compositing
        // with shading. Color is white.
        case 2:
          colorFun->AddRGBSegment(0.0, 1.0, 1.0, 1.0, 255.0, 1.0, 1.0, 1.0 );
          opacityFun->AddSegment( opacityLevel - 0.5*opacityWindow, 0.0,
                                  opacityLevel + 0.5*opacityWindow, 1.0 );
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
      mainWindow.show();

     delete uimw;
     delete window1;
     delete view1;

    return a.exec();
}
