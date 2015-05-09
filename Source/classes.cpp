/*
	 * License
	 
	 * Copyright 2015 DevWurm
	
	 * This file is part of directory_library.

	 *  directory_library is free software: you can redistribute it and/or modify
	    it under the terms of the GNU General Public License as published by
	    the Free Software Foundation, either version 3 of the License, or
	    (at your option) any later version.
	
	    directory_library is distributed in the hope that it will be useful,
	    but WITHOUT ANY WARRANTY; without even the implied warranty of
	    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	    GNU General Public License for more details.
	
	    You should have received a copy of the GNU General Public License
	    along with directory_library.  If not, see <http://www.gnu.org/licenses/>.
	
	    Diese Datei ist Teil von directory_library.
	
	    directory_library ist Freie Software: Sie k�nnen es unter den Bedingungen
	    der GNU General Public License, wie von der Free Software Foundation,
	    Version 3 der Lizenz oder (nach Ihrer Wahl) jeder sp�teren
	    ver�ffentlichten Version, weiterverbreiten und/oder modifizieren.
	
	    directory_library wird in der Hoffnung, dass es n�tzlich sein wird, aber
	    OHNE JEDE GEW�HRLEISTUNG, bereitgestellt; sogar ohne die implizite
	    Gew�hrleistung der MARKTF�HIGKEIT oder EIGNUNG F�R EINEN BESTIMMTEN ZWECK.
	    Siehe die GNU General Public License f�r weitere Details.
	
	    Sie sollten eine Kopie der GNU General Public License zusammen mit diesem
	    Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.
*/


#include <iostream>
#include <string>
#include <stdlib.h>
#ifdef __WIN32__
	#include <windows.h>
#else
	#include <dirent.h>
	#include <errno.h>
#endif
#include "../Headers/classes.h"
#include "../liberror/liberror.h"

using namespace std;
using err::error;

namespace direc {
directory::directory() { //standard constructor (set to current directory)
#ifdef __WIN32__
	path = ".\\";
#else	
	path = "./";
#endif
	try {
		update_files();
	}
	catch (error &e) {
		throw e;
	}
	catch (...) {
		cout << "An undefined error occurred!";
		exit(3);
	}
}

directory::directory(string in_path) { //constructor with string
	path = in_path;
#ifdef __WIN32__
	if (path.at(path.length() - 1) != '\\') { //let path end with '\'
		path += '\\';
	}
#else		
	if (path.at(path.length() - 1) != '/') { //let path end with '/'
		path += '/';
	}
#endif
	try {
		update_files();
	}
	catch (error &e) {
		throw e;
	}
	catch (...) {
		cout << "An undefined error occurred!";
		exit(3);
	}
}


void directory::update_files() { //update file list
	files.clear();
	dirs.clear();
	number_of_files = 0;
	number_of_dirs = 0;
#ifdef __WIN32__
	//Windows Code
	HANDLE used_directory; //something like target directory stream
	WIN32_FIND_DATA entry; //structure with file data
	DWORD entry_data;
	int int_handler;

	used_directory = FindFirstFile((path+"\\*").c_str(), &entry); //address first file
	if (used_directory == INVALID_HANDLE_VALUE) {//Throw Error at opening stream
		throw error(6, "Failure at opening directory");
	}
	else { //get all filenames
		if(GetLastError() == ERROR_FILE_NOT_FOUND) {
			number_of_files = 0;
			number_of_dirs = 0;
		}
		else {
			int filecounter = 0;
			int dircounter = 0;
			do {
				entry_data = GetFileAttributes((path + entry.cFileName).c_str());
				if (entry_data == INVALID_FILE_ATTRIBUTES) {
					throw error(6, "Failure at receiving file attributes");
				}
				else if (entry_data == FILE_ATTRIBUTE_DIRECTORY) {
					dirs.push_back(entry.cFileName); //get current filename
					++dircounter; //increase number of files
				}
				else {
					files.push_back(entry.cFileName); //get current filename
					++filecounter; //increase number of files
				}
				int_handler = FindNextFile(used_directory, &entry); //get next file
			} while (int_handler != 0);

			number_of_files = filecounter;
			number_of_dirs = dircounter;
		}
	}
	FindClose(used_directory); //close directory
#else
	//unix code
	DIR *used_directory = nullptr; //pointer to target directory
	dirent *entry = nullptr; //structure with file data

	errno = 0;
	used_directory = opendir(path.c_str()); //open directory
	if (used_directory == nullptr) { //throw errors when opening directory
		if (errno == EACCES) {
			errno = 0;
			throw error(1, "No Permissions to access directory");
		}
		else if (errno == ELOOP) {
			errno = 0;
			throw error(2, "Too many symbolic links were encountered in resolving path");
		}
		else if (errno == ENAMETOOLONG) {
			errno = 0;
			throw error(3, "Directory name or path name too long");
		}
		else if (errno == ENOENT) {
			errno = 0;
			throw error(4, "No Directory with this path");
		}
		else if (errno == ENOTDIR) {
			errno = 0;
			throw error(5, "Path is not a directory");
		}
		else {
			errno = 0;
			throw error(0, "Unknown Error");
		}
	}
	else { //open directory succeeded
		int filecounter = 0; //number of files in directory
		int dircounter = 0; //number of directories in directory

		do {
			errno = 0;
			entry = readdir(used_directory); //read next object from directory stream
			if (entry != nullptr) { //test if reading from directory succeded
				if ( opendir((path + entry->d_name).c_str()) != nullptr) { //object is directory
					dirs.push_back(entry->d_name); //add filename to file list
					++dircounter;
				}
				else { //object is file
					files.push_back(entry->d_name); //add filename to file list
					++filecounter;
				}
			}
			else { //reading from directory didn't succeed
				if (errno != 0) { //error occurred; throw errors
					if (errno == EOVERFLOW) {
						errno = 0;
						throw error(6, "File data can't be represented");
					}
					else {
						errno = 0;
						throw error(0, "Unknown Error");
					}
				}
				//else: last file; stream empty
			}
		} while (entry != nullptr);

		number_of_files = filecounter;
		number_of_dirs = dircounter;
	}
	closedir(used_directory);
#endif
}



void directory::set_path(string in_path) {//set the path
	path = in_path;
#ifdef __WIN32__
	if (path.at(path.length() - 1) != '\\') { //let path end with '\'
		path += '\\';
	}
#else		
	if (path.at(path.length() - 1) != '/') { //let path end with '/'
		path += '/';
	}
#endif
	try {
		update_files();
	}
	catch (error &e) {
		throw e;
	}
	catch (...) {
		cout << "An undefined error occurred!";
		exit(3);
	}
}

string directory::get_path() const {
	return path;
}

int directory::get_number_of_files() const {
	return number_of_files;
}

string directory::get_file_name(int index) const {
	return files.at(index);
}

string directory::get_file_path(int index) const {
	return path + files.at(index);
}

int directory::get_number_of_dirs() const {
	return number_of_dirs;
}

string directory::get_dir_name(int index) const {
	return dirs.at(index);
}

string directory::get_dir_path(int index) const {
	return path + dirs.at(index);
}

}
