CXXFLAGS =	-O2 -Wall -Wextra -pedantic

LIBS =		-lboost_filesystem -lboost_program_options

OBJS =		main.o options.o merge.o invalid_path.o symlink_exists.o

TARGET =	symlinkmerge

VPATH =		src/

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:		$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

