Unobtanium Core 0.10.4.1
=====================

Setup
---------------------
[Unobtanium Core](http://Unobtanium.uno/en/download) is the original Unobtanium client and it builds the backbone of the network. However, it downloads and stores the entire history of Unobtanium transactions (which is currently several GBs); depending on the speed of your computer and network connection, the synchronization process can take anywhere from a few hours to a day or more.

Running
---------------------
The following are some helpful notes on how to run Unobtanium on your native platform. 

### Unix

You need the Qt4 run-time libraries to run Unobtanium-Qt. On Debian or Ubuntu:

	sudo apt-get install libqtgui4

Unpack the files into a directory and run:

- bin/32/unobtanium-qt (GUI, 32-bit) or bin/32/unobtaniumd (headless, 32-bit)
- bin/64/unobtanium-qt (GUI, 64-bit) or bin/64/unobtaniumd (headless, 64-bit)



### Windows

Unpack the files into a directory, and then run unobtanium-qt.exe.

### OSX

Drag Unobtanium-Qt to your applications folder, and then run Unobtanium-Qt.

### Need Help?

* See the documentation at the [Unobtanium Wiki](https://unobtanium.uno/wiki)
for help and more information.
* Ask for help on [#bitcoin](http://webchat.freenode.net?channels=unobtanium) on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net?channels=bitcoin).
* Ask for help on the [BitcoinTalk](https://bitcointalk.org/) forums, in the [Technical Support board](https://bitcointalk.org/index.php?topic=527500.0).

Building
---------------------
The following are developer notes on how to build Unobtanium on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

- [OSX Build Notes](build-osx.md)
- [Unix Build Notes](build-unix.md)

Development
---------------------
The Unobtanium repo's [root README](https://github.com/Flurbos/Unobtanium/blob/master/README.md) contains relevant information on the development process and automated testing.

- [Developer Notes](developer-notes.md)
- [Multiwallet Qt Development](multiwallet-qt.md)
- [Release Notes](release-notes.md)
- [Release Process](release-process.md)
- [Source Code Documentation (External Link)](https://dev.visucore.com/bitcoin/doxygen/)
- [Translation Process](translation_process.md)
- [Unit Tests](unit-tests.md)

### Resources
* Discuss on the [BitcoinTalk](https://bitcointalk.org/) forums, in the [Development & Technical Discussion board](https://bitcointalk.org/index.php?topic=527500.0).
* Discuss on [#unobtanium-dev](http://webchat.freenode.net/?channels=bitcoin) on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net/?channels=unobtanium-dev).

### Miscellaneous
- [Assets Attribution](assets-attribution.md)
- [Files](files.md)
- [Tor Support](tor.md)
- [Init Scripts (systemd/upstart/openrc)](init.md)

License
---------------------
Distributed under the [MIT software license](http://www.opensource.org/licenses/mit-license.php).
This product includes software developed by the OpenSSL Project for use in the [OpenSSL Toolkit](https://www.openssl.org/). This product includes
cryptographic software written by Eric Young ([eay@cryptsoft.com](mailto:eay@cryptsoft.com)), and UPnP software written by Thomas Bernard.
