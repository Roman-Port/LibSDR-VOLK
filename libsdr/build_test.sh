# Create functions
buildvolk () {
	#ARGS:
	#	$1: Platform (win, linux, android)
	#	$2: Arch (x86)
	#	$3: CMAKE command line
	#	$4: Output extension

	#Log
	echo "NOW BUILDING $1/$2..."

	#Ensure the folders exist
	mkdir -p build/$1/$2/
	mkdir -p bin/$1/$2/

	#Move into dir
	cd build/$1/$2/

	#Configure CMAKE
	cmake ../../../.. $3

	#Actually build
	make

	#Move back
	cd ../../../

	#Move compiled file into output
	mv build/$1/$2/lib/libvolk.$4 bin/$1/$2/libvolk.so
}

buildvolk_android () {
	#ARGS:
	#	$1: Arch

	cwd=$(pwd)
	buildvolk "android" $1 "-DCMAKE_TOOLCHAIN_FILE=$cwd/android-ndk-r21e/build/cmake/android.toolchain.cmake -DANDROID_ABI=$1 -DANDROID_NATIVE_API_LEVEL=23 -DANDROID_ARM_NEON=ON -DENABLE_STATIC_LIBS=ON -DPYTHON_EXECUTABLE=/usr/bin/python3.6m -DENABLE_STATIC_LIBS=True -DENABLE_TESTING=OFF" "so"
}

buildvolk_win () {
	cwd=$(pwd)
	buildvolk "windows" "x64" "-DCMAKE_TOOLCHAIN_FILE=$cwd/mingw-w64-x86_64.cmake -DENABLE_STATIC_LIBS=True" "dll"
}

# Run
buildvolk_win
