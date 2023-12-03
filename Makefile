# Define the compiler
CXX = g++

# Define any compile-time flags
CXXFLAGS = -Wall -std=c++11

# Define the source files
SRCS = main.cpp movies.cpp

# Define the object files 
OBJS = $(SRCS:.cpp=.o)

# Define the executable file
MAIN = runMovies

.PHONY: clean

all: $(MAIN)
	@echo Compilation complete.

$(MAIN): $(OBJS)
	$(CXX)	$(CXXFLAGS)	$(INCLUDES)	-o	$(MAIN)	$(OBJS)	$(LFLAGS)	$(LIBS)

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) *.o *~ $(MAIN)
