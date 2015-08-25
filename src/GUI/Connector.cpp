#include "connector.h"

Connector::Connector(QMainWindow* window, Ui::MainWindow* uimw)
{
	this->window = window;
	this->uimw = uimw;

}
Connector::~Connector(){
	for (int i = 0; i < connectionTargets.size(); i++){
		delete connectionTargets[i];
	}
}
bool Connector::addFileMenu(){
	FileMenu* fm = new FileMenu(window);
	connectionTargets.push_back(fm);
	return QObject::connect(uimw->actionOpen, SIGNAL(triggered()), fm, SLOT(open()));
	
}