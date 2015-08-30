/*	SelectionBox.h
*
*		In Fibertracking seed points are mostly set in a region of interest (ROI).
*		This class provides a BoxWidget which can be dragged around in the renderer/GUI.
*		It functions as the ROI and sends its position and size to the FiberTracker 
*		to select the VOI for tracking.
*
*		Rotation is disabled, as well as the Handles which can be used for scaling were disabled
*		because they occluded the box in most cases.
*		This leaves Scaling in all 3 directions simultaneously with Right-Mouse and 
*		Translation with Middle-Mouse.
*
*	Fabian
*/

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
