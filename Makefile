INCLUDE = camera.c stereo.c vec.c paramload.c

# build all targets
all: init build

build: main.c $(INCLUDE)
	gcc -o build/recon $^

vpath %.c src
vpath %.c src/recon
vpath %.c src/math
vpath %.c src/conf

clean:
	rm build/*

init:
	mkdir -p build