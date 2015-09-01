/*	TensorComputations.h
*
*		The TensorComputations class handles the requests of the FiberTracker class.
*		For a specific dataset and pointID, the local tensor can be transferred.
*		With a 3x3 tensor, the three eigenvectors of that tensors can be computed
*		and transferred.
*
*	Valentin
*/


#ifndef TENSORCOMPUTATIONS_H
#define TENSORCOMPUTATIONS_H

#include "vtkSmartPointer.h"
#include "vtkAlgorithm.h"
#include "vtkNIFTIImageReader.h"
#include "vtkDataArray.h"
#include "vtkImageData.h"
#include "vtkPointData.h"
#include "vtkMatrix3x3.h"
//#include "vtkDoubleArray.h"
//#include "vtkDenseArray.h"
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
	// Description:
	// Get Tensor from a NIFTI image at a specific point, specified by the pointID.
	vtkSmartPointer<vtkMatrix3x3> GetTensorsFromNIFTI(vtkSmartPointer<vtkImageReader2> niftiReader, vtkIdType pointID);
	// Description:
	// Get the three eigenvectors stored in a 3x3 matrix from a second order 3x3 tensor.
	vtkSmartPointer<vtkMatrix3x3> GetEigenvectorsFromTensor(vtkSmartPointer<vtkMatrix3x3> tensor);
	~TensorComputations();
};

#endif
