ACLOCAL_AMFLAGS = -I build-aux/m4
DIST_SUBDIRS = secp256k1
AM_LDFLAGS = $(PTHREAD_CFLAGS) $(LIBTOOL_LDFLAGS)


if EMBEDDED_LEVELDB
LEVELDB_CPPFLAGS += -I$(srcdir)/leveldb/include
LEVELDB_CPPFLAGS += -I$(srcdir)/leveldb/helpers/memenv
LIBLEVELDB += $(builddir)/leveldb/libleveldb.a
LIBMEMENV  += $(builddir)/leveldb/libmemenv.a

# NOTE: This dependency is not strictly necessary, but without it make may try to build both in parallel, which breaks the LevelDB build system in a race
$(LIBLEVELDB): $(LIBMEMENV)

$(LIBLEVELDB) $(LIBMEMENV):
	@echo "Building LevelDB ..." && $(MAKE) -C $(@D) $(@F) CXX="$(CXX)" \
	  CC="$(CC)" PLATFORM=$(TARGET_OS) AR="$(AR)" $(LEVELDB_TARGET_FLAGS) \
          OPT="$(CXXFLAGS) $(CPPFLAGS)"
endif

UNOBTANIUM_CONFIG_INCLUDES=-I$(builddir)/config
UNOBTANIUM_INCLUDES=-I$(builddir) -I$(builddir)/obj $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS) $(CRYPTO_CFLAGS) $(SSL_CFLAGS)

UNOBTANIUM_INCLUDES += -I$(srcdir)/secp256k1/include

LIBUNOBTANIUM_SERVER=libunobtanium_server.a
LIBUNOBTANIUM_WALLET=libunobtanium_wallet.a
LIBUNOBTANIUM_COMMON=libunobtanium_common.a
LIBUNOBTANIUM_CLI=libunobtanium_cli.a
LIBUNOBTANIUM_UTIL=libunobtanium_util.a
LIBUNOBTANIUM_CRYPTO=crypto/libunobtanium_crypto.a
LIBUNOBTANIUM_UNIVALUE=univalue/libunobtanium_univalue.a
LIBUNOBTANIUMQT=qt/libunobtaniumqt.a
LIBSECP256K1=secp256k1/libsecp256k1.la

