PROJECT         = shitman3

CC              = i686-w64-mingw32-g++-posix
CFLAGS          = -std=c++2a -masm=intel -Wall -Wextra -Werror -Wshadow -Wpedantic -Wconversion\
                  -Wno-missing-field-initializers

LD              = i686-w64-mingw32-g++-posix
LDFLAGS         = -nostdinc++ -static -s -shared -ld3d9 -ld3dx9

ASM             = nasm
ASFLAGS         = -f win32

BIN             = Lib
BUILD           = Build

DEBUG           = $(BUILD)/Debug
RELEASE         = $(BUILD)/Release

INCLUDE         = Include
INCLUDES        = $(addprefix -I,$(INCLUDE))

SOURCE          = Sources
SOURCES         = $(wildcard $(SOURCE)/*.cpp)
DEBUG_OBJECTS   = $(patsubst $(SOURCE)/%.cpp,$(DEBUG)/%.o,$(SOURCES))
RELEASE_OBJECTS = $(patsubst $(SOURCE)/%.cpp,$(RELEASE)/%.o,$(SOURCES))

### COMMENT IF YOU USE A TOASTER ###
MAKEFLAGS      += -j$(shell nproc)
### COMMENT IF YOU USE A TOASTER ###

all: $(BIN) $(BUILD) $(PROJECT)
$(PROJECT): debug release

debug: CFLAGS := -O2 -g $(CFLAGS)
debug: $(DEBUG_OBJECTS)
	$(LD) $(DEBUG_OBJECTS) $(LDFLAGS) -o $(BIN)/$(PROJECT)_d.dll

release: CFLAGS := -O3 -fvisibility=hidden -ffast-math $(CFLAGS)
release: $(RELEASE_OBJECTS)
	$(LD) $(RELEASE_OBJECTS) $(LDFLAGS) -o $(BIN)/$(PROJECT).dll

$(DEBUG_OBJECTS): $(DEBUG)/%.o : $(SOURCE)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ 

$(RELEASE_OBJECTS): $(RELEASE)/%.o : $(SOURCE)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: $(BIN)
$(BIN):
	mkdir -p ./Lib

.PHONY: $(BUILD)
$(BUILD):
	mkdir -p ./Build/Debug
	mkdir -p ./Build/Release

.PHONY: clean
clean:
	rm -fr ./Lib/*
	rm -fr ./Build/*

.PHONY: extra-clean
extra-clean:
	rm -fr ./Lib
	rm -fr ./Build
