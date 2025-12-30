
ifeq ($(shell uname), Linux)
	INCLUDE_DIRS = /usr/include /usr/local/include
	LIB_DIRS = /usr/lib /usr/local/lib /usr/lib/x86_64-linux-gnu/ /lib
	SYSTEM_FLAGS = -lsubunit -lm 
endif

ifeq ($(shell uname), Darwin)
	CHECK_PREFIX := $(shell brew --prefix check)
	INCLUDE_DIRS = $(CHECK_PREFIX)/include /opt/homebrew/include /usr/local/include /usr/include
	LIB_DIRS = $(CHECK_PREFIX)/lib /usr/local/lib /opt/homebrew/lib 
endif

IFLAGS = $(foreach dir,$(INCLUDE_DIRS),-I$(dir))
LFLAGS = $(foreach dir,$(LIB_DIRS),-L$(dir))

CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 
CFLAGS_TESTS = -Wall -Wextra -Wno-memset-transposed-args -std=c11 
GCOV_FLAGS = -fprofile-arcs -ftest-coverage 

ifeq ($(shell name), Linux)
	CFLAGS_TESTS += -Wnostringop-overflow -Wnostringop-truncation
endif

LIB_SOURCES = \
	s21_string.c \
	s21_linux_err_messages.c \
	s21_mac_err_messages.c \
	s21_sprintf_utils.c \
	s21_string_utils.c \

LIB_OBJ = $(addprefix build/lib/,$(LIB_SOURCES:.c=.o))

TEST_SOURCES = \
	tests/test_s21_string.c \
	tests/test_s21_string_add.c \
	tests/test_s21_sprintf.c \
	tests/test_main.c \
	tests/test_s21_strerror.c

TEST_OBJ = $(addprefix build/test/, $(TEST_SOURCES:.c=.o))

$(shell mkdir -p build/lib build/test build/test/tests)

all: s21_string.a test gcov_report

s21_string.a: $(LIB_OBJ) 
	@ar rcs $@ $(LIB_OBJ) 

test: s21_string.a $(TEST_OBJ)
	@$(CC) $(CFLAGS_TESTS) $(GCOV_FLAGS) -o $@ $(TEST_OBJ) s21_string.a $(LFLAGS) -lcheck $(SYSTEM_FLAGS)

gcov_report: test
	@./test
	@lcov -c -d build/test -o build/test/coverage.txt
	@genhtml --rc branch_coverage=1 build/test/coverage.txt -o gcov_report

build/lib/%.o: %.c
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

build/test/%.o: %.c
	@$(CC) $(CFLAGS_TESTS) $(GCOV_FLAGS) $(IFLAGS) -c $< -o $@

build/test/tests/%.o: %.c
	@$(CC) $(CFLAGS) $(GCOV_FLAGS) $(IFLAGS) -c $< -o $@

clean:
	rm -rf build test s21_string.a gcov_report
