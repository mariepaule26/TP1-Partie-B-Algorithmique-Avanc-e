CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -g -Iinclude
EXEEXT ?=
TARGET = tp1_b$(EXEEXT)
TEST = test_graph$(EXEEXT)
COMMON = src/graph.c src/examples.c

.PHONY: all test run clean
all: $(TARGET)

$(TARGET): src/main.c $(COMMON) include/graph.h include/examples.h
	$(CC) $(CFLAGS) src/main.c $(COMMON) -o $@

$(TEST): tests/test_graph.c $(COMMON) include/graph.h include/examples.h
	$(CC) $(CFLAGS) tests/test_graph.c $(COMMON) -o $@

test: $(TEST)
	./$(TEST)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f tp1_b tp1_b.exe test_graph test_graph.exe
