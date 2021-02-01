RDFLAGS		= -g -Werror
PYFLAGS		= -D USE_PYTHON_INTERFACE
export RDFLAGS
export PYFLAGS

CC			= g++

CFLAGS		= -fPIC
CFLAGS		+= -I"$(COAST_DIR)/include"
CFLAGS		+= $(shell python3-config --cflags)
CFLAGS		+= $(RDFLAGS)
CFLAGS		+= $(PYFLAGS)
CFLAGS		+= -x c++ -std=c++17 -Wall -Wextra \
			   -D EXPERIMENTAL_FILESYSTEM

LDFLAGS		= --shared -lstdc++fs
LDFLAGS		+= $(shell python3-config --ldflags)
LDFLAGS		+= $(shell python3-config --libs)

DEPFILE		= .dep
SOURCES		= coast_user_lib.cpp
HEADERS		:= ${wildcard *.h}
OBJECTS		:= ${SOURCES:.cpp=.o}
SUBDIRS		= python
SUBOBJS		:= $(addsuffix /static.a, $(SUBDIRS))
SUBCLEAN	:= $(addsuffix .clean, $(SUBDIRS))
BINARY		= libCOAST.so
TARFILE		= archive.tar.gz
RELEASEF	= README.md override_example.py python/packages
RELEASEFP	:= $(addprefix "../$${PWD\#\#*/}/", $(RELEASEF) $(BINARY))


.PHONY: all
all:		$(BINARY)

.PHONY: release
release: RDFLAGS = -O3
release:	$(BINARY) $(TARFILE)

$(BINARY):	$(OBJECTS) $(SUBDIRS)
	$(CC) -o $@ $(OBJECTS) $(SUBOBJS) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

$(DEPFILE):	$(SOURCES) $(HEADERS)
	$(CC) -MM $(SOURCES) > $@
-include $(DEPFILE)

.PHONY: $(TARFILE)
$(TARFILE):	$(BINARY)
	@rm -rf python/packages/interface/__pycache__
	@tar cfz $(TARFILE) $(RELEASEFP)

.PHONY: docs
docs:
	doxygen

.PHONY: clean $(SUBCLEAN)
clean:		$(SUBCLEAN)
	rm -vf $(BINARY) $(OBJECTS) $(DEPFILE) $(TARFILE)
	@rm -rf python/packages/interface/__pycache__
	@rm -rf ./html
	@rm -rf ./latex
$(SUBCLEAN): %.clean:
	$(MAKE) -C $* clean

.PHONY: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@ -e
