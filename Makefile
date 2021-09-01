PROJECT=Hitman Blood Money Trainer

all:
	@# Build Injector
	cd ./injector && \
	powershell.exe -c "cmake.exe -A Win32 -B build" && \
	powershell.exe -c "cmake.exe --build build --config Release"
	
	@# Build Data Tool
	cd ./trainer && \
	powershell.exe -c "cmake.exe -A Win32 -B build" && \
	powershell.exe -c "cmake.exe --build build --config Release"
	
	@# Copy compiled files to ./bin
	if ! [ -d bin ]; then mkdir -p bin; fi && \
	cp ./injector/build/Release/Shitman.exe ./bin && \
	cp ./trainer/build/Release/trainer.dll ./bin/

clean:
	@# Clean output folder
	rm -fr ./bin/**
	
	@# Clean build folders
	cd ./injector && rm -fr ./build/**
	cd ./trainer && rm -fr ./build/**
