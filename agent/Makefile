
INCLUDE_DIRECTORIES=/usr/local/include/libxml++-2.6 \
	/usr/local/lib/libxml++-2.6/include \
	/usr/lib/glibmm-2.4 /usr/include/glibmm-2.4/ \
	/usr/lib/glibmm-2.4/include \
	/usr/include/glib-2.0 /usr/lib/glib-2.0/include \
	/usr/local/include ../lib ../devices

#INCLUDE_DIRECTORIES=/opt/local/include/libxml++-2.6 \
#	/opt/local/lib/libxml++-2.6/include /opt/local/include/libxml2 \
#	/opt/local/include/glibmm-2.4 /opt/local/lib/glibmm-2.4/include \
#	/opt/local/include/sigc++-2.0 /opt/local/lib/sigc++-2.0/include \
#	/opt/local/include/glib-2.0 /opt/local/lib/glib-2.0/include \
#	/opt/local/include ../lib ../devices
#LIB_DIRECTORIES=/opt/local/lib

CXXFLAGS = -g -Wall $(INCLUDE_DIRECTORIES:%=-I%) -DDLIB_NO_GUI_SUPPORT
LDFLAGS = $(LIB_DIRECTORIES:%=-L%)
LIBRARIES=  xml++-2.6 xml2 pthread z m glibmm-2.4 gobject-2.0 sigc-2.0 glib-2.0 #intl iconv 

vpath %.hpp ../src
vpath %.cpp ../src

SOURCES= \
cppagent.cpp \
agent.cpp \
adapter.cpp \
component.cpp \
component_event.cpp \
connector.cpp \
data_item.cpp \
device.cpp \
options.cpp \
xml_parser.cpp \
xml_printer.cpp \
globals.cpp

OBJS=$(SOURCES:%.cpp=%.o)
LIBS=$(LIBRARIES:%=-l%)

all: agent

clean:
	@echo Removing all object and binary files
	@rm -rf *.o agent

agent: $(OBJS)
	@echo Building agent
	@g++ ${CXXFLAGS} ${LDFLAGS} -o agent $+ ${LIBS}

%.o: %.cpp %.hpp
	@echo Compiling $<
	@g++ -c ${CXXFLAGS} $<

agent.o: adapter.hpp connector.hpp component.hpp component_event.hpp device.hpp \
	data_item.hpp xml_printer.hpp
