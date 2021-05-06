# Download the required dependencies
sudo apt update
sudo apt install build-essential cmake python3.8 python3-pip mingw-w64 mingw-w64-common -y

# Download mako
pip3 install mako

# Obtain the NDK
wget https://dl.google.com/android/repository/android-ndk-r21e-linux-x86_64.zip

# Unpack the NDK
unzip -q android-ndk-r21e-linux-x86_64.zip

# Now that it's unpacked, remove the ZIP
rm android-ndk-r21e-linux-x86_64.zip
