.SUFFIXES: .cpp .o .h

DIR = $(notdir $(CURDIR))

SYSNAME = $(shell uname -s)

NAME1 = main
NAME2 = test
NAME3 = onp
NAME4 = logicvariable
NAME5 = testConvertToONP
NAME6 = utils
NAME7 = truthTable


CXX = g++

LIBS =

CXXFLAGS = -Wall -std=c++11

OBJECTS = $(NAME1).o $(NAME2).o $(NAME3).o $(NAME4).o $(NAME5).o $(NAME6).o $(NAME7).o

HFILES = $(NAME2).h $(NAME3).h $(NAME4).h $(NAME5).h $(NAME6).h $(NAME7).h

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
