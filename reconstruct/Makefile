BUILD = ../build
INCLUDE = camera.c stereo.c vec.c paramload.c

# build all targets
all: init build

build: main.c $(INCLUDE)
	gcc -o $(BUILD)/recon $^

vpath %.c src
vpath %.c src/recon
vpath %.c src/math
vpath %.c src/conf

clean:
	rm $(BUILD)/*

init:
	mkdir -p $(BUILD)