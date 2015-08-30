/*	Connector.h
*
*		Qt uses a Signal-Slot Design Pattern to communicate between GUI and functions.
*		The Connector connects the various GUI elements and functions to signal other methods
*		that something (e.g. a parameter) has changed and the functions needs to update.
*		e.g. When switching to BoxView in the GUI a signal from the GUI-Element is sent
*		to the QVTKWrapper to switch the view.
*		to a BoxView.
*
*	Fabian
*/


#ifndef CONNECTOR_H
#define CONNECTOR_H
#include <qfiledialog.h>
#include <qmainwindow.h>
#include "FileMenu.h"
#include "ui_mainwindow.h"
#include "../Data/ImageReaderWrapper.h"
#include <vector>
#include "../Rendering/QVTKWrapper.h"
#include "../WindowHandler.h"
#include "vtkPoints.h"
#include "../Tracking/FiberTracker.h"
#include "../Rendering/SelectionBox.h"
class WindowHandler;
class QVTKWrapper;
class Connector 
{
public:
	Connector(QMainWindow*, Ui::MainWindow* uimw);
	~Connector();
	bool addFileReader(FileMenu* fm, ImageReaderWrapper* iw);
	bool addBoxView(QVTKWrapper* qvtk);
	bool addImagePlaneView(QVTKWrapper* qvtk);
	bool addWindowHandler(ImageReaderWrapper* iw, WindowHandler* wh);
	bool addMainAlgorithm(QVTKWrapper* qvtk);
	bool addFiberTracker(QVTKWrapper* qvtk);
	bool addFiberLines(QVTKWrapper* qvtk);
private:
	QMainWindow* window;
	Ui::MainWindow* uimw;

};

#endif // CONNECTOR_H
