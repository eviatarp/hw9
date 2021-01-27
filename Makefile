# Defined veriables CXX, CCLINK, CXXFLAGS, and OBJS
CXX=g++ # Compiler
CCLINK=$(CXX) # Read variable CXX using $(CXX)
CXXFLAGS=-g -Wall -std=c++11 # Flag rules
OBJS=field.o ip.o port.o string.o 

# creating exe file
firewall.exe: libfirewall.so main.o
	$(CCLINK) main.o -o firewall.exe -l firewall -l input -L.

# creating library
libfirewall.so: $(OBJS)
	$(CCLINK) -shared $(OBJS) -o libfirewall.so

# string independent 
string.o: string.cpp string.h
	$(CXX) $(CXXFLAGS) -c -fpic string.cpp

# port is dependent on string, field
port.o: port.cpp port.h string.h field.h
	$(CXX) $(CXXFLAGS) -c -fpic port.cpp

# ip is dependent on string, field
ip.o: ip.cpp ip.h string.h field.h
	$(CXX) $(CXXFLAGS) -c -fpic ip.cpp
		
# field is dependent on string, ip, port
field.o: field.cpp field.h string.h ip.h port.h
	$(CXX) $(CXXFLAGS) -c -fpic field.cpp

# main is dependent on string, ip, port, field
main.o: main.cpp ip.h string.h field.h port.h
	$(CXX) $(CXXFLAGS) -c -fpic main.cpp
	
# Gets rid of objects and executable files
clean:
	rm -rf *.o *.exe libfirewall.so