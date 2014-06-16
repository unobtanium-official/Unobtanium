#!/bin/bash

set -e

. scripts/include.sh

export STAGING=$HOME/staging
mkdir -p $STAGING
cd $STAGING
unzip -o $OUTDIR/qt-win32-4.8.3-gitian-r4.zip
unzip -o $OUTDIR/boost-win32-1.54.0-gitian-r6.zip
unzip -o $OUTDIR/bitcoin-deps-win32-gitian-r9.zip
cd ~/deps
rm -rf unobtanium
git clone https://github.com/unobtanium-official/unobtanium.git	# or just unpack a .tar archive
cd ~/deps/unobtanium
export PATH=$STAGING/host/bin:$PATH
ln -sf $STAGING $HOME/qt

# coin qt
$HOME/staging/host/bin/qmake -spec unsupported/win32-g++-cross MINIUPNPC_LIB_PATH=$STAGING/lib MINIUPNPC_INCLUDE_PATH=$STAGING/include BDB_LIB_PATH=$STAGING/lib BDB_INCLUDE_PATH=$STAGING/include BOOST_LIB_PATH=$STAGING/lib BOOST_INCLUDE_PATH=$STAGING/include BOOST_LIB_SUFFIX=-mt-s BOOST_THREAD_LIB_SUFFIX=_win32-mt-s OPENSSL_LIB_PATH=$STAGING/lib OPENSSL_INCLUDE_PATH=$STAGING/include QRENCODE_LIB_PATH=$STAGING/lib QRENCODE_INCLUDE_PATH=$STAGING/include USE_QRCODE=1 INCLUDEPATH=$STAGING/include DEFINES=BOOST_THREAD_USE_LIB BITCOIN_NEED_QT_PLUGINS=1 QMAKE_LRELEASE=lrelease QMAKE_CXXFLAGS=-frandom-seed=unobtanium USE_BUILD_INFO=1 USE_SSE2=1 USE_UPNP=-
make clean
make $MAKEOPTS
$HOST-strip release/*-qt.exe
rm -rf $OUTDIR/client
mkdir $OUTDIR/client
cp release/*-qt.exe $OUTDIR/client

# coind
cd src
make -f makefile.linux-mingw clean
make -f makefile.linux-mingw $MAKEOPTS DEPSDIR=$STAGING unobtaniumd.exe USE_UPNP=0 DEBUGFLAGS="-frandom-seed=unobtanium" USE_SSE2=1
$HOST-strip *.exe
rm -rf $OUTDIR/daemon
mkdir $OUTDIR/daemon
cp *.exe $OUTDIR/daemon

. ./nsis.sh