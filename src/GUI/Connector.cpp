#include "connector.h"

Connector::Connector(QMainWindow* window, Ui::MainWindow* uimw)
{
	this->window = window;
	this->uimw = uimw;

}
Connector::~Connector(){

}
bool Connector::addFileReader(FileMenu* fm,ImageReaderWrapper* iw){
	bool q1 = QObject::connect(uimw->actionOpen, SIGNAL(triggered()), fm, SLOT(open()));
	bool q2 = QObject::connect(fm, SIGNAL(FileNameChanged(char*)), iw, SLOT(setFileName(char*)));
	return q1 && q2;
}

bool Connector::addBoxView(QVTKWrapper* qvtk){
	return QObject::connect(uimw->actionBox, SIGNAL(triggered()), qvtk, SLOT(switchToBoxView()));
}

bool Connector::addImagePlaneView(QVTKWrapper* qvtk){
	return QObject::connect(uimw->actionImageplane, SIGNAL(triggered()), qvtk, SLOT(switchToImagePlaneView()));
}
bool Connector::addWindowHandler(ImageReaderWrapper* iw, WindowHandler* wh){
	return QObject::connect(iw, SIGNAL(initRenderer(vtkSmartPointer<vtkImageReader2>)), wh, SLOT(init(vtkSmartPointer<vtkImageReader2>)));
}
bool Connector::addSelectionBox(QVTKWrapper* qvtk){
	return QObject::connect(uimw->pushButton, SIGNAL(clicked()), qvtk, SLOT(addSelectionBox()));
}

bool Connector::addFiberTracker(QVTKWrapper* qvtk){
	return QObject::connect(qvtk->GetSelectionBox(), SIGNAL(SelectionBoxChanged(vtkVector3d, vtkVector3d, int)), qvtk, SLOT(Update(vtkVector3d, vtkVector3d, int)));
}