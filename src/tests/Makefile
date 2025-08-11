CC := g++
CFLAGS := -std=c++20 -Wall -Wextra -Werror
GCOVFLAGS := -fprofile-arcs -ftest-coverage
LDFLAGS := -lgtest -lgtest_main -pthread

SRC_DIR := ../containers_header
TEST_DIR := .
BUILD_DIR := ../build
GCOV_DIR := ../gcov_report

SRC := $(wildcard $(SRC_DIR)/*.h)
TEST_FILES := $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS := $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(notdir $(TEST_FILES)))
TARGET := $(BUILD_DIR)/test

.PHONY: all test gcov_report valgrind clean

all: test

test: $(TARGET)
	./$(TARGET)

$(TARGET): $(TEST_OBJS) $(SRC)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

gcov_report: CFLAGS += $(GCOVFLAGS)
gcov_report: $(TARGET)
	@mkdir -p $(GCOV_DIR)
	./$(TARGET)
	lcov --rc geninfo_unexecuted_blocks=1 --capture --directory $(BUILD_DIR) --output-file $(GCOV_DIR)/coverage.info --ignore-errors inconsistent
	lcov --remove $(GCOV_DIR)/coverage.info '/usr/*' --output-file $(GCOV_DIR)/coverage.info
	genhtml $(GCOV_DIR)/coverage.info --output-directory $(GCOV_DIR)
	@echo "Coverage report generated at $(GCOV_DIR)/index.html"
	xdg-open $(GCOV_DIR)/index.html 2>/dev/null || open $(GCOV_DIR)/index.html 2>/dev/null

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

valgrind: $(TARGET)
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(GCOV_DIR)