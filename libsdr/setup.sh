# Obtain the NDK
wget https://dl.google.com/android/repository/android-ndk-r21e-linux-x86_64.zip

# Unpack the NDK
unzip -q android-ndk-r21e-linux-x86_64.zip

# Now that it's unpacked, remove the ZIP
rm android-ndk-r21e-linux-x86_64.zip

# Install mingw for Windows builds
sudo apt-get install mingw-w64
