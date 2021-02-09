CXX =g++ // name of the compiler
CXX_FILE = $(wildcard *.cpp) // finds all the cpp files in the folder, should be only one for our projects
TARGET = $(patsubst %.cpp, %, $(CXX_FILE)) // gets the name of target without the cpp
CXXFLAGS = -g -std=c++11 -Wall -Werror -pedantic-errors -fmesssage-length=0 // gives various error messages so the code is not sloppy or wrong

all: // Has no build dependency
	$(CXX) $(CXXFLAGS) $(CXX_FILE) -o $(TARGET)
clean:
	rm -f $(TARGET) $(TARGET).exe