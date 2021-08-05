CC=gcc

FLAGS=-I../lib/inc -L../lib/bin -Werror -std=gnu99 -g -O0
LIBS=-lraylib -ldl -lm -lpthread -lgorlot

FILES=build/main.o build/editor/gui.o build/editor/gui/topbar/topbar.o \
	build/editor/gui/outliner/outliner.o build/editor/editor.o \
	build/utils/input.o build/editor/gui/explorer/explorer.o \
	build/editor/tools/move_tool.o build/editor/gui/outliner/context.o
OUT=bin/editor.o

all: $(FILES)
	@$(CC) $(FLAGS) $(FILES) -o $(OUT) $(LIBS)
	@echo "Editor built successfully"

build/main.o: src/main.c
	@echo -e "CC\t\t"$<
	@$(CC) $(FLAGS) $< -c -o $@ $(LIBS)

build/editor/gui.o: src/editor/gui.c
	@echo -e "CC\t\t"$<
	@$(CC) $(FLAGS) $< -c -o $@ $(LIBS)

build/editor/gui/topbar/topbar.o: src/editor/gui/topbar/topbar.c
	@echo -e "CC\t\t"$<
	@$(CC) $(FLAGS) $< -c -o $@ $(LIBS)

build/editor/gui/outliner/outliner.o: src/editor/gui/outliner/outliner.c
	@echo -e "CC\t\t"$<
	@$(CC) $(FLAGS) $< -c -o $@ $(LIBS)

build/editor/editor.o: src/editor/editor.c
	@echo -e "CC\t\t"$<
	@$(CC) $(FLAGS) $< -c -o $@ $(LIBS)

build/utils/input.o: src/utils/input.c
	@echo -e "CC\t\t"$<
	@$(CC) $(FLAGS) $< -c -o $@ $(LIBS)

build/editor/gui/explorer/explorer.o: src/editor/gui/explorer/explorer.c
	@echo -e "CC\t\t"$<
	@$(CC) $(FLAGS) $< -c -o $@ $(LIBS)

build/editor/tools/move_tool.o: src/editor/tools/move_tool.c
	@echo -e "CC\t\t"$<
	@$(CC) $(FLAGS) $< -c -o $@ $(LIBS)

build/editor/gui/outliner/context.o: src/editor/gui/outliner/context.c
	@echo -e "CC\t\t"$<
	@$(CC) $(FLAGS) $< -c -o $@ $(LIBS)

run: all
	@$(OUT)

clean:
	@rm $(FILES) $(OUT)
