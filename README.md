# fiber
Repository for the fiber tracking project.

REQUIRED:
VTK (6.2.0) http://www.vtk.org/download/

Use MSVC Compiler (2013)

Windows (tested only on Windows)

OpenGL (at least 2.1)

INSTALLATION:

1.  Download and install Qt with QTDesigner

2.  Download and install VTK from http://www.vtk.org/download/ using CMake and Visual Studio 2013.

2.1 Check the box VTK_Group_Qt to use Qt with VTK

	- If you run into errors linking with Microsoft Devolpment Kit uncheck the DirectX directory in CMake.

3.  Clone this repository and build it using cmake and your compiler of choice and link it with VTK.

4.  Copy the dynamic linked libraries from the vtk-bin into the bin folder of the fiber-tracking project.

5.  Download or use your own (converted) NIFTI-Images and put them somewhere in the bin folder, where you will find them (e.g. bin/datasets/dti30/dti30.nii)

6.  Run fiber.exe from command line with the dataset: "fiber -NII datasets/dti30/dti30.nii"


INPUT DATA:

.nii (NIFTI-Images), NIFTI is an extension of the DICOM-format to support DTI-Imaging.


Links for development:

Will probably feature QT for GUI, examples can be found here: http://www.vtk.org/Wiki/VTK/Examples/Cxx#Qt

3 Plane Slicing example, as its done in a lot of fiber tracking examples to have some anatomy reference in addition to the fibers:
http://www.vtk.org/gitweb?p=VTK.git;a=blob;f=Examples/GUI/Qt/FourPaneViewer/QtVTKRenderWindows.cxx;h=3e94b312d5a5d9b3bfaacdc1f0142df09086326c;hb=HEAD

B-Spline Generation to create fibers from points using VTK: http://www.vtkjournal.org/browse/publication/790
