#include "filemenu.h"

FileMenu::FileMenu(QMainWindow* window)
{
	this->window = window;
}
FileMenu::~FileMenu(){

}

// Opens a dialog, where the user can only load in NIFTI-Images (cause everything else is not supported).
void FileMenu::open(){

	// Opens the dialog.
	QString string = QFileDialog::getOpenFileName(window, tr("Open File"), "","NIFTI-Image (*.nii.gz)");
	
	//Converts the QString to a char*.
	QByteArray array = string.toLocal8Bit();
	char* filename = array.data();

	//And signals the reader, where the new File is.
	emit FileNameChanged(filename);
}
