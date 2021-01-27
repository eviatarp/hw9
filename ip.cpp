#include "ip.h"
#include "field.h"
#include "string.h"
#include <stdio.h>

#define MASK_SEGMENT 2
#define SEGMENTS 4
enum {max_ip = 255};
enum {mask_size = 32};
enum {max_shift = 24};
enum {min_shift = 8};

Ip::Ip(String pattern) : Field(pattern, IP) {
	low = 0;
	high = 0;	
} 

bool Ip::set_value(String val) {
	val = val.trim();
	size_t size = 0;
	String *temp_string_arr; 
	val.split("./", &temp_string_arr, &size);
	if(size != SEGMENTS+1) {                        
		delete[] temp_string_arr;
		return false;
	}
	for(int check_value=0; check_value<SEGMENTS+1; check_value++) {
		if(temp_string_arr[check_value].to_integer()<0 || 
		   temp_string_arr[check_value].to_integer()>max_ip) {
			delete[] temp_string_arr;
			return false;
		}
	}
	if(temp_string_arr[SEGMENTS].to_integer()<0 ||  
	   temp_string_arr[SEGMENTS].to_integer()>mask_size) {
		delete[] temp_string_arr; 
		return false;
	}
	int mask = 0;
	for(int i=0; i<temp_string_arr[SEGMENTS].to_integer(); i++) {
		mask = ((mask<<1)+1);
	}
	mask = (mask<<(mask_size-temp_string_arr[SEGMENTS].to_integer()));
	int sum = 0;
	int shift = max_shift;
	for (int i=0; i<SEGMENTS; ++i)
	{
		sum = sum+((temp_string_arr[i].to_integer())<<shift);
		shift = shift-min_shift;
	}
	low = mask&sum;
	high = low|(~mask);
	delete[] temp_string_arr; 
	return true;

}

bool Ip::match_value(String val) const {
	val = val.trim();
	size_t size = 0;
	String *temp_string_arr; 
	val.split(".", &temp_string_arr, &size);
	if(size != SEGMENTS) {
		delete[] temp_string_arr;
		return false;
	}
	unsigned int sum = 0;
	int shift = max_shift;
	for (int i=0; i<SEGMENTS; ++i)
	{
		sum = sum+((temp_string_arr[i].to_integer())<<shift);
		shift = shift-min_shift;
	}
	if(sum<low || sum>high) {
		delete[] temp_string_arr;
		return false;
	}
	delete[] temp_string_arr;
	return true;
}