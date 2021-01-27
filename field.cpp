#include "field.h"
#include "ip.h"
#include "port.h"
#include "string.h"
#include <stdio.h>

Field::Field(String pattern, field_type type) : pattern(pattern), type(type) {} 

Field::Field(String pattern) : pattern(pattern), type(GENERIC) {}

Field::~Field() {}

field_type Field::get_type() const {
	return type;
}

bool Field::set_value(String val) {
	if(get_type() == IP) {
		return (((Ip*)(this))->set_value(val));
	} else {
		return (((Ip*)(this))->set_value(val));
	}
}

bool Field::match_value(String val) const {
	if(get_type() == IP) {
		return (((Ip*)(this))->match_value(val));
	} else if(get_type() == PORT) {
		return (((Port*)(this))->match_value(val));
	} else {
		return false;
	}
}

bool Field::match(String packet) {
	String* cur_packet;
	bool passed = false;
    size_t packet_size = 0;
    String* address;
    size_t address_size = 0;
	packet.split(",", &cur_packet, &packet_size);     
	for(unsigned int i=0; i<packet_size; i++) {
		cur_packet[i].split("=", &address, &address_size);
		if(address[0].trim().equals(pattern.trim())) {
			passed = match_value(address[1].trim());
			delete[] address;
			delete[] cur_packet;
			return passed;
		}
		delete[] address; 
	}
	delete[] cur_packet;
	return passed;
}

