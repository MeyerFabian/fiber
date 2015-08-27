
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
	QApplication a(argc, argv);

	QMainWindow mainWindow;
	Ui::MainWindow* uimw = new Ui::MainWindow();
	uimw->setupUi(&mainWindow);
	

	vtkSmartPointer<vtkNIFTIImageReader> niftreader = vtkSmartPointer<vtkNIFTIImageReader>::New();

	// Enable Filebrowsing
	Connector* conn = new Connector(&mainWindow, uimw);
	FileMenu fm = FileMenu(&mainWindow);

	// Enable the reader, which will be used to read in the file browsed
	ImageReaderWrapper* iw = new ImageReaderWrapper(niftreader);
	conn->addFileReader(&fm, iw);

	WindowHandler* wh = new WindowHandler(argc, argv, conn,uimw);
	conn->addWindowHandler(iw,wh);
	mainWindow.show();


	
	return a.exec(); 
	delete uimw;
	delete conn;
	delete iw;
}
