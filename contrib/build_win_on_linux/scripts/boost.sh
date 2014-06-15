#!/bin/bash

set -e

cd ~
export INSTALLPREFIX="$OUTDIR/staging/boost"
mkdir -p deps/boost
cd deps/boost
wget -c http://pkgs.fedoraproject.org/repo/pkgs/mingw-boost/boost_1_54_0.tar.bz2/15cb8c0803064faef0c4ddf5bc5ca279/boost_1_54_0.tar.bz2
wget -c http://wtogami.fedorapeople.org/boost-mingw-gas-cross-compile-2013-03-03.patch
mkdir -p "$INSTALLPREFIX"
tar xjf boost_1_54_0.tar.bz2
cd boost_1_54_0
GCCVERSION=$($HOST-g++ -E -dM $(mktemp --suffix=.h) | grep __VERSION__ | cut -d ' ' -f 3 | cut -d '"' -f 2)
echo "using gcc : $GCCVERSION : $HOST-g++
:
<rc>$HOST-windres
<archiver>$HOST-ar
<cxxflags>-frandom-seed=boost1
<ranlib>$HOST-ranlib
;" > user-config.jam
./bootstrap.sh --without-icu
patch -p0 < ../boost-mingw-gas-cross-compile-2013-03-03.patch
sed -i 's^\[ ac.check-library /zlib//zlib : <library>/zlib//zlib^^' libs/iostreams/build/Jamfile.v2
sed -i 's^<source>zlib.cpp <source>gzip.cpp \]^^' libs/iostreams/build/Jamfile.v2
./bjam toolset=gcc binary-format=pe target-os=windows threadapi=win32 threading=multi variant=release link=static --user-config=user-config.jam --without-mpi --without-python -sNO_BZIP2=1 -sNO_ZLIB=1 --layout=tagged --build-type=complete --prefix="$INSTALLPREFIX" $MAKEOPTS install
cd "$INSTALLPREFIX"
zip -r boost-win32-1.54.0-gitian-r6.zip *
cp boost-win32-1.54.0-gitian-r6.zip $OUTDIR

