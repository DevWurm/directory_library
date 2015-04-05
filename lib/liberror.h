/*
	 * License
	 
	 * Copyright 2015 DevWurm
	
	 * This file is part of error_library.

	 *  error_library is free software: you can redistribute it and/or modify
	    it under the terms of the GNU General Public License as published by
	    the Free Software Foundation, either version 3 of the License, or
	    (at your option) any later version.
	
	    error_library is distributed in the hope that it will be useful,
	    but WITHOUT ANY WARRANTY; without even the implied warranty of
	    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	    GNU General Public License for more details.
	
	    You should have received a copy of the GNU General Public License
	    along with error_library.  If not, see <http://www.gnu.org/licenses/>.
	
	    Diese Datei ist Teil von error_library.
	
	    error_library ist Freie Software: Sie können es unter den Bedingungen
	    der GNU General Public License, wie von der Free Software Foundation,
	    Version 3 der Lizenz oder (nach Ihrer Wahl) jeder späteren
	    veröffentlichten Version, weiterverbreiten und/oder modifizieren.
	
	    error_library wird in der Hoffnung, dass es nützlich sein wird, aber
	    OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt; sogar ohne die implizite
	    Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
	    Siehe die GNU General Public License für weitere Details.
	
	    Sie sollten eine Kopie der GNU General Public License zusammen mit diesem
	    Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.
*/

#ifndef ERROR_H_
#define ERROR_H_

#include <string>
#include <ostream>

using std::string;
using std::ostream;

namespace err {

class error {
private:
	int code;
	string description;
public:
	error(int c, string m): code(c), description(m) {};
	int get_code() const;
	string get_description() const;
	string get_message() const; //get a string with code and description
	void output_error() const; //write error message to cout
	void output_error(ostream& output); //write error message to output stream
	friend ostream& operator<< (ostream& output, error& err_obj); //stream error to stream
};

}



#endif /* ERROR_H_ */
