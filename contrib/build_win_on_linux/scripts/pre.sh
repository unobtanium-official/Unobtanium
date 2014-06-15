#!/bin/bash

set -e

rm -rf ~/deps ~/out ~/staging ~/qt

sudo apt-get install -y mingw-w64 g++-mingw-w64 faketime zip build-essential psmisc nsis git

mkdir ~/deps ~/out

