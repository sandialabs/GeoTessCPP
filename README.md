# GeoTessCPP
A model parameterization and software support system that implements the construction, population, storage and interrogation of data stored in 3D Earth models. This version is in C++ and intended for Linux systems.

This project is the C++ version.  There is also a Java version available here:
https://github.com/sandialabs/GeoTessJava

This C++ version includes the following components:
	- GeoTessCPP: The base classes
	- GeoTessAmplitudeCPP: A derived class that adds seismic amplitude and attenuation functionality
	- LibCorr3D: A derived class that manages 3D correction lookup surfaces for seismic observables.
	- GeoTessCPPExamples: Some example programs in C++
	- GeoTessUsersManual.pdf: a manual
	- LICENSE: A file containing the software license
	- Makefile: a make file that will call the make files in each component to build the entire 
	     project
	- geo-tess-cpp-cxx-test: A collection of unit tests for the various software components.
	     Only included in the devl version of the software, not the master version.

Source code documentation is available here: https://sandialabs.github.io/GeoTessCPP/
