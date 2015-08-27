#include "filemenu.h"

FileMenu::FileMenu(QMainWindow* window)
{
	this->window = window;
}
FileMenu::~FileMenu(){

}
void FileMenu::open(){
	QString string = QFileDialog::getOpenFileName(window, tr("Open File"), "","NIFTI-Image (*.nii.gz)");
	
	QByteArray array = string.toLocal8Bit();
	char* filename = array.data();
	emit FileNameChanged(filename);
}
