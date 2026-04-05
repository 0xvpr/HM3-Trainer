PROJECT         = binkw32_patch

CC              = i686-w64-mingw32-g++
CFLAGS          = -O2 -std=c++23 -Wall -Wextra -Werror -Wshadow -Wpedantic -Wconversion\
                  -Wno-missing-field-initializers -Wno-attributes -Wno-cast-function-type -Wno-unused-but-set-parameter\
                  -fno-rtti -fno-exceptions -fno-asynchronous-unwind-tables

LD              = i686-w64-mingw32-g++
LDFLAGS         = -static -shared

LIB             = ../lib
BUILD           = ../build

INCLUDE         = $(PROJECT)
INCLUDES        = $(addprefix -I,$(INCLUDE))

SOURCE          = .
SOURCES         = $(addprefix $(SOURCE)/,binkw32_patch.cpp)
DEBUG_OBJECTS   = $(patsubst $(SOURCE)/%.cpp,$(BUILD)/%_d.o,$(SOURCES))
RELEASE_OBJECTS = $(patsubst $(SOURCE)/%.cpp,$(BUILD)/%.o,$(SOURCES))

### COMMENT IF YOU USE A TOASTER ###
MAKEFLAGS      += -j$(shell nproc)
### COMMENT IF YOU USE A TOASTER ###

.PHONY: all debug release extra-clean clean docker-build docker-container $(LIB) $(BUILD) $(PROJECT)
all: $(LIB) $(BUILD) $(PROJECT)
$(PROJECT): release

debug:   CFLAGS  += -g
release: CFLAGS  += -march=native -mavx512f -fPIE -fomit-frame-pointer
release: CFLAGS  += -fno-ident -fvisibility=hidden -fno-strict-aliasing
release: CFLAGS  += -DWIN32_LEAN_AND_MEAN -DVC_EXTRALEAN
release: LDFLAGS += -s

debug: $(DEBUG_OBJECTS)
	$(LD) $(DEBUG_OBJECTS) $(ASM_OBJECTS) $(LDFLAGS) -o $(LIB)/$(PROJECT)_d.dll

release: $(RELEASE_OBJECTS)
	$(LD) $(RELEASE_OBJECTS) $(ASM_OBJECTS) $(LDFLAGS) -o $(LIB)/$(PROJECT).dll

$(DEBUG_OBJECTS): $(BUILD)/%_d.o : $(SOURCE)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ 

$(RELEASE_OBJECTS): $(BUILD)/%.o : $(SOURCE)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIB):
	mkdir -p ../lib

$(BUILD):
	mkdir -p ../build

docker-container:
	docker build -f "Dockerfile" -t "$(PROJECT)-dev" .
docker-build:
	docker run -v "$(shell pwd):/var/$(PROJECT)-dev/$(PROJECT)" -u "$(shell id -u):$(shell id -g)" "$(PROJECT)-dev" make

clean:
	rm -fr ../lib/*
	rm -fr ../build/*
extra-clean:
	rm -fr ../lib
	rm -fr ../build
