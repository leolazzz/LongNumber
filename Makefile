CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

BUILD_DIR = build

LONGNUMBER_SRC = src/longnumber.cpp
COUNTPI_SRC = src/countpi.cpp
TEST_SRC = tests/test.cpp

LONGNUMBER_OBJ = $(LONGNUMBER_SRC:.cpp=.o)
COUNTPI_OBJ = $(COUNTPI_SRC:.cpp=.o)
TEST_OBJ = $(TEST_SRC:.cpp=.o)

COUNTPI_EXE = $(BUILD_DIR)/CountPi
TEST_EXE = $(BUILD_DIR)/Test

all: $(COUNTPI_EXE) $(TEST_EXE)

$(COUNTPI_EXE): $(LONGNUMBER_OBJ) $(COUNTPI_OBJ)
	@mkdir -p $(BUILD_DIR)  # Создаем папку build, если её нет
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TEST_EXE): $(LONGNUMBER_OBJ) $(TEST_OBJ)
	@mkdir -p $(BUILD_DIR)  # Создаем папку build, если её нет
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: test pi
test: $(TEST_EXE)
	./$(TEST_EXE)

pi: $(COUNTPI_EXE)
	./$(COUNTPI_EXE)

.PHONY: clean
clean:
	rm -f *.o $(COUNTPI_EXE) $(TEST_EXE)
	rmdir $(BUILD_DIR)  # Удаляем папку build, если она пуста