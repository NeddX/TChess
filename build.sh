#!/usr/bin/env sh

clear
echo "Build started."

# Temporary fro now.
#rm -rf "builds/linux"

if [ ! -d "builds" ]; then
    echo "Configuring CMake..."
	mkdir -p "builds"
	mkdir -p "builds/linux"
	cd "builds/linux"
	cmake ../../
elif [ ! -d "builds/linux" ]; then
	echo "Configuring CMake.."
    mkdir -p "builds/linux"
	cd "builds/linux"
	cmake ../../
else
	cd "builds/linux"
fi

echo "Building..."
cmake --build ./
cp "compile_commands.json" ../../
echo "Build finished."
