#include "connector.h"

Connector::Connector(QMainWindow* window, Ui::MainWindow* uimw)
{
	this->window = window;
	this->uimw = uimw;

}
Connector::~Connector(){

}
bool Connector::addFileMenu(FileMenu* fm){
	return QObject::connect(uimw->actionOpen, SIGNAL(triggered()), fm, SLOT(open()));
	
}

bool Connector::addBoxView(QVTKWrapper* qvtk){
	return QObject::connect(uimw->actionBox, SIGNAL(triggered()), qvtk, SLOT(switchToBoxView()));
}

bool Connector::addImagePlaneView(QVTKWrapper* qvtk){
	return QObject::connect(uimw->actionImageplane, SIGNAL(triggered()), qvtk, SLOT(switchToImagePlaneView()));

}