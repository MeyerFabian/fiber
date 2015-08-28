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
#include "vtkVector.h"
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
	bool addSelectionBox(QVTKWrapper* qvtk);
	bool addFiberTracker(QVTKWrapper* qvtk);
private:
	QMainWindow* window;
	Ui::MainWindow* uimw;

};

#endif // CONNECTOR_H
