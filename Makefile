PROJECTS = shitman3 loader binkw32_patch

.PHONY: all clean extra-clean shitman3 loader binkw32_patch package
all: $(PROJECTS)

shitman3: 
	make -C $@

loader: 
	make -C $@

binkw32_patch:
	make -C $@

clean:
	rm -f ./bin/*
	rm -f ./lib/*
	rm -f ./build/*

extra-clean:
	rm -fr ./bin
	rm -fr ./lib
	rm -fr ./build

package:
	zip -jrD shitman.zip bin/loader.exe lib/shitman3.dll lib/binkw32_patch.dll
