# Unobtanium Core file system

**Contents**

- [Data directory location](#data-directory-location)

- [Data directory layout](#data-directory-layout)

- [GUI settings](#gui-settings)

- [Notes](#notes)

## Data directory location

The data directory is the default location where the Unobtanium Core files are stored.

1. The default data directory paths for supported platforms are:

Platform | Data directory path
---------|--------------------
Linux    | `$HOME/.unobtanium/`
macOS    | `$HOME/Library/Application Support/Unobtanium/`
Windows  | `%APPDATA%\Unobtanium\` <sup>[\[1\]](#note1)</sup>

2. A custom data directory path can be specified with the `-datadir` option.

3. All content of the data directory, except for `unobtanium.conf` file, is chain-specific. This means the actual data directory paths for non-mainnet cases differ:

Chain option                   | Data directory path
-------------------------------|------------------------------
`-chain=main` (default)        | *path_to_datadir*`/`
`-chain=test` or `-testnet`    | *path_to_datadir*`/testnet/`
`-chain=regtest` or `-regtest` | *path_to_datadir*`/regtest/`

## Data directory layout

Subdirectory       | File(s)               | Description
-------------------|-----------------------|------------
`blocks/`          |                       | Blocks directory; can be specified by `-blocksdir` option (except for `blocks/index/`)
`blocks/index/`    | LevelDB database      | Block index
`blocks/`          | `blkNNNNN.dat`<sup>[\[2\]](#note2)</sup> | Actual Unobtanium blocks (in network format, dumped in raw on disk, 128 MiB per file)
`blocks/`          | `revNNNNN.dat`<sup>[\[2\]](#note2)</sup> | Block undo data (custom format)
`chainstate/`      | LevelDB database      | Blockchain state (a compact representation of all currently unspent transaction outputs (UTXOs) and metadata about the transactions they are from)
`./`               | `banlist.dat`         | Stores the IPs/subnets of banned nodes
`./`               | `unobtanium.conf`        | User-defined [configuration settings](unobtanium-conf.md) for `unobtaniumd` or `unobtanium-qt`. File is not written to by the software and must be created manually. Path can be specified by `-conf` option
`./`               | `debug.log`           | Contains debug information and general logging generated by `unobtaniumd` or `unobtanium-qt`; can be specified by `-debuglogfile` option
`./`               | `fee_estimates.dat`   | Stores statistics used to estimate minimum transaction fees and priorities required for confirmation
`./`               | `peers.dat`           | Peer IP address database (custom format)
`./`               | `wallet.dat`          | Personal wallet (a BDB database) with keys and transactions

## GUI settings

`unobtanium-qt` uses [`QSettings`](https://doc.qt.io/qt-5/qsettings.html) class; this implies platform-specific [locations where application settings are stored](https://doc.qt.io/qt-5/qsettings.html#locations-where-application-settings-are-stored).


## Notes

<a name="note1">1</a>. The `/` (slash, U+002F) is used as the platform-independent path component separator in this document.

<a name="note2">2</a>. `NNNNN` matches `[0-9]{5}` regex.


