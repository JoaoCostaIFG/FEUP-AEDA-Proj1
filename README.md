# FEUP-AEDA-Proj1
First project for the AEDA chair (FEUP MIEIC 2019/2020).  
Chosen project theme: **Cartão Museus de Portugal**.  

### NOTES
Google tests and doxygen have been commented out from the CMakeLists file.
You can uncomment them at your discretion if you want to use them.  
If you uncomment the google tests lib from the CMakeLists file, you still
need to uncomment the include line in the **main.cpp** file.  

### TIPS
If you want to compile this project from the terminal using CMake, you might want to
do the following:  
- create a directory in the project's root: **mkdir cmake-build-debug**  
- cd into the created directory: **cd cmake-build-debug**  
- run the following command: **cmake .. && cmake --build . && ./<executable_name>**  
Everytime you want to recompile and run the project, you just need to run
that last command inside the created folder. Be careful to not commit this folder
and its contents to the repository as it is considered bad practice (and the files
are useless for sharing purposes).  

### UML
Our [UML file](UML_class_diagram.svg) was drawn using [draw.io](https://www.draw.io).  
Our UML is provided in the **[UML_class_diagram.svg](UML_class_diagram.svg)** file as an SVG.  

### Authors
List of [collaborators](https://github.com/tiagodusilva/FEUP-AEDA-Proj1/contributors)

### Know bugs
The code on this repository was left *as is* on the dead-line for delivery so the
bugs listed below should be fixed on the second part of the project:  
- Reading list of users' (CCs) who have bought an event from files (missing a vector clear)  
- Information validity checking when using some of the setters (information changing)  
- Can't remember the others (if any)..  

### License
MIT
