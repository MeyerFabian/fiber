#include "connector.h"

Connector::Connector(QMainWindow* window, Ui::MainWindow* uimw)
{
	this->window = window;
	this->uimw = uimw;

}
Connector::~Connector(){

}
// Connects FileMenu and Reader so we can use the File->Open.. to dynamically load in files
bool Connector::addFileReader(FileMenu* fm,ImageReaderWrapper* iw){
	bool q1 = QObject::connect(uimw->actionOpen, SIGNAL(triggered()), fm, SLOT(open()));
	bool q2 = QObject::connect(fm, SIGNAL(FileNameChanged(char*)), iw, SLOT(setFileName(char*)));
	return q1 && q2;
}
// Connects View->Widget->Box so we can dynamically switch to the BoxView if we want 
bool Connector::addBoxView(QVTKWrapper* qvtk){
	return QObject::connect(uimw->actionBox, SIGNAL(triggered()), qvtk, SLOT(switchToBoxView()));
}

// Connects View->Widget->ImagePlane so we can dynamically switch to the ImagePlaneView if we want 
bool Connector::addImagePlaneView(QVTKWrapper* qvtk){
	return QObject::connect(uimw->actionImageplane, SIGNAL(triggered()), qvtk, SLOT(switchToImagePlaneView()));
}
// When we load a File the windowHandler is automatically called, which foremost takes care of the views
bool Connector::addWindowHandler(ImageReaderWrapper* iw, WindowHandler* wh){
	return QObject::connect(iw, SIGNAL(initRenderer(vtkSmartPointer<vtkImageReader2>)), wh, SLOT(init(vtkSmartPointer<vtkImageReader2>)));
}

// Starts the Main-Algorithm, which is:
// 1. Add a Region of Interest (Selection Box)
// 2. Initialize the Fiber-Tracker and the Fiber-Lines
bool Connector::addMainAlgorithm(QVTKWrapper* qvtk){
	return QObject::connect(uimw->pushButton, SIGNAL(clicked()), qvtk, SLOT(addMainAlgorithm()));
}

// Enables the Selection-Box to directly signals its state(position,scale) to the Fibertracker to calculate updated Fiberpoints
bool Connector::addFiberTracker(QVTKWrapper* qvtk){
	return QObject::connect(qvtk->GetSelectionBox(), SIGNAL(SelectionBoxChanged(vtkVector3d, vtkVector3d, int)), qvtk, SLOT(Update(vtkVector3d, vtkVector3d, int)));
}
// Sends the FiberPoints calculated by the Fibertracker to the Fiber.h, which generates and displays the Fiberlines.
bool Connector::addFiberLines(QVTKWrapper* qvtk){
	return QObject::connect(qvtk->GetFiberTracker(), SIGNAL(updateFibers(std::vector<vtkSmartPointer<vtkPoints> >*)), qvtk->GetFiber(), SLOT(update(std::vector<vtkSmartPointer<vtkPoints> >*)));
}