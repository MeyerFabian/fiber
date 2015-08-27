
/*=========================================================================

Program:   Visualization Toolkit
Module:    GPURenderDemo.cxx

Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
All rights reserved.
See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notice for more information.

=========================================================================*/



#ifndef WINDOWHANDLER_H
#define WINDOWHANDLER_H
#include <qobject.h>


#include "vtkBoxWidget.h"
#include "vtkCamera.h"
#include "vtkCommand.h"
#include "vtkColorTransferFunction.h"
#include "vtkDICOMImageReader.h"
#include "vtkImageData.h"
#include "vtkImageResample.h"
#include "vtkMetaImageReader.h"
#include "vtkPiecewiseFunction.h"
#include "vtkPlanes.h"
#include "vtkProperty.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkVolume.h"
#include "vtkVolumeProperty.h"
#include "vtkXMLImageDataReader.h"
#include "vtkSmartVolumeMapper.h"
#include "vtkNIFTIImageReader.h"
#include "vtkSmartPointer.h"
#include "vtkImagePlaneWidget.h"
#include "vtkInteractorStyleUser.h"
#include "vtkPointData.h"
#include "vtkDoubleArray.h"
#include "vtkCellData.h"

#include "vtkVector.h"
#include "vtkVectorDot.h"
#include "TensorComputations/TensorComputations.h"
#include "vtkPointLocator.h"

#include <QVTKWidget.h>
#include <QMainWindow>

#include "GUI/ui_mainwindow.h"
#include "GUI/Connector.h"

#include "Rendering/QVTKWrapper.h"
#include "Rendering/ImagePlaneView.h"
#include "Rendering/BoxView.h"
#include "Rendering/ViewCreator.h"

#include "Data/ImageReaderWrapper.h"

#define VTI_FILETYPE 1
#define MHA_FILETYPE 2
#define NIFTI_FILETYPE 3


vtkVector3d addVec(vtkVector3d vec1, vtkVector3d vec2);
vtkVector3d substractVec(vtkVector3d vec1, vtkVector3d vec2);
vtkVector3d multiplyVec(vtkVector3d vec1, double scalar);

class Connector;
class WindowHandler :public QObject
{
	Q_OBJECT
public:
	WindowHandler(int argc, char *argv[], Connector* conn, Ui::MainWindow* uimw);
	~WindowHandler();
public slots:
	void init(vtkSmartPointer<vtkImageReader2>);
private:
	Ui::MainWindow* uimw;
	Connector* conn;
	int argc;
	char *argv[];
};

#endif // WINDOWHANDLER_H

