cfgvolk () {
        #ARGS:
        #       $1: Platform (win, linux, android)
        #       $2: Arch (x86)
        #       $3: CMAKE command line
        #       $4: Output extension

        #Log
        echo "NOW CONFIGURING $1/$2..."

        #Ensure the folders exist
        mkdir -p build/$1/$2/
        mkdir -p bin/$1/$2/

        #Move into dir
        cd build/$1/$2/

        #Configure CMAKE
        cmake ../../../.. $3

        #Move back
        cd ../../../

        #Write the build script
        printf "echo \"NOW BUILDING $1/$2...\"\ncd build/$1/$2/\nmake\ncd ../../../\nmv build/$1/$2/lib/libvolk.$4 bin/$1/$2/libvolk.so" >> build_$1_$2.sh

        #Set file permissions
        chmod 777 build_$1_$2.sh

	#Append to build list
	buildlist="${buildlist}./build_$1_$2.sh\n"
}

cfgvolk_android () {
        #ARGS:
        #       $1: Arch

        cwd=$(pwd)
        cfgvolk "android" $1 "-DCMAKE_TOOLCHAIN_FILE=$cwd/android-ndk-r21e/build/cmake/android.toolchain.cmake -DANDROID_ABI=$1 -DANDROID_NATIVE_API_LEVEL=23 -DANDROID_ARM_NEON=ON -DENABLE_STATIC_LIBS=ON -DPYTHON_EXECUTABLE=/usr/bin/python3.6m -DENABLE_STATIC_LIBS=True -DENABLE_TESTING=OFF" "so"
}

cfgvolk_win () {
        cwd=$(pwd)
        cfgvolk "windows" "x64" "-DCMAKE_TOOLCHAIN_FILE=$cwd/mingw-w64-x86_64.cmake -DENABLE_STATIC_LIBS=True" "dll"
}

# Remove the current build scripts
rm build_*.sh

# Configure all
buildlist=""
cfgvolk_win
cfgvolk "linux" "x64" "-DENABLE_STATIC_LIBS=True" "so"
cfgvolk_android "armeabi-v7a"
bulidvolk_android "arm64-v8a"
cfgvolk_android "x64"
cfgvolk_android "x86_64"

# Write the "build_all" file
printf $buildlist >> "build_all.sh"
chmod 777 build_all.sh
