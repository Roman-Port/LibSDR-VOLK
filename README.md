# VOLK for LibSDR

VOLK for LibSDR is a modifed, "trim the fat" version of VOLK designed for LibSDR.

## Building

To build, clone recursively:

```
git clone --recursive https://github.com/gnuradio/volk.git
```

Then, navigate into the ``libsdr`` folder and run the first-time setup script ``setup.sh``. You'll only have to do this once:

```
cd libsdr
./setup.sh
```

Then, run the ``configure.sh`` script. You'll likely only need to run this once, but if you make changes to the build process, it may need to be run again:

```
./configure.sh
```

Now, you can actually build each platform (or them all). The configure script generated ``build`` scripts for each platform. Run the ones you need, or build for all platforms:

```
./build_all.sh
```

The binaries will now exist in the ``libsdr/bin/`` directory.
