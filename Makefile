# set the compiler to g++
CXX = g++                          # compiler to use
# set the compiler flags to use C++11 standard and enable all warnings
CXXFLAGS = -std=c++11 -Wall -Wextra -Werror  # compiler flags
# define the name of the final executable
TARGET = lab9                      # target executable name
# list the source files
SRCS = main.cpp matrix.cpp         # source files

# object files
OBJS = $(SRCS:.cpp=.o)

# default target: build the executable
all: $(TARGET)                     # default target depends on the executable

# rule to compile and link all source files
$(TARGET): $(OBJS)                 # target depends on the source files
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)  # compile and link source files

# compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# rule to clean up generated files
clean:                             # clean target to remove built files
	rm -f $(TARGET) $(OBJS)            # remove the executable and object files

.PHONY: all clean                  # declare phony targets
