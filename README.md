# fiber
Repository for the fiber tracking project.

REQUIRED:
VTK (6.2.0) http://www.vtk.org/download/

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

1.  Download and install Qt with QTDesigner

2.  Download and install VTK from http://www.vtk.org/download/ using CMake and Visual Studio 2013.

    2.1 Check the box VTK_Group_Qt to use Qt with VTK

    2.2 Make sure to check the version (4 or 5) in the drop-down menu of Cmake.

    2.1.1 If you run into errors linking with Microsoft Development Kit uncheck the DirectX directory in CMake.

3.  Clone this repository and build it using cmake and your compiler of choice and link it with VTK.

4.  Copy the dynamic linked libraries from the vtk-bin into the bin folder of the fiber-tracking project.

5.  Download or use your own (converted) NIFTI-Images and put them somewhere in the bin folder, where you will find them (e.g. bin/datasets/dti30/dti30.nii)

6.  Run fiber.exe from command line with the dataset: "fiber -NIFTI datasets/dti30/dti30.nii -Imageplane"


INPUT DATA:

.nii (NIFTI-Images), NIFTI is an extension of the DICOM-format to support DTI-Imaging.


Links for development:

Will probably feature QT for GUI, examples can be found here: http://www.vtk.org/Wiki/VTK/Examples/Cxx#Qt

B-Spline Generation to create fibers from points using VTK: http://www.vtkjournal.org/browse/publication/790
