#!/bin/bash

set -e

. scripts/include.sh

scripts/pre.sh
scripts/boost.sh
scripts/deps.sh
scripts/qt.sh

