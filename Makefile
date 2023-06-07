CC = gcc
CFLAGS = -Wall -Wextra -std=c11
SRCS = $(wildcard *.c)
TEST_SRCS = $(wildcard unit_tests/*.c)
OBJS = $(SRCS:.c=.o)
TEST_OBJS = $(TEST_SRCS:.c=.o)
TARGET = way
TEST_TARGET = unit_tests

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(TEST_TARGET): $(TEST_OBJS) $(OBJS)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_OBJS) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

unit_test/%.o: unit_tests/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f $(OBJS) $(TEST_OBJS) $(TARGET) $(TEST_TARGET)
