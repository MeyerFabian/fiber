#include "filemenu.h"

FileMenu::FileMenu(QMainWindow* window)
{
	this->window = window;
}
FileMenu::~FileMenu(){

}
void FileMenu::open(){
	QString filename = QFileDialog::getOpenFileName(window, tr("Open File"), "","NIFTI-Image (*.nii.gz)");
	QMessageBox::information(window, tr("File Name"), filename);
}
