#ifndef IMAGEREADERWRAPPER_H
#define IMAGEREADERWRAPPER_H
#include <qobject.h>
#include "vtkImageReader2.h"
#include "vtkSmartPointer.h"
class ImageReaderWrapper :public QObject
{
	Q_OBJECT
public:
	ImageReaderWrapper(vtkSmartPointer<vtkImageReader2> reader);
	~ImageReaderWrapper();
public slots:
	void setFileName(char* filename);
private:
	vtkSmartPointer<vtkImageReader2> reader;
};

#endif //  IMAGEREADERWRAPPER_H
