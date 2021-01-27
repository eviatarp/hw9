
#include "port.h"
#include "string.h"
#include "field.h"

enum {max_port = 65535};
enum {segments = 2};

Port::Port(String pattern) : Field(pattern,PORT) {
	range[0] = 0;
	range[1] = 0;
}

bool Port::set_value(String val) { 
	val = val.trim();
	size_t size = 0;
	String *temp_string_arr; 
	val.split("-", &temp_string_arr, &size); 
	if(size != segments) {
		delete[] temp_string_arr;
		return false;
	}
	int low = temp_string_arr[0].to_integer();
	int high = temp_string_arr[1].to_integer();
	if(low<0 || low>max_port || high<0 || high>max_port) {
		delete[] temp_string_arr;
		return false;
	}
	range[0] = low;
	range[1] = high;
	delete[] temp_string_arr;
	return true;
}
 


bool Port::match_value(String val) const {
	val = val.trim();
	int port = val.to_integer();
	if(port <= range[1] && port >= range[0]) {
		return true;
	} else {
		return false;
	}
}