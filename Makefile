CXX = g++ -Wall -g3 -fPIC
CPPFLAGS +=
CXXFLAGS += -std=c++14
ASAN_FLAGS = -fsanitize=address -fno-omit-frame-pointer
ASAN_LIBS = -static-libasan
LDFLAGS += -L/usr/local/lib -ldl
INCLUDES += -I./includes/cxxopts-2.2.0/include -I./includes/Mustache-4.0

SRC_DIR = ./src
OBJ_DIR = ./lib
BIN_DIR = ./bin

DAY_SRC_FILES = $(wildcard $(SRC_DIR)/day*.cpp)
DAY_DEP_FILES = $(SRC_DIR)/SolutionFactory.cpp
DAY_OBJ_FILES = $(filter-out $(SRC_DIR)/advent.cpp, $(patsubst $(SRC_DIR)/day%.cpp, $(OBJ_DIR)/day%.o, $(DAY_SRC_FILES)))
SOLUTION_FACTORY = $(OBJ_DIR)/SolutionFactory.o

vpath %.cpp $(SRC_DIR)
vpath %.o $(OBJ_DIR)


$(BIN_DIR)/advent: $(SOLUTION_FACTORY) $(DAY_OBJ_FILES) $(SRC_DIR)/advent.cpp
	@echo "Building $@"
	$(CXX) $(INCLUDES) $^ $(CPPFLAGS) $(ASAN_FLAGS) $(LDFLAGS) $(ASAN_LIBS) -o $@

$(OBJ_DIR)/SolutionFactory.o: $(SRC_DIR)/SolutionFactory.cpp
	$(CXX) -c $^ $(CPPFLAGS) $(ASAN_FLAGS) $(LDFLAGS) $(ASAN_LIBS) -o $@


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Building $@"
	$(CXX) -c $< $(CPPFLAGS) $(ASAN_FLAGS) $(LDFLAGS) $(ASAN_LIBS) -o $@

all: $(DAY_OBJ_FILES) $(BIN_DIR)/advent

run: all
	./advent run $(DAY) < ../input/day$(DAY).txt

.PHONY: clean solve

new:
	@echo "TO BE COMPLETED"
	./advent new

solve:
	./advent run $(DAY)

clean:
	rm -rf $(BIN_DIR)/advent
	rm -rf $(OBJ_DIR)/*.o
