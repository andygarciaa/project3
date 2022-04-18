# COP3530 Project 3 - Shopping Bot
A bot built using C++ that finds the lowest prices for various clothes (currently limited to shirts, pants, and shoes). GUI implemented using 
[ImGui](https://github.com/ocornut/imgui), [SFML](https://www.sfml-dev.org/download.php), and [ImGui-SFML](https://github.com/eliasdaler/imgui-sfml)
to integrate the two libraries.

## How to Build and Run
1. Download SFML-2.5.1 from the link above and extract in root folder (i.e. C:\) of your desktop
2. Downloaad and extract this repo 
3. Open the solution in this repo in Visual Studio 2019 as a project
4. In solution explorer, right click the ImGui folder and click include in project if it isn't already
5. Right click SFML tab in solution explorer and open properties page
6. In "C/C++"->"General" on the left, make sure "Additional Include Directories" has "$(SolutionDir)\imgui\;C:\SFML-2.5.1\include"
7. In "C/C++"->"Preprocessor", make sure "Preprocessor Definitions" has "SFML_STATIC;WIN32;<different options>"
8. In "Linker"->"General", make sure "Additional Library Directories" has "C:\SFML-2.5.1\lib"
9. In "Linker"->"Input", make sure "Additional Dependencies" has "opengl32.lib;freetype.lib;sfml-graphics-s-d.lib;gdi32.lib;winmm.lib;
sfml-window-s-d.lib;sfml-system-s-d.lib;%(AdditionalDependencies)"
10. Click ok and run "Local Windows Debugger" in x86 at the top which will (hopefully) generate an executable in the debug folder and 
run the program
