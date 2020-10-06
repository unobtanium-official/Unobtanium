#!/usr/bin/env bash
###################
# makeseeds.sh
###################
set -eu
set -o pipefail
###################
SERVER="https://chainz.cryptoid.info/uno/api.dws?q=nodes"
###################

curl -sSL ${SERVER} | grep -E -o "([0-9]{1,3}[\.]){3}[0-9]{1,3}" | sed '/^0/d' | sed 's/$/:65534/' > nodes_main.txt


echo -e "[\033[32mdone!\033[0m]"
echo "Seeds file written to nodes_main.txt"



