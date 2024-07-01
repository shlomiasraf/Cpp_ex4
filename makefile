CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Source files
SOURCESDemo = Demo.cpp
SOURCESTest = testCounter.cpp tests.cpp

# Object files
OBJECTSDemo = $(SOURCESDemo:.cpp=.o)
OBJECTSTest = $(SOURCESTest:.cpp=.o)

# Build the demo executable
demo: $(OBJECTSDemo)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Build the testCounter executable
testCounter: $(OBJECTSTest)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Compile .cpp files to .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the project
tree: demo
	./demo

tests: testCounter
	./testCounter

# Clean up build files
clean:
	rm -f *.o demo testCounter

.PHONY: all clean demo testCounter tree tests
