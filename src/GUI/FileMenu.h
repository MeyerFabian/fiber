/*	FileMenu.h
*
*		Whenever we use the File->Open.. Action in the GUI a FileDialog occurs to open a NIFTI file.
*		This class takes care of opening the Dialog, selecting the file and 
*		handing it over to the reader.
*
*	Fabian
*/
#ifndef FILEMENU_H
#define FILEMENU_H
#include <qobject.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qmainwindow.h>
class FileMenu :public QObject
{
	Q_OBJECT
public:
	FileMenu(QMainWindow*);
	~FileMenu();
public slots:
	void open();
signals:
	void FileNameChanged(char*);
private:
	QMainWindow* window;
};

#endif // FILEMENU_H
