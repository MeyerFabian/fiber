/*	WindowHandler.h
*
*		Handles Initialization of the QVTKWrapper(for GUI and Rendering)
*		and the rendered properties as well.
*
*	Fabian
*/


#ifndef WINDOWHANDLER_H
#define WINDOWHANDLER_H
#include <qobject.h>


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

#include "vtkVector.h"
#include "vtkVectorDot.h"
#include "TensorComputations/TensorComputations.h"
#include "vtkPointLocator.h"

#include <QVTKWidget.h>
#include <QMainWindow>

#include "GUI/ui_mainwindow.h"
#include "GUI/Connector.h"

#include "Rendering/QVTKWrapper.h"
#include "Rendering/ImagePlaneView.h"
#include "Rendering/BoxView.h"
#include "Rendering/ViewCreator.h"

#include "Data/ImageReaderWrapper.h"
#include "Tracking/FiberTracker.h"



class Connector;
class QVTKWrapper;


class WindowHandler :public QObject
{
	Q_OBJECT
public:
	WindowHandler(int argc, char *argv[], Connector* conn, Ui::MainWindow* uimw);
	~WindowHandler();
public slots:
	void init(vtkSmartPointer<vtkImageReader2>);
private:
	Ui::MainWindow* uimw;
	Connector* conn;
	int argc;
	View* view1;
	ViewCreator* vc;
	QVTKWrapper* window1; 
	TensorComputations* tensorComp;
	char* argv[];

};

#endif // WINDOWHANDLER_H

