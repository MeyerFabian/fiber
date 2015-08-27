#ifndef CONNECTOR_H
#define CONNECTOR_H
#include <qfiledialog.h>
#include <qmainwindow.h>
#include "FileMenu.h"
#include "ui_mainwindow.h"
#include "../Data/ImageReaderWrapper.h"
#include <vector>
#include "../Rendering/QVTKWrapper.h"
class Connector 
{
public:
	Connector(QMainWindow*, Ui::MainWindow* uimw);
	~Connector();
	bool addFileReader(FileMenu* fm, ImageReaderWrapper* iw);
	bool addBoxView(QVTKWrapper* qvtk);
	bool addImagePlaneView(QVTKWrapper* qvtk);

private:
	QMainWindow* window;
	Ui::MainWindow* uimw;

};

#endif // CONNECTOR_H
