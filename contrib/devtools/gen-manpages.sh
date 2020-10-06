#!/usr/bin/env bash
# Copyright (c) 2016-2019 The Bitcoin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

export LC_ALL=C
TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
BUILDDIR=${BUILDDIR:-$TOPDIR}

BINDIR=${BINDIR:-$BUILDDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

UNOBTANIUMD=${UNOBTANIUMD:-$BINDIR/unobtaniumd}
UNOBTANIUMCLI=${UNOBTANIUMCLI:-$BINDIR/unobtanium-cli}
UNOBTANIUMTX=${UNOBTANIUMTX:-$BINDIR/unobtanium-tx}
UNOBTANIUMQT=${UNOBTANIUMQT:-$BINDIR/qt/unobtanium-qt}

[ ! -x $UNOBTANIUMD ] && echo "$UNOBTANIUMD not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
read -r -a BTCVER <<< "$($UNOBTANIUMCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }')"

# Create a footer file with copyright content.
# This gets autodetected fine for unobtaniumd if --version-string is not set,
# but has different outcomes for unobtanium-qt and unobtanium-cli.
echo "[COPYRIGHT]" > footer.h2m
$UNOBTANIUMD --version | sed -n '1!p' >> footer.h2m

for cmd in $UNOBTANIUMD $UNOBTANIUMCLI $UNOBTANIUMTX $UNOBTANIUMQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${BTCVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${BTCVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
