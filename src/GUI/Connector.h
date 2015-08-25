#ifndef CONNECTOR_H
#define CONNECTOR_H
#include <qfiledialog.h>
#include <qmainwindow.h>
#include "FileMenu.h"
#include "ui_mainwindow.h"
#include <vector>
class Connector 
{
public:
	Connector(QMainWindow*, Ui::MainWindow* uimw);
	~Connector();
	bool addFileMenu();
private:
	QMainWindow* window;
	Ui::MainWindow* uimw;
	std::vector<QObject*> connectionTargets;

};

#endif // CONNECTOR_H
