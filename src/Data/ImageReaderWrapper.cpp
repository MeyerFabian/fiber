#include "ImageReaderWrapper.h"

ImageReaderWrapper::ImageReaderWrapper(vtkSmartPointer<vtkImageReader2> reader)
{
	this->reader = reader;
}
ImageReaderWrapper::~ImageReaderWrapper(){

}
// Reads in a new volume and emits a signal to the WindowHandler that we can start rendering the image.
void ImageReaderWrapper::setFileName(char* filename){
	reader->SetFileName(filename);
	reader->Update();
	emit initRenderer(reader);
}
