PROJECT         = shitman3

CC              = i686-w64-mingw32-g++
CFLAGS          = -O2 -std=c++2a -Wall -Wextra -Werror -Wshadow -Wpedantic -Wconversion\
                  -Wno-missing-field-initializers -Wno-attributes -Wno-cast-function-type -Wno-unused-but-set-parameter\
                  -fno-rtti -fno-exceptions -fno-asynchronous-unwind-tables

LD              = i686-w64-mingw32-g++
LDFLAGS         = -static -shared -ld3d9 -ld3dx9

ASM             = nasm
ASFLAGS         = -f win32

LIB             = ../lib
BUILD           = ../build

INCLUDE         = .
INCLUDES        = $(addprefix -I,$(INCLUDE))

SOURCE          = .
SOURCES         = $(wildcard $(SOURCE)/*.cpp)
DEBUG_OBJECTS   = $(patsubst $(SOURCE)/%.cpp,$(BUILD)/%_d.o,$(SOURCES))
RELEASE_OBJECTS = $(patsubst $(SOURCE)/%.cpp,$(BUILD)/%.o,$(SOURCES))

ASM_SOURCE      = .
ASM_SOURCES     = $(wildcard $(ASM_SOURCE)/*.asm)
ASM_OBJECTS     = $(patsubst $(ASM_SOURCE)/%.asm,$(BUILD)/%.obj,$(ASM_SOURCES))

### COMMENT IF YOU USE A TOASTER ###
MAKEFLAGS      += -j$(shell nproc)
### COMMENT IF YOU USE A TOASTER ###

.PHONY: all extra-clean clean docker-build docker-container $(LIB) $(BUILD) $(PROJECT) loader binkw32_patch
all: $(LIB) $(BUILD) $(PROJECT)
$(PROJECT): release

debug:   CFLAGS  += -g
release: CFLAGS  += -march=native -mavx512f -fPIE -fomit-frame-pointer
release: CFLAGS  += -fno-ident -fvisibility=hidden -fno-strict-aliasing
release: CFLAGS  += -DWIN32_LEAN_AND_MEAN -DVC_EXTRALEAN
release: LDFLAGS += -s

debug: $(ASM_OBJECTS) $(DEBUG_OBJECTS)
	$(LD) $(DEBUG_OBJECTS) $(ASM_OBJECTS) $(LDFLAGS) -o $(LIB)/$(PROJECT)_d.dll

release: $(ASM_OBJECTS) $(RELEASE_OBJECTS)
	$(LD) $(RELEASE_OBJECTS) $(ASM_OBJECTS) $(LDFLAGS) -o $(LIB)/$(PROJECT).dll

$(DEBUG_OBJECTS): $(BUILD)/%_d.o : $(SOURCE)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ 

$(RELEASE_OBJECTS): $(BUILD)/%.o : $(SOURCE)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(ASM_OBJECTS): $(BUILD)/%.obj : $(ASM_SOURCE)/%.asm
	$(ASM) $(ASFLAGS) $< -o $@

$(LIB):
	mkdir -p ../lib

$(BUILD):
	mkdir -p ../build

docker-container:
	docker build -f "Dockerfile" -t "$(PROJECT)-dev" .
docker-build:
	docker run -v "$(shell pwd):/var/$(PROJECT)-dev/$(PROJECT)" -u "$(shell id -u):$(shell id -g)" "$(PROJECT)-dev" make

clean:
	rm -fr ./lib/*
	rm -fr ./build/*

extra-clean:
	rm -fr ./lib
	rm -fr ./build
