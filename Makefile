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

C_DEFS += \
-DGIT_BRANCH=\"$(BRANCH)\" \
-DGIT_HASH=\"$(HASH)\" \
-DGIT_TAG=\"$(TAG)\"

TARGET_BASE1=all_tests
TARGET1 = $(TARGET_BASE1)$(TARGET_EXTENSION)
SRC_FILES1=\
  $(UNITY_ROOT)/src/unity.c \
  $(UNITY_ROOT)/extras/fixture/src/unity_fixture.c \
  Src/base64.c \
  Src/crc32.c \
  Src/json.c \
  Src/queue.c \
  Src/software_info.c \
  Src/utils.c \
  Tests/test_main.c \
  Tests/test_base64.c \
  Tests/test_crc32.c \
  Tests/test_json.c \
  Tests/test_queue.c \
  Tests/test_utils.c
INC_DIRS=-IInc -I$(UNITY_ROOT)/src -I$(UNITY_ROOT)/extras/fixture/src
SYMBOLS=-DUNITY_FIXTURE_NO_EXTRAS

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
	@cppcheck --error-exitcode=1 Src
	
misra:
	$(call colorecho,'Checking MISRA C:2012 with cppcheck')
	@cppcheck cppcheck -IInc Src --force --addon=misra.py --inline-suppr --error-exitcode=1 \
	-i Tests
	
#######################################
# Unit test
#######################################

all: clean default

default:
	$(C_COMPILER) $(CFLAGS) $(C_DEFS) $(INC_DIRS) $(SYMBOLS) -g $(SRC_FILES1) -o $(TARGET1) -lm
	- ./$(TARGET1) -v 

clean:
	$(CLEANUP) $(TARGET1)

ci: CFLAGS += -Werror
ci: default
