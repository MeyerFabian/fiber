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
