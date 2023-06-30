#!/usr/bin/env sh

clear
echo "Build started."

# Temporary fro now.
#rm -rf "builds/linux"

if [ ! -d "builds" ]; then
    echo "Configuring CMake..."
	mkdir -p "builds"
	mkdir -p "builds/linux-release"
	cd "builds/linux-release"
	cmake -DCMAKE_BUILD_TYPE=Release ../../
elif [ ! -d "builds/linux-release" ]; then
	echo "Configuring CMake.."
    mkdir -p "builds/linux-release"
	cd "builds/linux-release"
	cmake -DCMAKE_BUILD_TYPE=Release ../../
else
	cd "builds/linux-release"
fi

echo "Building..."
cmake --build ./
cp "compile_commands.json" ../../
echo "Build finished."
