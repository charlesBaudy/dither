NAME=dither

# since $(NAME) isn't an object nor
# a file until it's created:
#.DEFAULT_GOAL := $(NAME)

# enable full parallelism (because I can)
MAKEFLAGS+= -j

# but first rule is the .DEFAULT_GOAL
all: $(NAME)

SOURCES= \
	$(wildcard sources/*.cpp)

DEFINES=\
	-D__PROGNAME__=devoir-3 \
	-D__PROGVER__=0.5

INCLUDES=-I. -I./includes/ -I/usr/include/boost/

WARNINGS=-Wall -Wextra -Wfatal-errors -Wno-unused-function

LANGUAGE_FLAGS=-std=c++17
COMMON_FLAGS=$(LANGUAGE_FLAGS) $(WARNINGS) $(DEFINES) $(INCLUDES)
RELEASE_FLAGS= -O3 -fwhole-program -flto $(COMMON_FLAGS)
DEBUG_FLAGS= -O0 -g3 $(COMMON_FLAGS)

CXXFLAGS=$(RELEASE_FLAGS)
LDFLAGS=
LIBS  = -lboost_program_options

OBJS=$(SOURCES:.cpp=.o)

-include .depend
-include .flags

count_files=$(shell cut -d: -f 2- .depend | tr ' ' "\n" | sort -u )


depend:
	@./make-depend.py "$(INCLUDES)" "$(SOURCES)" > .depend

debug:
	@echo "CXXFLAGS="$(DEBUG_FLAGS) > .flags

release:
	@echo "CXXFLAGS="$(RELEASE_FLAGS) > .flags

$(NAME): $(OBJS)
	g++ $(OBJS) $(LDFLAGS) -o $(NAME) $(LIBS)

clean:
	@rm -v $(wildcard sources/*.o)
	@rm -v .depend .flags

# counts "real" lines of code
count:
	@echo full:
	@wc -l $(count_files)
	@echo useful: $(shell \
	grep -v \
	-e "^[ ]*//" \
	-e "^[ ]*$$" \
	-e "^[ ]*{[ ]*$$" \
	-e "^[ ]*}[ ]*$$" \
	$(count_files) | wc -l )