$(LIBSECP256K1): $(wildcard secp256k1/src/*) $(wildcard secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES = \
  crypto/libunobtanium_crypto.a \
  libunobtanium_util.a \
  libunobtanium_common.a \
  univalue/libunobtanium_univalue.a \
  libunobtanium_server.a \
  libunobtanium_cli.a
if ENABLE_WALLET
UNOBTANIUM_INCLUDES += $(BDB_CPPFLAGS)
EXTRA_LIBRARIES += libunobtanium_wallet.a
endif

if BUILD_UNOBTANIUM_LIBS
lib_LTLIBRARIES = libunobtaniumconsensus.la
LIBUNOBTANIUM_CONSENSUS=libunobtaniumconsensus.la
else
LIBUNOBTANIUM_CONSENSUS=
endif

bin_PROGRAMS =
TESTS =

if BUILD_UNOBTANIUMD
  bin_PROGRAMS += unobtaniumd
endif

if BUILD_UNOBTANIUM_UTILS
  bin_PROGRAMS += unobtanium-cli unobtanium-tx
endif

.PHONY: FORCE
# unobtanium core #
UNOBTANIUM_CORE_H = \
  addrman.h \
  alert.h \
  allocators.h \
  amount.h \
  auxpow.h \
  base58.h \
  bignum.h \
  bloom.h \
  chain.h \
  chainparamsbase.h \
  chainparams.h \
  chainparamsseeds.h \
  checkpoints.h \
  checkqueue.h \
  clientversion.h \
  wallet/coincontrol.h \
  coins.h \
  compat.h \
  compressor.h \
  core_io.h \
  walllet/crypter.h \
  wallet/db.h \
  eccryptoverify.h \
  ecwrapper.h \
  hash.h \
  init.h \
  key.h \
  keystore.h \
  leveldbwrapper.h \
  limitedmap.h \
  main.h \
  merkleblock.h \
  miner.h \
  mruset.h \
  netbase.h \
  net.h \
  noui.h \
  pow.h \
  primitives/block.h \
  primitives/transaction.h \
  protocol.h \
  pubkey.h \
  random.h \
  rpcclient.h \
  rpcprotocol.h \
  rpcserver.h \
  script/interpreter.h \
  script/script_error.h \
  script/script.h \
  script/sigcache.h \
  script/sign.h \
  script/standard.h \
  serialize.h \
  streams.h \
  sync.h \
  threadsafety.h \
  timedata.h \
  tinyformat.h \
  txdb.h \
  txmempool.h \
  ui_interface.h \
  uint256.h \
  undo.h \
  util.h \
  utilmoneystr.h \
  utilstrencodings.h \
  utiltime.h \
  version.h \
  wallet/walletdb.h \
  wallet/wallet.h \
  wallet/wallet_ismine.h \
  compat/sanity.h

obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh $(abs_top_builddir)/src/obj/build.h \
	  $(abs_top_srcdir)
libunobtanium_util_a-clientversion.$(OBJEXT): obj/build.h

# server: shared between unobtaniumd and unobtanium-qt
libunobtanium_server_a_CPPFLAGS = $(UNOBTANIUM_INCLUDES) $(MINIUPNPC_CPPFLAGS)
libunobtanium_server_a_SOURCES = \
  addrman.cpp \
  alert.cpp \
  bloom.cpp \
  chain.cpp \
  checkpoints.cpp \
  init.cpp \
  leveldbwrapper.cpp \
  main.cpp \
  merkleblock.cpp \
  miner.cpp \
  net.cpp \
  noui.cpp \
  pow.cpp \
  rest.cpp \
  rpcblockchain.cpp \
  rpcmining.cpp \
  rpcmisc.cpp \
  rpcnet.cpp \
  wallet/rpcrawtransaction.cpp \
  rpcserver.cpp \
  script/sigcache.cpp \
  timedata.cpp \
  txdb.cpp \
  txmempool.cpp \
  $(UNOBTANIUM_CORE_H)

# wallet: shared between unobtaniumd and unobtanium-qt, but only linked
# when wallet enabled
libunobtanium_wallet_a_CPPFLAGS = $(UNOBTANIUM_INCLUDES)
libunobtanium_wallet_a_SOURCES = \
  wallet/db.cpp \
  wallet/crypter.cpp \
  wallet/rpcdump.cpp \
  wallet/rpcwallet.cpp \
  wallet/wallet.cpp \
  wallet/wallet_ismine.cpp \
  wallet/walletdb.cpp \
  $(UNOBTANIUM_CORE_H)

# crypto primitives library
crypto_libunobtanium_crypto_a_CPPFLAGS = $(UNOBTANIUM_CONFIG_INCLUDES)
crypto_libunobtanium_crypto_a_SOURCES = \
  crypto/sha1.cpp \
  crypto/sha256.cpp \
  crypto/sha512.cpp \
  crypto/hmac_sha256.cpp \
  crypto/hmac_sha512.cpp \
  crypto/ripemd160.cpp \
  crypto/common.h \
  crypto/sha256.h \
  crypto/sha512.h \
  crypto/hmac_sha256.h \
  crypto/hmac_sha512.h \
  crypto/sha1.h \
  crypto/ripemd160.h

# univalue JSON library
univalue_libunobtanium_univalue_a_SOURCES = \
  univalue/univalue.cpp \
  univalue/univalue_read.cpp \
  univalue/univalue_write.cpp \
  univalue/univalue_escapes.h \
  univalue/univalue.h

# common: shared between unobtaniumd, and unobtanium-qt and non-server tools
libunobtanium_common_a_CPPFLAGS = $(UNOBTANIUM_INCLUDES)
libunobtanium_common_a_SOURCES = \
  allocators.cpp \
  amount.cpp \
  auxpow.cpp \
  base58.cpp \
  chainparams.cpp \
  coins.cpp \
  compressor.cpp \
  primitives/block.cpp \
  primitives/transaction.cpp \
  core_read.cpp \
  core_write.cpp \
  eccryptoverify.cpp \
  ecwrapper.cpp \
  hash.cpp \
  key.cpp \
  keystore.cpp \
  netbase.cpp \
  protocol.cpp \
  pubkey.cpp \
  script/interpreter.cpp \
  script/script.cpp \
  script/sign.cpp \
  script/standard.cpp \
  script/script_error.cpp \
  $(UNOBTANIUM_CORE_H)

# util: shared between all executables.
# This library *must* be included to make sure that the glibc
# backward-compatibility objects and their sanity checks are linked.
libunobtanium_util_a_CPPFLAGS = $(UNOBTANIUM_INCLUDES)
libunobtanium_util_a_SOURCES = \
  chainparamsbase.cpp \
  clientversion.cpp \
  compat/glibc_sanity.cpp \
  compat/glibcxx_sanity.cpp \
  compat/strnlen.cpp \
  random.cpp \
  rpcprotocol.cpp \
  sync.cpp \
  uint256.cpp \
  util.cpp \
  utilmoneystr.cpp \
  utilstrencodings.cpp \
  utiltime.cpp \
  $(UNOBTANIUM_CORE_H)

if GLIBC_BACK_COMPAT
libunobtanium_util_a_SOURCES += compat/glibc_compat.cpp
endif

# cli: shared between unobtanium-cli and unobtanium-qt
libunobtanium_cli_a_CPPFLAGS = $(UNOBTANIUM_INCLUDES)
libunobtanium_cli_a_SOURCES = \
  rpcclient.cpp \
  $(UNOBTANIUM_CORE_H)

nodist_libunobtanium_util_a_SOURCES = $(srcdir)/obj/build.h
#

# unobtaniumd binary #
unobtaniumd_SOURCES = unobtaniumd.cpp
unobtaniumd_CPPFLAGS = $(UNOBTANIUM_INCLUDES)
unobtaniumd_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
unobtaniumd_SOURCES += unobtaniumd-res.rc
endif

unobtaniumd_LDADD = \
  $(LIBUNOBTANIUM_SERVER) \
  $(LIBUNOBTANIUM_COMMON) \
  $(LIBUNOBTANIUM_UNIVALUE) \
  $(LIBUNOBTANIUM_UTIL) \
  $(LIBUNOBTANIUM_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBMEMENV) \
  $(LIBSECP256K1)

if ENABLE_WALLET
unobtaniumd_LDADD += libunobtanium_wallet.a
endif

unobtaniumd_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(MINIUPNPC_LIBS)
#

# unobtanium-cli binary #
unobtanium_cli_SOURCES = unobtanium-cli.cpp
unobtanium_cli_CPPFLAGS = $(UNOBTANIUM_INCLUDES)
unobtanium_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
unobtanium_cli_SOURCES += unobtanium-cli-res.rc
endif

unobtanium_cli_LDADD = \
  $(LIBUNOBTANIUM_CLI) \
	$(LIBUNOBTANIUM_UNIVALUE) \
  $(LIBUNOBTANIUM_UTIL)

unobtanium_cli_LDADD += $(BOOST_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS)
#

# unobtanium-tx binary #
unobtanium_tx_SOURCES = unobtanium-tx.cpp
unobtanium_tx_CPPFLAGS = $(UNOBTANIUM_INCLUDES)
unobtanium_tx_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

unobtanium_tx_LDADD = \
  $(LIBUNOBTANIUM_UNIVALUE) \
  $(LIBUNOBTANIUM_COMMON) \
  $(LIBUNOBTANIUM_UTIL) \
  $(LIBUNOBTANIUM_CRYPTO) \
  $(LIBSECP256K1)

unobtanium_tx_LDADD += $(BOOST_LIBS) $(CRYPTO_LIBS)
#

# unobtaniumconsensus library #
if BUILD_UNOBTANIUM_LIBS
include_HEADERS = script/unobtaniumconsensus.h
libunobtaniumconsensus_la_SOURCES = \
  crypto/hmac_sha512.cpp \
  crypto/ripemd160.cpp \
  crypto/sha1.cpp \
  crypto/sha256.cpp \
  crypto/sha512.cpp \
  eccryptoverify.cpp \
  ecwrapper.cpp \
  hash.cpp \
  primitives/transaction.cpp \
  pubkey.cpp \
  script/unobtaniumconsensus.cpp \
  script/interpreter.cpp \
  script/script.cpp \
  uint256.cpp \
  utilstrencodings.cpp

if GLIBC_BACK_COMPAT
  libunobtaniumconsensus_la_SOURCES += compat/glibc_compat.cpp
endif

libunobtaniumconsensus_la_LDFLAGS = -no-undefined $(RELDFLAGS)
libunobtaniumconsensus_la_LIBADD = $(CRYPTO_LIBS)
libunobtaniumconsensus_la_CPPFLAGS = $(CRYPTO_CFLAGS) -I$(builddir)/obj -DBUILD_UNOBTANIUM_INTERNAL

if USE_LIBSECP256K1
libunobtaniumconsensus_la_LIBADD += secp256k1/libsecp256k1.la
endif
endif
#

CLEANFILES = leveldb/libleveldb.a leveldb/libmemenv.a *.gcda *.gcno

DISTCLEANFILES = obj/build.h

EXTRA_DIST = leveldb

clean-local:
	-$(MAKE) -C leveldb clean
	-$(MAKE) -C secp256k1 clean
	rm -f leveldb/*/*.gcno leveldb/helpers/memenv/*.gcno
	-rm -f config.h

.rc.o:
	@test -f $(WINDRES)
	$(AM_V_GEN) $(WINDRES) -DWINDRES_PREPROC -i $< -o $@

.mm.o:
	$(AM_V_CXX) $(OBJCXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	  $(CPPFLAGS) $(AM_CXXFLAGS) $(QT_INCLUDES) $(CXXFLAGS)  -c -o $@ $<

%.pb.cc %.pb.h: %.proto
	@test -f $(PROTOC)
	$(AM_V_GEN) $(PROTOC) --cpp_out=$(@D) --proto_path=$(abspath $(<D) $<)

if ENABLE_TESTS
include Makefile.test.include
endif

if ENABLE_QT
include Makefile.qt.include
endif

if ENABLE_QT_TESTS
include Makefile.qttest.include
endif
