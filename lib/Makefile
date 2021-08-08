CC=gcc

FLAGS=-Iinc -Werror -std=gnu99 -g -O0 -fPIC
LIBS=-lraylib -ldl -lm -lpthread

FILES=build/utils/vector.o build/core/scene.o build/core/element.o \
	build/math/matrix.o build/math/vector.o build/core/camera.o
OUT=bin/libgorlot.so

all: $(FILES)
	@$(CC) $(FLAGS) -shared $(FILES) -o $(OUT) $(LIBS)
	@echo "Gorlot built successfully"

build/utils/vector.o: src/utils/vector.c
	@echo -e "CC\t\t"$<
	@$(CC) $(FLAGS) $< -c -o $@ $(LIBS)

build/core/scene.o: src/core/scene.c
	@echo -e "CC\t\t"$<
	@$(CC) $(FLAGS) $< -c -o $@ $(LIBS)

build/core/element.o: src/core/element.c
	@echo -e "CC\t\t"$<
	@$(CC) $(FLAGS) $< -c -o $@ $(LIBS)

build/math/matrix.o: src/math/matrix.c
	@echo -e "CC\t\t"$<
	@$(CC) $(FLAGS) $< -c -o $@ $(LIBS)

build/math/vector.o: src/math/vector.c
	@echo -e "CC\t\t"$<
	@$(CC) $(FLAGS) $< -c -o $@ $(LIBS)

build/core/camera.o: src/core/camera.c
	@echo -e "CC\t\t"$<
	@$(CC) $(FLAGS) $< -c -o $@ $(LIBS)

clean:
	@rm $(FILES) $(OUT)
