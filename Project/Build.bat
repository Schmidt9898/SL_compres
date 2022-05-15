mkdir build
cmake -E make_directory $(CURDIR)/release
cmake -S . -B .\build
cmake --build .\build --config Release -j8