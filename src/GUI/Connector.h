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
class WindowHandler;
class Connector 
{
public:
	Connector(QMainWindow*, Ui::MainWindow* uimw);
	~Connector();
	bool addFileReader(FileMenu* fm, ImageReaderWrapper* iw);
	bool addBoxView(QVTKWrapper* qvtk);
	bool addImagePlaneView(QVTKWrapper* qvtk);
	bool addWindowHandler(ImageReaderWrapper* iw, WindowHandler* wh);
private:
	QMainWindow* window;
	Ui::MainWindow* uimw;

};

#endif // CONNECTOR_H
