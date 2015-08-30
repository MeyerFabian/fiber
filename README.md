# fiber
Repository for the fiber tracking project.

REQUIRED:
VTK (6.2.0) http://www.vtk.org/download/

QT (5) http://www.qt.io/qt5-5/

GLEW (1.10) http://glew.sourceforge.net/

Use MSVC Compiler (2013)

Windows (tested only on Windows)

OpenGL (at least 2.1)

FULL PATH USED:

GLEWDIR:  {Path to GLEW}\glew-1.11.0

MSVC: {Path to MSVC}\Microsoft Visual Studio 12.0\VC"

QTDIR: {Path to Qt}\Qt32\5.5\msvc2013

VTKDIR: {Path to VTK}\VTK-MSVC\bin"

PATH: %MSVC%\bin;%QTDIR%\bin;%VTKDIR%;%GLEWDIR%;

INSTALLATION:

1.  Download and install GLEW and Qt along with QTDesigner

2.  Download and install VTK from http://www.vtk.org/download/ using CMake and Visual Studio 2013.

    2.1 If you run into errors linking with Microsoft Development Kit uncheck the DirectX directory in CMake. DirectX ist not used so you might uncheck it anyway.

    2.2 Check the box VTK_Group_Qt to use Qt with VTK

    2.3 Make sure to check the version of QT(5) in the drop-down menu of Cmake.

    2.4 Start VTK.sln, set Building to Release Mode and build using Strg-Shift-B.


3.  Clone this repository and build it using cmake and your compiler of choice and link it with VTK.

4.  Copy the dynamic linked libraries from the vtk-bin into the bin folder of the fiber-tracking project.

5.  Download or use your own (converted) NIFTI-Images and put them somewhere in the bin folder, where you will find them (e.g. bin/datasets/dti30/dti30.nii)

6.  Run fiber.exe


INPUT DATA:

.nii (NIFTI-Images), NIFTI is an extension of the DICOM-format to support DTI-Imaging.

EXAMPLE DATASETS:

http://scil.dinf.usherbrooke.ca/?page_id=822
