#include <stddef.h>
#include <iostream>
#include <cstring>
#include "string.h"

/**
 * @brief checks if the current char is a delimiter 
 * @param to_check is the checked char
 * @param delimiters is a pointer to the array of delimiters
 * @return true if the checked char is a delimiter. else - false.
 */
static bool check_delimiters(char to_check, const char* delimiters) { 
    for(;*delimiters != '\0'; delimiters++) {
        if(to_check == *delimiters) {
            return true;
        }
    }
    return false;
}  

String::String() : 
	data(new char[1]) , length(0) {
	data[0] = '\0';
}
	
String::String(const String &str) {
	data = new char[str.length+1];
	strcpy(data, str.data);	
    length = str.length;
}
	
String::String(const char *str) {
	if(str == NULL) {
		data = new char[1];
		data[0] = '\0'; 
	}
	else {
		data = new char[strlen(str)+1];
		strcpy(data, str);
		length = strlen(str);
	}
}

String::~String() {
	delete[] data; 
}

String& String::operator=(const String &rhs) {
	if(this == &rhs) {
		return *this;
	}
	delete[] data;
	data = new char[(rhs.length)+1];
	strcpy(data, rhs.data);
	length = rhs.length;
	return *this;
}
    
String& String::operator=(const char *str) {
	if(data == str) {
		return *this;
	}
	delete[] data;
	data = new char[strlen(str)+1];
	strcpy(data, str);
	length = strlen(str);
	return *this;
}

bool String::equals(const String &rhs) const { 
  return equals(rhs.data); 
}

bool String::equals(const char *rhs) const {
    if((strlen(rhs)) != length) {
        return false;
    } else {
        if(strcmp(data, rhs) == 0) {
    	   return true;
        } else {
           return false;
        }
    }
}

void String::split(const char *delimiters,
                   String **output,
                   size_t *size) const {
    int words_counter = 0;
    bool word_flag = true;
    for(unsigned int j=0; j<length; j++) {
        if((!check_delimiters(data[j], delimiters)) && (word_flag == true)) {
            words_counter++;
            word_flag = false;
        } else if(check_delimiters(data[j], delimiters)) {
            word_flag = true;
        }
    }
    if(output == NULL) {  
        *size = words_counter;
        return;
    }    
    String *str_arr = new String[words_counter];
    int cur_char = 0;
    int cur_word = 0;
    char temp_word[length+1];
    memset(temp_word, 0, length+1);
    for(unsigned int j=0; j<length; j++) {
        if(!check_delimiters(data[j], delimiters)) {
            temp_word[cur_char] = data[j];
            cur_char++;
        } else if(cur_char != 0) {
            str_arr[cur_word] = temp_word;
            memset(temp_word, 0, cur_char);
            cur_char = 0;
            cur_word++;
        }
    }
    if(cur_char != 0) {
        str_arr[cur_word] = temp_word;
        cur_word++;
    }
    *size = words_counter;
    *output = str_arr;
}

int String::to_integer() const {
    int num_string = atoi(data);
    return num_string;
}

String String::trim() const {
    int i = 0;
    int j = length;
    int temp_len = length;
    while(data[i] == ' ') {
        temp_len--;
        i++;
    }
    if(temp_len == 0) {
        String tmp;
        return tmp;
    }
    while(data[j-1] == ' ') {
        temp_len--;
        j--;
    }
    
    char temp_new_string[temp_len+1];
    memset(temp_new_string, 0, temp_len+1);
    for(int k=0; k<temp_len; k++) {
        temp_new_string[k] = data[i];
        i++;
    }
    String new_string(temp_new_string);
    return new_string;
}