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
	
	    directory_library ist Freie Software: Sie können es unter den Bedingungen
	    der GNU General Public License, wie von der Free Software Foundation,
	    Version 3 der Lizenz oder (nach Ihrer Wahl) jeder späteren
	    veröffentlichten Version, weiterverbreiten und/oder modifizieren.
	
	    directory_library wird in der Hoffnung, dass es nützlich sein wird, aber
	    OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt; sogar ohne die implizite
	    Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
	    Siehe die GNU General Public License für weitere Details.
	
	    Sie sollten eine Kopie der GNU General Public License zusammen mit diesem
	    Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.
*/

#ifndef CLASSES_H_
#define CLASSES_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace direc {

class directory {
private:
	string path;
	vector<string>files;
	int number_of_files;
	vector<string>dirs;
	int number_of_dirs;
	void update_files();
public:
	directory();
	directory(string in_path);
	void set_path(string in_path);
	string get_path() const;
	int get_number_of_files() const;
	string get_file_name(int index) const;
	string get_file_path(int index) const;
	int get_number_of_dirs() const;
	string get_dir_name(int index) const;
	string get_dir_path(int index) const;
};

}

#endif /* CLASSES_H_ */
