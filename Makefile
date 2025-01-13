PROJECT         = shitman3

CC              = i686-w64-mingw32-g++
CFLAGS          = -std=c++2a -Wall -Wextra -Werror -Wshadow -Wpedantic -Wconversion\
                  -Wno-missing-field-initializers -Wno-attributes -Wno-cast-function-type -Wno-unused-but-set-parameter\
                  -fno-rtti -fno-exceptions

LD              = i686-w64-mingw32-g++
LDFLAGS         = -static -shared -ld3d9 -ld3dx9

ASM             = nasm
ASFLAGS         = -f win32

LIB             = lib
BUILD           = build

INCLUDE         = include
INCLUDES        = $(addprefix -I,$(INCLUDE))

SOURCE          = src
SOURCES         = $(wildcard $(SOURCE)/*.cpp)
DEBUG_OBJECTS   = $(patsubst $(SOURCE)/%.cpp,$(BUILD)/%_d.o,$(SOURCES))
RELEASE_OBJECTS = $(patsubst $(SOURCE)/%.cpp,$(BUILD)/%.o,$(SOURCES))

ASM_SOURCE      = src
ASM_SOURCES     = $(wildcard $(ASM_SOURCE)/*.asm)
ASM_OBJECTS     = $(patsubst $(ASM_SOURCE)/%.asm,$(BUILD)/%.obj,$(ASM_SOURCES))

### COMMENT IF YOU USE A TOASTER ###
MAKEFLAGS      += -j$(shell nproc)
### COMMENT IF YOU USE A TOASTER ###

all: $(LIB) $(BUILD) $(PROJECT)
$(PROJECT): release

debug:   CFLAGS  += -O2 -g
release: CFLAGS  += -march=native -Ofast -fPIE -funsafe-math-optimizations -fomit-frame-pointer
release: CFLAGS  += -funroll-loops -funsafe-loop-optimizations -funswitch-loops -floop-parallelize-all
release: CFLAGS  += -finline-functions -falign-functions -falign-loops -falign-jumps -fno-function-sections
release: CFLAGS  += -fno-ident -fvisibility=hidden -fstrict-aliasing
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
	mkdir -p ./lib

$(BUILD):
	mkdir -p ./build
	mkdir -p ./build

.PHONY: docker-container
docker-container:
	docker build -f "Dockerfile" -t "$(PROJECT)-dev" .
.PHONY: docker-build
docker-build:
	docker run -v "$(shell pwd):/var/$(PROJECT)-dev/$(PROJECT)" -u "$(shell id -u):$(shell id -g)" "$(PROJECT)-dev" make

.PHONY: clean
clean:
	rm -fr ./lib/*
	rm -fr ./build/*

.PHONY: extra-clean
extra-clean:
	rm -fr ./lib
	rm -fr ./build
