.SUFFIXES: .cpp .o .h

DIR = $(notdir $(CURDIR))

SYSNAME = $(shell uname -s)

NAME1 = sortowanie

CXX = g++

LIBS =

CXXFLAGS = -Wall -std=c++11

OBJECTS = $(NAME1).o

HFILES = 

TARGET = $(NAME1).out

%.o : %.cpp $(HFILES) Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LIBS) $(OBJECTS) -o $(TARGET)


.PHONY : run1

run1: $(TARGET)
	./$(TARGET)

.PHONY : clean

clean :
	$(RM) $(TARGET) *.o core
