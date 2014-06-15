#!/bin/bash

set -e

export INSTALLPREFIX=$OUTDIR/staging/deps
mkdir -p $INSTALLPREFIX
mkdir -p ~/deps/deps
cd ~/deps/deps

# openssl
wget http://mirrors.ibiblio.org/openssl/source/openssl-1.0.1f.tar.gz
tar xzf openssl-1.0.1f.tar.gz
cd openssl-1.0.1f
./Configure --cross-compile-prefix=$HOST- mingw --openssldir=$INSTALLPREFIX
make
make install_sw
cd ..

# db
wget http://download.oracle.com/berkeley-db/db-4.8.30.NC.tar.gz
tar xzf db-4.8.30.NC.tar.gz
cd db-4.8.30.NC/build_unix
../dist/configure --prefix=$INSTALLPREFIX --enable-mingw --enable-cxx --host=$HOST --disable-shared --disable-replication
make $MAKEOPTS library_build
make install_lib install_include
cd ../..

# miniupnpc 
wget http://miniupnp.free.fr/files/miniupnpc-1.6.tar.gz
tar xzf miniupnpc-1.6.tar.gz
cd miniupnpc-1.6
echo "
--- miniupnpc-1.6/Makefile.mingw.orig   2013-09-29 18:52:51.014087958 -1000
+++ miniupnpc-1.6/Makefile.mingw        2013-09-29 19:09:29.663318691 -1000
@@ -67,8 +67,8 @@
 
 wingenminiupnpcstrings.o:    wingenminiupnpcstrings.c
 
-miniupnpcstrings.h: miniupnpcstrings.h.in wingenminiupnpcstrings
-	wingenminiupnpcstrings \$< \$@
+miniupnpcstrings.h: miniupnpcstrings.h.in 
+	sed -e 's|OS/version|MSWindows/5.1.2600|' -e 's|MINIUPNPC_VERSION_STRING \"version\"|MINIUPNPC_VERSION_STRING \"VERSIONHERE\"|' \$< > \$@
 
 minixml.o:   minixml.c minixml.h miniupnpcstrings.h
 
" | sed "s/VERSIONHERE/$(cat VERSION)/" | patch -l -p1
mkdir -p dll
make -f Makefile.mingw CC=$HOST-gcc AR=$HOST-ar libminiupnpc.a
install -d $INSTALLPREFIX/include/miniupnpc
install -v *.h $INSTALLPREFIX/include/miniupnpc
install -v libminiupnpc.a $INSTALLPREFIX/lib
cd ..

# zlib
wget http://zlib.net/fossils/zlib-1.2.6.tar.gz
tar xzf zlib-1.2.6.tar.gz
cd zlib-1.2.6
CROSS_PREFIX=$HOST- ./configure --prefix=$INSTALLPREFIX --static
make
make install
cd ..

# libpng
wget http://ftp.sunet.se/pub/multimedia/graphics/ImageMagick/delegates/libpng-1.5.9.tar.gz
tar xzf libpng-1.5.9.tar.gz
cd libpng-1.5.9
CFLAGS="-I$INSTALLPREFIX/include" LDFLAGS="-L$INSTALLPREFIX/lib" ./configure --disable-shared --prefix=$INSTALLPREFIX --host=$HOST
make $MAKEOPTS
make install
cd ..

# qrencode
wget http://fukuchi.org/works/qrencode/qrencode-3.2.0.tar.bz2
tar xjf qrencode-3.2.0.tar.bz2
cd qrencode-3.2.0
png_CFLAGS="-I$INSTALLPREFIX/include" png_LIBS="-L$INSTALLPREFIX/lib -lpng" ./configure --prefix=$INSTALLPREFIX --host=$HOST
make
make install
cd ..

# libevent
wget https://github.com/downloads/libevent/libevent/libevent-2.0.21-stable.tar.gz
tar xf libevent-2.0.21-stable.tar.gz
cd libevent-2.0.21-stable
./configure --prefix=$INSTALLPREFIX --host=$HOST --enable-static
make
make install

# save compile results
cd $INSTALLPREFIX
zip -r $OUTDIR/bitcoin-deps-win32-gitian-r9.zip include lib





