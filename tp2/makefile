CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O2
INCLUDES = -Iinclude
SRC_DIR = src
TEST_DIR = test

EXEC_PERF = exePerfs
EXEC_PLANETES = exePlanetes

SRC_COMMON = $(SRC_DIR)/particule.cxx

all: $(EXEC_PERF) $(EXEC_PLANETES)

$(EXEC_PERF): $(TEST_DIR)/test_perfs_creation.cxx $(SRC_COMMON)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

$(EXEC_PLANETES): $(TEST_DIR)/test_planetes.cxx $(SRC_COMMON)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

run_planetes: $(EXEC_PLANETES)
	./$(EXEC_PLANETES)

run_perfs: $(EXEC_PERF)
	./$(EXEC_PERF)

clean:
	rm -f $(EXEC_PLANETES) $(EXEC_PERF) a.out *.o gmon.out data.txt

.PHONY: all clean run_planetes run_perfs
