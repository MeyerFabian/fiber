#include "ImageReaderWrapper.h"

ImageReaderWrapper::ImageReaderWrapper(vtkSmartPointer<vtkImageReader2> reader)
{
	this->reader = reader;
}
ImageReaderWrapper::~ImageReaderWrapper(){

}
void ImageReaderWrapper::setFileName(char* filename){
	reader->SetFileName(filename);

	reader->Update();
	emit initRenderer(reader);
}
