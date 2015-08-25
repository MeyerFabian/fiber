#include "TensorComputations.h"
using namespace std;


TensorComputations::TensorComputations()
{
}


TensorComputations::~TensorComputations()
{
}

vtkSmartPointer<vtkDenseArray<double> > TensorComputations::GetTensorsFromNIFTI(vtkSmartPointer<vtkNIFTIImageReader> niftiReader, int dim[]){

	niftiReader->Update();

	//#Valle: Read out tensor data
	vtkSmartPointer<vtkDataArray> tensors = niftiReader->GetOutput()->GetPointData()->GetScalars();
	vtkSmartPointer<vtkImageData> imgData = niftiReader->GetOutput();

	const int numberOfPoints = niftiReader->GetOutput()->GetPointData()->GetNumberOfTuples();

	//vector<vector<double> > tensorArray = make_2DimVector<double>(numberOfCells, 9);
	vtkSmartPointer<vtkDenseArray<double> > tensorArray = vtkSmartPointer<vtkDenseArray<double> >::New();
	tensorArray->Resize(numberOfPoints, 9);

	int globalCounter = 0;

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
				vtkIdType pointId = imgData->ComputeCellId(ijk);	//korrekte Methode?

				double tensor[9];
				tensors->GetTuple(pointId, tensor);

				int localCounter = 0;

				for (int i = 0; i < 9; i++)
				{
					// line doesnt work
					tensorArray->SetValue(globalCounter, localCounter, tensor[i]);
					localCounter++;
				}

				globalCounter++;
			}
		}
	}

	/*vtkGenericDataSet *dataset;
	vtkGenericCellIterator *it = dataset->NewCellIterator(2);
	for (it->Begin(); !it->IsAtEnd(); it->Next());
	{
	spec = it->GetCell();
	}

	cout << dim[0] << " " << dim[1] << " " << dim[2] << endl;
	cout << globalCounter << endl;*/

	return tensorArray;
}



void GetEigenvectorsFromTensor(vtkSmartPointer<vtkDenseArray<double>> tensors, vtkSmartPointer<vtkDoubleArray> *eigenvector1, vtkSmartPointer<vtkDoubleArray> *eigenvector2, vtkSmartPointer<vtkDoubleArray> *eigenvector3)
{
	// Each one of these arrays is a single component of
	// the data. That is, if you have 3D spatial data (x,y,z)
	// you need to construct an array of all the x values,
	// an array of all the y values, and an array of all the
	// z values.

	// Construct a data set of 3 3D points.

	// These would be all of your "x" values.
	const char m0Name[] = "M0";
	vtkSmartPointer<vtkDoubleArray> dataset1Arr = vtkSmartPointer<vtkDoubleArray>::New();
	dataset1Arr->SetNumberOfComponents(1);
	dataset1Arr->SetName(m0Name);
	dataset1Arr->InsertNextValue(0);
	dataset1Arr->InsertNextValue(1);
	dataset1Arr->InsertNextValue(0);

	tensors->GetValue(1, 0);

	// These would be all of your "y" values.
	const char m1Name[] = "M1";
	vtkSmartPointer<vtkDoubleArray> dataset2Arr = vtkSmartPointer<vtkDoubleArray>::New();
	dataset2Arr->SetNumberOfComponents(1);
	dataset2Arr->SetName(m1Name);
	dataset2Arr->InsertNextValue(0);
	dataset2Arr->InsertNextValue(0);
	dataset2Arr->InsertNextValue(1);

	// These would be all of your "z" values.
	const char m2Name[] = "M2";
	vtkSmartPointer<vtkDoubleArray> dataset3Arr = vtkSmartPointer<vtkDoubleArray>::New();
	dataset3Arr->SetNumberOfComponents(1);
	dataset3Arr->SetName(m2Name);
	dataset3Arr->InsertNextValue(0);
	dataset3Arr->InsertNextValue(0);
	dataset3Arr->InsertNextValue(0);

	vtkSmartPointer<vtkTable> datasetTable = vtkSmartPointer<vtkTable>::New();
	datasetTable->AddColumn(dataset1Arr);
	datasetTable->AddColumn(dataset2Arr);
	datasetTable->AddColumn(dataset3Arr);

	vtkSmartPointer<vtkPCAStatistics> pcaStatistics =
		vtkSmartPointer<vtkPCAStatistics>::New();
#if VTK_MAJOR_VERSION <= 5
	pcaStatistics->SetInput(vtkStatisticsAlgorithm::INPUT_DATA, datasetTable);
#else
	pcaStatistics->SetInputData(vtkStatisticsAlgorithm::INPUT_DATA, datasetTable);
#endif

	pcaStatistics->SetColumnStatus("M0", 1);
	pcaStatistics->SetColumnStatus("M1", 1);
	pcaStatistics->SetColumnStatus("M2", 1);
	pcaStatistics->RequestSelectedColumns();
	pcaStatistics->SetDeriveOption(true);
	pcaStatistics->Update();

	///////// Eigenvalues ////////////
	vtkSmartPointer<vtkDoubleArray> eigenvalues =
		vtkSmartPointer<vtkDoubleArray>::New();
	pcaStatistics->GetEigenvalues(eigenvalues);
	//  double eigenvaluesGroundTruth[3] = {.5, .166667, 0};
	for (vtkIdType i = 0; i < eigenvalues->GetNumberOfTuples(); i++)
	{
		std::cout << "Eigenvalue " << i << " = " << eigenvalues->GetValue(i) << std::endl;
	}

	///////// Eigenvectors ////////////
	vtkSmartPointer<vtkDoubleArray> eigenvectors =
		vtkSmartPointer<vtkDoubleArray>::New();

	pcaStatistics->GetEigenvectors(eigenvectors);
	for (vtkIdType i = 0; i < eigenvectors->GetNumberOfTuples(); i++)
	{
		std::cout << "Eigenvector " << i << " : ";
		double* evec = new double[eigenvectors->GetNumberOfComponents()];
		eigenvectors->GetTuple(i, evec);
		for (vtkIdType j = 0; j < eigenvectors->GetNumberOfComponents(); j++)
		{
			std::cout << evec[j] << " ";
			vtkSmartPointer<vtkDoubleArray> eigenvectorSingle =
				vtkSmartPointer<vtkDoubleArray>::New();
			pcaStatistics->GetEigenvector(i, eigenvectorSingle);
		}
		delete evec;
		std::cout << std::endl;
	}

}
