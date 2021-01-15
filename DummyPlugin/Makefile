SHELL = bash
PackagePath = $(shell pwd)

BUTOOL_PATH = ../../

LIBRARY_DUMMY_DEVICE = lib/libBUTool_DummyDevice.so
LIBRARY_DUMMY_DEVICE_SOURCES = $(wildcard src/DummyDevice/*.cc)
LIBRARY_DUMMY_DEVICE_OBJECT_FILES = $(patsubst src/%.cc,obj/%.o,${LIBRARY_DUMMY_DEVICE_SOURCES})

LIBRARY_DUMMY = lib/libBUTool_Dummy.so
LIBRARY_DUMMY_SOURCES = $(wildcard src/Dummy/*.cc)
LIBRARY_DUMMY_OBJECT_FILES = $(patsubst src/%.cc,obj/%.o,${LIBRARY_DUMMY_SOURCES})

INCLUDE_PATH = \
							-Iinclude  \
							-I$(BUTOOL_PATH)/include \

LIBRARY_PATH = \
							-Llib \
							-L$(BUTOOL_PATH)/lib \

INSTALL_PATH ?= ./install

CPP_FLAGS = -std=c++11 -g -O3 -rdynamic -Wall -MMD -MP -fPIC ${INCLUDE_PATH} -Werror -Wno-literal-suffix

CPP_FLAGS +=-fno-omit-frame-pointer -Wno-ignored-qualifiers -Werror=return-type -Wextra -Wno-long-long -Winit-self -Wno-unused-local-typedefs  -Woverloaded-virtual

LINK_LIBRARY_FLAGS = -shared -fPIC -Wall -g -O3 -rdynamic ${LIBRARY_PATH} ${LIBRARIES} -Wl,-rpath=${PackagePath}/lib

.PHONY: all _all clean _cleanall build _buildall

default: build
clean: _cleanall
_cleanall:
	rm -rf obj
	rm -rf bin
	rm -rf lib

all: _all
build: _all
buildall: _all
_all: ${LIBRARY_DUMMY_DEVICE} ${LIBRARY_DUMMY}

${LIBRARY_DUMMY_DEVICE}: ${LIBRARY_DUMMY_DEVICE_OBJECT_FILES} ${LIBRARY_DUMMY}
	#g++ ${LINK_LIBRARY_FLAGS} -lBUTool_DUMMY ${LIBRARY_DUMMY_DEVICE_OBJECT_FILES} -o $@
	g++ ${LINK_LIBRARY_FLAGS} ${LIBRARY_DUMMY_DEVICE_OBJECT_FILES} -o $@
	@echo "export BUTOOL_AUTOLOAD_LIBRARY_LIST=\$$BUTOOL_AUTOLOAD_LIBRARY_LIST:$$PWD/${LIBRARY_DUMMY_DEVICE}" > env.sh

${LIBRARY_DUMMY}: ${LIBRARY_DUMMY_OBJECT_FILES}
	#g++ ${LINK_LIBRARY_FLAGS}  ${LIBRARY_DUMMY_OBJECT_FILES} -ldummy -o $@
	g++ ${LINK_LIBRARY_FLAGS}  ${LIBRARY_DUMMY_OBJECT_FILES} -o $@

# -----------------------
# install
# -----------------------
install: all
	install -m 775 -d ${INSTALL_PATH}/lib
	install -b -m 775 ./lib/* ${INSTALL_PATH}/lib

obj/%.o : src/%.cc
	mkdir -p $(dir $@)
	mkdir -p {lib,obj}
	g++ ${CPP_FLAGS} -c $< -o $@

-include $(LIBRARY_OBJECT_FILES:.o=.d)
