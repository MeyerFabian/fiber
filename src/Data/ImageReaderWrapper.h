/*	ImageReaderWrapper.h
*
*		Holds the reader which is used to read in files and signals the WindowHandler to begin
*		with Rendering, when a file was read in.
*
*	Fabian
*/

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
signals:
	void initRenderer(vtkSmartPointer<vtkImageReader2> reader);
private:
	vtkSmartPointer<vtkImageReader2> reader;
};

#endif //  IMAGEREADERWRAPPER_H
