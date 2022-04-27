COMP=gcc
OBJECTS=RLEList.o tool/AsciiArtTool.o tool/main.o
OUT_FILE=AsciiArtTool
DEBUG_FLAGS=# add the -g flag for
COMP_FLAGS=-std=c99 -I/home/mtm/public/2122b/ex1 -Itool -Wall -pedantic-errors -Werror -DNDEBUG

$(OUT_FILE) : $(OBJECTS)
	$(COMP) $(DEBUG_FLAGS) $(OBJECTS) -o $(OUT_FILE)

tool/main.o: tool/AsciiArtTool.c tool/AsciiArtTool.h tool/main.c RLEList.c RLEList.h
	$(COMP) -c $(DEBUG_FLAGS) $(COMP_FLAGS) $*.c -o tool/main.o

tool/AsciiArtTool.o: tool/AsciiArtTool.c tool/AsciiArtTool.h RLEList.c RLEList.h
	$(COMP) -c $(DEBUG_FLAGS) $(COMP_FLAGS) $*.c -o tool/AsciiArtTool.o

RLEList.o: RLEList.c RLEList.h
	$(COMP) -c $(DEBUG_FLAGS) $(COMP_FLAGS) $*.c -o RLEList.o

clean:
	rm -f $(OBJECTS) $(OUT_FILE)

