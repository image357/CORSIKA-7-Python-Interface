RDFLAGS		= -g -Werror
PYFLAGS		= -D USE_PYTHON_INTERFACE
export RDFLAGS
export PYFLAGS

CC			= g++
AR			= ar

CFLAGS		= -fPIC
CFLAGS		+= -I"$(COAST_DIR)/include"
CFLAGS		+= $(shell python3-config --cflags)
CFLAGS		+= $(RDFLAGS)
CFLAGS		+= $(PYFLAGS)
CFLAGS		+= -x c++ -std=c++17 -Wall -Wextra \
			   -D EXPERIMENTAL_FILESYSTEM

ARFLAGS		= rcsT

DEPFILE		= .dep
SOURCES		= PythonWrapper.cpp CppWrapper.cpp PythonInterface.cpp \
			  CorsikaConfig.cpp
HEADERS		:= ${wildcard *.h}
OBJECTS		:= ${SOURCES:.cpp=.o}
SUBDIRS		=
SUBOBJS		:= $(addsuffix /static.a, $(SUBDIRS))
SUBCLEAN	:= $(addsuffix .clean, $(SUBDIRS))
BINARY		= static.a


.PHONY: all
all:		$(BINARY)

$(BINARY):	$(OBJECTS) $(SUBDIRS)
	$(AR) $(ARFLAGS) $@ $(OBJECTS) $(SUBOBJS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

$(DEPFILE):	$(SOURCES) $(HEADERS)
	$(CC) -MM $(SOURCES) > $@
-include $(DEPFILE)

.PHONY: clean $(SUBCLEAN)
clean:		$(SUBCLEAN)
	rm -vf $(BINARY) $(OBJECTS) $(DEPFILE)
$(SUBCLEAN): %.clean:
	$(MAKE) -C $* clean

.PHONY: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@ -e
