#!/bin/bash
# create multiresolution windows icon
ICON_SRC=../../src/qt/res/icons/unobtanium.png
ICON_DST=../../src/qt/res/icons/unobtanium.ico
convert ${ICON_SRC} -resize 16x16 unobtanium-16.png
convert ${ICON_SRC} -resize 32x32 unobtanium-32.png
convert ${ICON_SRC} -resize 48x48 unobtanium-48.png
convert unobtanium-16.png unobtanium-32.png unobtanium-48.png ${ICON_DST}

