#include "connector.h"

Connector::Connector(QMainWindow* window, Ui::MainWindow* uimw)
{
	this->window = window;
	this->uimw = uimw;

}
Connector::~Connector(){
	for (std::vector<QObject*>::size_type i = 0; i < connectionTargets.size(); i++){
		delete connectionTargets[i];
	}
}
bool Connector::addFileMenu(FileMenu* fm){
	connectionTargets.push_back(fm);
	return QObject::connect(uimw->actionOpen, SIGNAL(triggered()), fm, SLOT(open()));
	
}