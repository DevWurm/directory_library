/*
	 * License
	 
	 * Copyright 2015 DevWurm
	
	 * This file is part of order_system.

	 *  order_system is free software: you can redistribute it and/or modify
	    it under the terms of the GNU General Public License as published by
	    the Free Software Foundation, either version 3 of the License, or
	    (at your option) any later version.
	
	    order_system is distributed in the hope that it will be useful,
	    but WITHOUT ANY WARRANTY; without even the implied warranty of
	    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	    GNU General Public License for more details.
	
	    You should have received a copy of the GNU General Public License
	    along with order_system.  If not, see <http://www.gnu.org/licenses/>.
	
	    Diese Datei ist Teil von order_system.
	
	    order_system ist Freie Software: Sie können es unter den Bedingungen
	    der GNU General Public License, wie von der Free Software Foundation,
	    Version 3 der Lizenz oder (nach Ihrer Wahl) jeder späteren
	    veröffentlichten Version, weiterverbreiten und/oder modifizieren.
	
	    order_system wird in der Hoffnung, dass es nützlich sein wird, aber
	    OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt; sogar ohne die implizite
	    Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
	    Siehe die GNU General Public License für weitere Details.
	
	    Sie sollten eine Kopie der GNU General Public License zusammen mit diesem
	    Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.
*/



#include <string>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include "../Headers/classes.h"

using namespace std;

namespace direc {
directory::directory() { //standard constructor (set to current directory)
	path = "./";
	try {
		update_files();
	}
	catch (error &e) {
		cout<<"An Error occured! ("<< e.get_code() << "): " << e.get_message() << endl;
		throw e;
	}
	catch (...) {
		cout << "An undefined error occured!";
		exit(3);
	}
}

directory::directory(string in_path) { //constructor with string
	path = in_path;
	if (path.at(path.length() - 1) != '/') { //let path end with '/'
		path += '/';
	}
	try {
		update_files();
	}
	catch (error &e) {
		cout<<"An Error occured! ("<< e.get_code() << "): " << e.get_message() << endl;
		throw e;
	}
	catch (...) {
		cout << "An undefined error occured!";
		exit(3);
	}
}


void directory::update_files() { //update file list
	files.clear();
	number_of_files = 0;

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

		do {
			errno = 0;
			entry = readdir(used_directory); //read next file from directory stream
			if (entry != nullptr) { //reading from directory succeeded
				files.push_back(entry->d_name); //add filename to file list
				++filecounter;
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
	}
	closedir(used_directory);
}



void directory::set_path(string in_path) {//set the path
	path = in_path;
	if (path.at(path.length() - 1) != '/') { //let path end with '/'
			path += '/';
	}
	try {
		update_files();
	}
	catch (error &e) {
		cout<<"An Error occured! ("<< e.get_code() << "): " << e.get_message() << endl;
		throw e;
	}
	catch (...) {
		cout << "An undefined error occured!";
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

}
