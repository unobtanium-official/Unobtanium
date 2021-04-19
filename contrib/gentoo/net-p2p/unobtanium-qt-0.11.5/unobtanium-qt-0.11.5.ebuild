# Copyright 2010-2019 Gentoo Authors
# Distributed under the terms of the GNU General Public License v2

EAPI=5

DESCRIPTION="An end-user Qt GUI for the Unobtanium crypto-currency"
LICENSE="DWTFYW"
HOMEPAGE="http://unobtanium.uno/"
SLOT="0"
SRC_URI="http://unobtanium.uno/src/v0.11.5/Unobtanium-0.11.5.tar.gz -> unobtanium-0.11.5.tar.gz"

DB_VER="4.8"
inherit autotools bash-completion-r1 db-use gnome2-utils xdg-utils

SLOT="0"
KEYWORDS="~amd64 ~arm ~arm64 ~ppc ~ppc64 ~x86 ~amd64-linux ~x86-linux"

IUSE="+asm dbus kde bip70 evo +libressl +qrcode +system-leveldb test upnp +wallet zeromq"

RDEPEND="
	>=dev-libs/boost-1.52.0:=[threads(+)]
	>=dev-libs/univalue-1.0.4:=
	dev-qt/qtcore:5
	dev-qt/qtgui:5
	dev-qt/qtnetwork:5
	dev-qt/qtwidgets:5
	system-leveldb? ( virtual/bitcoin-leveldb )
	bip70? ( dev-libs/protobuf:= )
	dbus? ( dev-qt/qtdbus:5 )
	dev-libs/libevent:=
	!libressl? ( dev-libs/openssl:0=[-bindist] )
	libressl? ( dev-libs/libressl:0= )
	qrcode? (
		media-gfx/qrencode:=
	)
	upnp? ( >=net-libs/miniupnpc-1.9.20150916:= )
	wallet? ( sys-libs/db:$(db_ver_to_slot "${DB_VER}")=[cxx] )
	zeromq? ( net-libs/zeromq:= )
"
DEPEND="${RDEPEND}
	dev-qt/linguist-tools:5
	evo? (
		gnome-base/librsvg
		media-gfx/imagemagick[png]
	)
"

DOCS=( doc/files.md doc/release-notes.md doc/REST-interface.md doc/tor.md )

S="${WORKDIR}/Unobtanium"

pkg_pretend() {
		elog "You are building ${PN} from Unobtanium Core."
		elog "For more information, see:"
		elog "http://unobtanium.uno/release/release-${PV}/"
}

src_prepare() {

	# Save the generic icon for later
	cp src/qt/res/src/bitcoin.svg bitcoin128.svg || die

	echo '#!/bin/true' >share/genbuild.sh || die
	mkdir -p src/obj || die
	echo "#define BUILD_SUFFIX gentoo${PVR#${PV}}" >src/obj/build.h || die

	eautoreconf
}

src_configure() {
	local my_econf=(
		$(use_enable asm)
		$(use_enable bip70)
		$(use_with dbus qtdbus)
		$(use_with qrcode qrencode)
		$(use_with upnp miniupnpc)
		$(use_enable upnp upnp-default)
		$(use_enable test tests)
		$(use_enable wallet)
		$(use_enable zeromq zmq)
		--with-gui=qt5
		--disable-util-cli
		--disable-util-tx
		--disable-util-wallet
		--disable-bench
		--without-libs
		--without-rapidcheck
		--disable-fuzz
		--disable-ccache
                --disable-tests
		--with-system-univalue
	)
	econf "${my_econf[@]}"
}

src_install() {
	default

	insinto /usr/share/icons/hicolor/scalable/apps/
	doins bitcoin128.svg
	if use evo; then
		newins src/qt/res/src/bitcoin.svg unobtanium.svg
	fi
}

update_caches() {
	gnome2_icon_cache_update
	xdg_desktop_database_update
}

pkg_postinst() {
	update_caches

	elog "To have ${PN} automatically use Tor when it's running, be sure your"
	elog "'torrc' config file has 'ControlPort' and 'CookieAuthentication' setup"
	elog "correctly, and add your user to the 'tor' user group."
}

pkg_postrm() {
	update_caches
}
