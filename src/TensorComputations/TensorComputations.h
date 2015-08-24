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

class TensorComputations
{
public:
	TensorComputations();
    vtkSmartPointer<vtkDenseArray<double> > GetTensorsFromNIFTI(vtkSmartPointer<vtkNIFTIImageReader> niftiReader, int dim[]);
	~TensorComputations();
};

#endif // BOXVIEW_H
