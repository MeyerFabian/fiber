#include "TensorComputations.h"
using namespace std;


TensorComputations::TensorComputations()
{
}


TensorComputations::~TensorComputations()
{
}

vtkDenseArray<double>* TensorComputations::GetTensorsFromNIFTI(vtkSmartPointer<vtkNIFTIImageReader> &niftiReader, int dim[]){

	niftiReader->Update();

	//#Valle: Read out tensor data
	vtkDataArray *tensors = niftiReader->GetOutput()->GetPointData()->GetScalars();
	vtkImageData *imgData = niftiReader->GetOutput();

	const int numberOfCells = niftiReader->GetOutput()->GetNumberOfCells();

	//vector<vector<double> > tensorArray = make_2DimVector<double>(numberOfCells, 9);
	vtkDenseArray<double> *tensorArray = vtkDenseArray<double>::New();
	tensorArray->Resize(numberOfCells, 9);

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
				vtkIdType pointId = imgData->ComputeCellId(ijk);

				double tensor[9];
				tensors->GetTuple(pointId, tensor);

				int localCounter = 0;

				for each (double tensorValue in tensor)
				{
					tensorArray->SetValue(globalCounter,localCounter,tensorValue);
					localCounter++;
				}

				globalCounter++;
			}
		}
	}

	return tensorArray;
}

/*
template<typename T>
void resize2DimVector(vector< vector<T> > & vec, size_t FirstDim, size_t SecDim)
{
	vec.resize(FirstDim);
	for (size_t i = 0; i < FirstDim; ++i)
		vec[i].resize(SecDim);
}


template<typename T>
const vector< vector<T> > make_2DimVector(size_t FirstDim, size_t SecDim)
{
	vector< vector<T> > vec;
	resize2DimVector(vec, FirstDim, SecDim);
	return vec;
}


template<typename T>
void resize3DimVector(vector< vector< vector<T> > > & vec, size_t FirstDim, size_t SecDim, size_t ThirdDim)
{
	vec.resize(FirstDim);
	for (size_t i = 0; i < FirstDim; ++i)
	{
		vec[i].resize(SecDim);
		for (size_t j = 0; j < SecDim; ++j)
			vec[i][j].resize(ThirdDim);
	}
}


template<typename T>
const vector< vector< vector<T> > > make_3DimVector(size_t FirstDim, size_t SecDim, size_t ThirdDim)
{
	vector< vector< vector<T> > > vec;
	resize3DimVector(vec, FirstDim, SecDim, ThirdDim);
	return vec;
}
*/
