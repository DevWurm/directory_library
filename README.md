# directory_library
A lightweight and simple multiplatform library for exploring directorys in C++ easily (show files and folers in a directory).
With the library you get access to a simple class wich does all the directory crawling for you. You put in a path and
get back a list of all the files and directorys in the given directory. It provides the same interface for Windows and Unix Systems.

##Librarys
The code is compiled in one library "libdirectory.a"/"libdirectory_windows.a", you need to add to your sources, together with the libdirectory.h
 and liberror.h header file you have to include into your source files.

##How to use
<pre><code>
#include "libdirectory.h" //include the header
#include <iostream>
int main() {
	<b>direc::directory dir("/home/user/")</b>; //ceate a directory object (from namespace direc) with a given directory
	std::cout << <b>dir.get_number_of_files()</b>; //get the number of files and folders in the directory
	std::cout << <b>dir.get_file_name(8)</b>; //get the filename of the 8th file
	<b>dir.set_path("./documents/")</b>; //set the path of the directory to a new value (file list is updated automaticly)
	<b>dir.get_path()</b>; //get the current path of the directory
	std::cout << <b>dir.get_file_path(8)</b>; //get the full path of the 8th file
	<b>direc::directory dir2</b>; //create an empty directory object
	return 0;
}
</code></pre>

##License
Copyright 2015 DevWurm<br>
'directory_library' is offered under GPL 3 License (Read ./license/gpl-3.0.txt)

##Documentation
Documentation will be offered soon. (Email me if you have any questions)

##Setup
<b>Building:</b><br>
On Windows install MinGW (components: g++, mingw32-make, ar, ranlib) and add the MinGW bin folder to your path variable
Change into the top directory of the repository and execute
<pre><code>make</code></pre>
or
<pre><code>mingw32-make</code></pre>
on Windows.
Make sure error_lib/error.o exists. On Windows delete the folders Binary and lib before building.
In the subfolder Binary an Object file gets compiled and in the subfolder lib a library file together with the header is
generated. The latest source is provided on <a href="https://github.com/DevWurm/directory_library">GitHub</a><br><br>
<b>Using:</b><br>
Include the header file into your source file(s)
<pre><code>#include "libdirectory.h"</code></pre>
and (optionally [Read Dependencies]) the error_library header file
<pre><code>#include "liberror.h"</code></pre>
and add the library file to your compiling command (C++11 is required)
<pre><code>g++ your.cpp source.cpp files.cpp  <b>libdirectory.a</b> -std=c++11 -o ./output</code></pre>
or
<pre><code>g++ your.cpp source.cpp files.cpp  <b>libdirectory_windows.a</b> -std=c++11 -o .\output.exe</code></pre>
on Windows.
<br>
All the Element functions are showed in the how to use section.

##Errors
directory_library throws <a href="https://github.com/DevWurm/error_library">error_library</a> error objects with a description and a code of the error. Read the
<a href="https://github.com/DevWurm/error_library/blob/master/README.md">error_library Readme</a> for a description how they work and the Section Dependencies in this Readme for 
a description how to add error_library to your project.

##Dependencies
directory_library uses <a href="https://github.com/DevWurm/error_library">error_library</a>, which is also licensed under GPL3. For this reason the file error_lib/error.o
should exist. If not or if you want to update error_library, run the script errorlib_update.sh (Linux only). Then there is a small probabillity, that directory_library doesn't
work anymore (because the interface of error_library could have changed). If you are on Windows or you don't want to take the risk of a corrupted update, then take the
error_lib/error.o from the directory_library GitHub Repository. error.o is included into libdirectory.a. If you want to use the error_library in your project, then include lib/liberror.h
to your project, too. You dont NEED the error.o file for building (read the section How to use from <a href="https://github.com/DevWurm/error_library/blob/master/README.md">error_library Readme</a>!),
 but then you have to adapt the makefile or build yourself.

##Authors
DevWurm<br>
Email: <a href='mailto:devwurm@gmx.net'>devwurm@gmx.net</a><br>
Feel free to contact me, if you have any questions or ideas about the project :)

##Collaborating
You can use the GitHub issue tracker for bugs and feature requests or create a pull request to submit 
changes and forks are welcome, too.
If you don't want to use these possibilities, you can also write me an email at 
<a href='mailto:devwurm@gmx.net'>devwurm@gmx.net</a>.
