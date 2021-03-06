/*	Fiber.h
*
*		To visualize Fibers this class provides methods to create Fiberlines from the points,
*		which are calculated by the Fibertracker and renders them to the window. Essentially 
*		updates should be called whenever a parameter changes. 
*		(e.g. SelectionBox moves, more seedpoints etc.)
*
*	Fabian
*/

#ifndef FIBER_H
#define FIBER_H
#include "vtkSmartPointer.h"
#include "vtkRenderer.h"
#include "vtkRenderWindowInteractor.h"
#include <qobject.h>
#include "vtkPoints.h"
#include <vector>
#include "vtkPolyLine.h"
#include "vtkCellArray.h"
#include "vtkPolyData.h"
#include "vtkPolyDataMapper.h"
class Fiber : public QObject 
{
	Q_OBJECT
public:
	Fiber(vtkSmartPointer<vtkRenderer> renderer);
	~Fiber();


public:    
	void activate();
	void deactivate();
public slots:
void update(std::vector<vtkSmartPointer<vtkPoints> >*);
private:
	std::vector< vtkSmartPointer<vtkActor>> actors;
	vtkSmartPointer<vtkRenderer> renderer;
	
};

#endif // FIBER_H
