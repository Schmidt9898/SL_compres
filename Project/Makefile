.PHONY: build run clean

build:
	cmake -E make_directory $(CURDIR)/build
	cmake -E make_directory $(CURDIR)/release
	cmake -S . -B .\build
	cmake --build .\build --config Release -j8
	copy .\build\Release\run.exe .\release\run.exe
run: build
	.\build\Release\run.exe 0 0 0
clean:
	del /s /q build

