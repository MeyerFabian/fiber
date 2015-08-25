#ifndef TENSORCOMPUTATIONS_H
#define TENSORCOMPUTATIONS_H

#include "vtkSmartPointer.h"
#include "vtkAlgorithm.h"
#include "vtkNIFTIImageReader.h"
#include "vtkDataArray.h"
#include "vtkImageData.h"
#include "vtkPointData.h"
#include "vtkDoubleArray.h"
#include "vtkDenseArray.h"
//#include "vtkGenericCellIterator.h"

#include <vtkVersion.h>
#include "vtkSmartPointer.h"
#include "vtkDoubleArray.h"
#include "vtkMultiBlockDataSet.h"
#include "vtkPCAStatistics.h"
#include "vtkStringArray.h"
#include "vtkTable.h"

class TensorComputations
{
public:
	TensorComputations();
    vtkSmartPointer<vtkDenseArray<double> > GetTensorsFromNIFTI(vtkSmartPointer<vtkNIFTIImageReader> niftiReader, int dim[]);
	void GetEigenvectorsFromTensor(vtkSmartPointer<vtkDenseArray<double>> tensors, vtkSmartPointer<vtkDoubleArray> *eigenvector1, vtkSmartPointer<vtkDoubleArray> *eigenvector2, vtkSmartPointer<vtkDoubleArray> *eigenvector3);
	~TensorComputations();
};

#endif
