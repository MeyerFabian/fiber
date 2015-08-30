
#include "vtkNIFTIImageReader.h"
#include "vtkSmartPointer.h"


#include <QVTKWidget.h>
#include <QMainWindow>

#include "GUI/ui_mainwindow.h"
#include "GUI/Connector.h"

#include "Data/ImageReaderWrapper.h"

#include "WindowHandler.h"

int main(int argc, char *argv[])
{
	// Set up a QApplication to use Qt in the background.
	QApplication a(argc, argv);

	// Setup the QTGui and Window specified in the ui_mainwindow.h
	// The header ui_mainwindow.h is generated with the command:
	// uic Mainwindow.ui > ui_mainwindow.h 
	// where Mainwindow.ui can be read in with QtDesigner or QtCreator
	// to create a GUI.
	QMainWindow mainWindow;
	Ui::MainWindow* uimw = new Ui::MainWindow();
	uimw->setupUi(&mainWindow);
	
	//Initialize the Reader we want to use, here NIFTI.
	vtkSmartPointer<vtkNIFTIImageReader> niftreader = vtkSmartPointer<vtkNIFTIImageReader>::New();

	// Enable Filebrowsing
	Connector* conn = new Connector(&mainWindow, uimw);
	FileMenu fm = FileMenu(&mainWindow);

	// Enable the reader, which will be used to read in the file browsed
	ImageReaderWrapper* iw = new ImageReaderWrapper(niftreader);
	conn->addFileReader(&fm, iw);

	// Enable the windowHandler, which initializes the properties(volume,widgets) when opening a file
	WindowHandler* wh = new WindowHandler(argc, argv, conn,uimw);
	conn->addWindowHandler(iw,wh);

	// Create a window to show the GUI (VTKs window is not rendered yet)
	mainWindow.show();


	
	return a.exec(); 
	delete uimw;
	delete conn;
	delete iw;
}
