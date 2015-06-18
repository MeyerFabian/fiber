# fiber
Repository for the fiber tracking project.

REQUIRED PACKAGES:
VTK (6.2.0) http://www.vtk.org/download/

Documentation: 
Some DICOM images may not load into VTK with the built-in vtkDICOMImageReader. Especially the majority of OsiriX data sets (http://www.osirix-viewer.com/datasets/) don't work. The only data set that could be loaded was BRAINIX. Im not quite sure if it is actually a multiframe dataset, where the data sets need to be composed.

A solution could be the following project suited for complex DICOM-images. We will be supplied with some DTI-MR data sets. If they cant be loaded into VTK we need to take a look into that:
DICOM for VTK http://dgobbi.github.io/vtk-dicom/