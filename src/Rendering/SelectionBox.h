#ifndef SELECTIONBOX_H
#define SELECTIONBOX_H
#include "vtkSmartPointer.h"
#include "vtkRenderer.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkBoxWidget.h"
#include <qobject.h>
#include "vtkVector.h"
#include "vtkPolyData.h"
#include "vtkCommand.h"

class SelectionBox : public QObject 
{
	Q_OBJECT
public:
	SelectionBox();
	~SelectionBox();


public:    
	void activate(vtkSmartPointer<vtkRenderer> renderer, vtkSmartPointer<vtkRenderWindowInteractor> rendint);
	void deactivate(vtkSmartPointer<vtkRenderer> renderer);
	void update();
signals:
	void SelectionBoxChanged(vtkVector3d boxWidgetPos, vtkVector3d boxWidgetExtents, int seedPointsPerAxis);
private:
	vtkSmartPointer<vtkBoxWidget> box = vtkSmartPointer<vtkBoxWidget>::New();
	vtkVector3d boxWidgetPos;
	vtkVector3d boxWidgetExtents;
};

#endif // SELECTIONBOX_H
