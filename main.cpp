#include "field.h"
#include "ip.h"
#include "port.h"
#include "string.h"
#include "input.h"
#include <iostream>
#include <stdio.h>

int main(int argc, char *argv[]) {
	if(check_args(argc,argv)) {
		return 1;
	}
	size_t size = 0;
	String temp(argv[1]);
	String *rule;
	temp.split("=", &rule, &size);
	rule[0] = rule[0].trim();
	if(rule[0].equals("dst-ip") || rule[0].equals("src-ip")) {
		Ip ip_rule(rule[0].trim());
		ip_rule.set_value(rule[1].trim());
		parse_input(ip_rule);
	} else if(rule[0].equals("dst-port") || rule[0].equals("src-port")) {
		Port port_rule(rule[0].trim());
		port_rule.set_value(rule[1].trim());
		parse_input(port_rule);
	} else {
		delete[] rule;
		return 1;
	}
	delete[] rule;	
	return 0;
};