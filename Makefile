# Detect the OS we are running on, and adjust commands as needed
ifeq ($(OS),Windows_NT)
  ifeq ($(shell uname -s),) # not in a bash-like shell
	CLEANUP = del /F /Q
	MKDIR = mkdir
  else # in a bash-like shell, like msys
	CLEANUP = rm -f
	MKDIR = mkdir -p
  endif
	TARGET_EXTENSION=.exe
else
	CLEANUP = rm -f
	MKDIR = mkdir -p
	TARGET_EXTENSION=.out
endif

######################################
# Git branch and hash
######################################
export BRANCH := $(shell git rev-parse --abbrev-ref HEAD)
export HASH := $(shell git rev-parse HEAD)
export TAG := $(shell git tag --sort=committerdate | tail -1)

C_COMPILER=gcc
ifeq ($(shell uname -s), Darwin)
C_COMPILER=clang
endif

UNITY_ROOT=Tests/Unity

CFLAGS=-std=c99
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Wpointer-arith
CFLAGS += -Wcast-align
CFLAGS += -Wwrite-strings
CFLAGS += -Wswitch-default
CFLAGS += -Wunreachable-code
CFLAGS += -Winit-self
CFLAGS += -Wmissing-field-initializers
CFLAGS += -Wno-unknown-pragmas
CFLAGS += -Wstrict-prototypes
CFLAGS += -Wundef
CFLAGS += -Wold-style-definition
CFLAGS += -ftest-coverage
CFLAGS += -fprofile-arcs

C_DEFS += \
-DGIT_BRANCH=\"$(BRANCH)\" \
-DGIT_HASH=\"$(HASH)\" \
-DGIT_TAG=\"$(TAG)\"

TARGET_DIR=build
TARGET_BASE=all_tests
TARGET = $(TARGET_DIR)/$(TARGET_BASE)$(TARGET_EXTENSION)

IMUTILITY_FILES=\
  Src/base64.c \
  Src/bubble_sort.c \
  Src/crc32.c \
  Src/heap_sort.c \
  Src/json.c \
  Src/priority_queue.c \
  Src/queue.c \
  Src/scheduler.c \
  Src/utils.c

SRC_FILES+=$(IMUTILITY_FILES) \
  $(UNITY_ROOT)/src/unity.c \
  $(UNITY_ROOT)/extras/fixture/src/unity_fixture.c \
  Tests/Helper/sort_functions.c \
  Tests/test_main.c \
  Tests/test_base64.c \
  Tests/test_bubble_sort.c \
  Tests/test_crc32.c \
  Tests/test_heap_sort.c \
  Tests/test_json.c \
  Tests/test_priority_queue.c \
  Tests/test_queue.c \
  Tests/test_scheduler.c \
  Tests/test_utils.c
INC_DIRS=-IInc -I$(UNITY_ROOT)/src -I$(UNITY_ROOT)/extras/fixture/src
SYMBOLS = -DUNITY_FIXTURE_NO_EXTRAS
SYMBOLS += -DUNITY_INCLUDE_DOUBLE
SYMBOLS += -DUNITY_DOUBLE_PRECISION=1e-12

#######################################
# Astyle
#######################################
.PHONY: check_format format

check_format:
	$(call colorecho,'Checking formatting with astyle')
	@Tools/astyle/check_code_style_all.sh
	@git diff --check

format:
	$(call colorecho,'Formatting with astyle')
	@Tools/astyle/check_code_style_all.sh --fix
	
#######################################
# Cppcheck
#######################################
.PHONY: cppcheck misra
cppcheck:
	$(call colorecho,'Checking code with cppcheck')
	@cppcheck cppcheck --enable=all -IInc Src Tests -iTests/Unity --suppress=missingInclude --error-exitcode=1
	
misra:
	$(call colorecho,'Checking MISRA C:2012 with cppcheck')
	@cppcheck cppcheck -IInc Src --force --addon=misra.py --inline-suppr --suppress=misra-c2012-2.3 \
	 --suppress=misra-c2012-8.7 --error-exitcode=1

#######################################
# Code coverage
#######################################
GCOV_EXTENSIONS=*.gc*
GCOVR_FOLDER=gcovr-report
LCOV_FOLDER=lcov-report

lcov-report: all
	mkdir $(LCOV_FOLDER)
	lcov --capture --directory . --output-file $(LCOV_FOLDER)/coverage.info
	lcov --remove $(LCOV_FOLDER)/coverage.info '*/Tests/*' --output-file $(LCOV_FOLDER)/coverage.info
	genhtml $(LCOV_FOLDER)/coverage.info --output-directory $(LCOV_FOLDER)

gcovr-report: all
	mkdir $(GCOVR_FOLDER)
	gcovr -e "Tests" --root . --html --html-details --output $(GCOVR_FOLDER)/coverage.html

#######################################
# Dependancies
#######################################
deps:
	sudo apt-get install lcov
	pip3 install gcovr

#######################################
# Unit test
#######################################

all: clean default

default:
	mkdir $(TARGET_DIR)
	$(C_COMPILER) $(CFLAGS) $(C_DEFS) $(INC_DIRS) $(SYMBOLS) -g $(SRC_FILES) -o $(TARGET) -lm
	- ./$(TARGET) -v 

clean:
	$(CLEANUP) $(TARGET) $(GCOV_EXTENSIONS) \
	rmdir -rf $(TARGET_DIR) $(GCOVR_FOLDER) $(LCOV_FOLDER)

ci: CFLAGS += -Werror
ci: default
