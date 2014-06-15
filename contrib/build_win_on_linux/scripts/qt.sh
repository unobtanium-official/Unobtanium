#!/bin/bash

set -e

mkdir ~/deps/qt
cd ~/deps/qt
export INSTDIR="$HOME/qt/"
mkdir $INSTDIR
mkdir -p $INSTDIR/host/bin
wget http://pkgs.fedoraproject.org/repo/pkgs/qt/qt-everywhere-opensource-src-4.8.3.tar.gz/a663b6c875f8d7caa8ac9c30e4a4ec3b/qt-everywhere-opensource-src-4.8.3.tar.gz
unzip $OUTDIR/bitcoin-deps-win32-gitian-r9.zip
DEPSDIR=`pwd`
tar xzf qt-everywhere-opensource-src-4.8.3.tar.gz
cd qt-everywhere-opensource-src-4.8.3
sed 's/$TODAY/2011-01-30/' -i configure
sed "s/i686-pc-mingw32-/$HOST-/" -i mkspecs/unsupported/win32-g++-cross/qmake.conf
sed --posix "s|QMAKE_CFLAGS\t\t= -pipe|QMAKE_CFLAGS\t\t= -pipe -isystem /usr/$HOST/include/ -frandom-seed=qtbuild|" -i mkspecs/unsupported/win32-g++-cross/qmake.conf
sed 's/QMAKE_CXXFLAGS_EXCEPTIONS_ON = -fexceptions -mthreads/QMAKE_CXXFLAGS_EXCEPTIONS_ON = -fexceptions/' -i mkspecs/unsupported/win32-g++-cross/qmake.conf
sed 's/QMAKE_LFLAGS_EXCEPTIONS_ON = -mthreads/QMAKE_LFLAGS_EXCEPTIONS_ON = -lmingwthrd/' -i mkspecs/unsupported/win32-g++-cross/qmake.conf
sed --posix "s/QMAKE_MOC\t\t= $HOST-moc/QMAKE_MOC\t\t= moc/" -i mkspecs/unsupported/win32-g++-cross/qmake.conf
sed --posix "s/QMAKE_RCC\t\t= $HOST-rcc/QMAKE_RCC\t\t= rcc/" -i mkspecs/unsupported/win32-g++-cross/qmake.conf
sed --posix "s/QMAKE_UIC\t\t= $HOST-uic/QMAKE_UIC\t\t= uic/" -i mkspecs/unsupported/win32-g++-cross/qmake.conf
OPENSSL_LIBS="-L$DEPSDIR/lib -lssl -lcrypto -lgdi32" ./configure -prefix $INSTDIR -bindir $INSTDIR/host/bin -I $DEPSDIR/include -confirm-license -release -opensource -static -no-qt3support -xplatform unsupported/win32-g++-cross -no-multimedia -no-audio-backend -no-phonon -no-phonon-backend -no-declarative -no-script -no-scripttools -no-javascript-jit -no-webkit -no-svg -no-xmlpatterns -no-sql-sqlite -no-nis -no-cups -no-iconv -no-dbus -no-gif -no-libtiff -no-opengl -nomake examples -nomake demos -nomake docs -no-feature-style-plastique -no-feature-style-cleanlooks -no-feature-style-motif -no-feature-style-cde -no-feature-style-windowsce -no-feature-style-windowsmobile -no-feature-style-s60 -openssl-linked
find . -name *.prl | xargs -l sed 's|/\.||' -i
find . -name *.prl | xargs -l sed 's|/$||' -i
make $MAKEOPTS install
cd $INSTDIR
find . -name *.prl | xargs -l sed 's|/$||' -i
zip -r $OUTDIR/qt-win32-4.8.3-gitian-r4.zip *

