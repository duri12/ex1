COMP=gcc
OBJECTS=main.o AsciiArtTool.o RLEList.o
OUT_FILE=AsciiArtTool
DEBUG_FLAGS=-g
COMP_FLAGS=-std=c99 -Wall -Werror

$(OUT_FILE) : $(OBJECTS)
	$(COMP) $(DEBUG_FLAGS) $(OBJECTS) -o $(OUT_FILE)


main.o: tool/AsciiArtTool.c tool/AsciiArtTool.h tool/main.c RLEList.c RLEList.h
	$(COMP) -c $(DEBUG_FLAGS) $(COMP_FLAGS) tool/$*.c

AsciiArtTool.o: tool/AsciiArtTool.c tool/AsciiArtTool.h RLEList.c RLEList.h
	$(COMP) -c $(DEBUG_FLAGS) $(COMP_FLAGS) tool/$*.c

RLEList.o: RLEList.c RLEList.h
	$(COMP) -c $(DEBUG_FLAGS) $(COMP_FLAGS) $*.c

