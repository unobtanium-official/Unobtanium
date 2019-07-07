Unobtanium Core version 0.11.0.0-alpha is now available from:

  https://github.com/sherlockcoin/Unobtanium (Will be updated once merged to master fork branch)

Project [UNIFYING] is a development initiative to revamp Unobtanium Core Development and bring about upgraded and updated and security fixes to the Unobtanium Core functionality and also the code base to act as a centralized collective and updated point for developers to work on, it will also bring about major Unobtanium Improvement Proposals (UIPs) and a full feature updates in the coming times.

Please report bugs using the issue tracker at github:

  https://github.com/sherlockcoin/Unobtanium/issues

Upgrading and downgrading
==========================

How to Upgrade
--------------

If you are running an older version, shut it down. Wait until it has completely
shut down (which might take a few minutes for older versions), then run the
installer (on Windows) or just copy over /Applications/Unobtanium-Qt (on Mac) or
unobtaniumd/unobtanium-qt (on Linux).

If you are upgrading from version 0.10.5.0 or earlier, the first time you run
0.11.0.0-alpha your blockchain files will be re-indexed, which will take anywhere from
30 minutes to several hours, depending on the speed of your machine.

Downgrading warnings
--------------------

There are currently no downgrade complications reported so far, if so found this part of the release notes will be updated.

Detailed release notes follow. This overview includes changes that affect behavior, not code moves, refactors and string updates. For convenience in locating the code changes and accompanying discussion, both the pull request and git merge commit are mentioned.

0.11.0.0-alpha Release notes * Strict Semantic Versioning to follow hereafter.
==============================================================================

bb79a91 [UNIFYING][CORE]Fixes getnetworkhashps overflow
3d4f18d [UNIFYING][CORE]Minor/Major Version Update Start of UNIFYING PROJECT
870a5a2 [UNIFYING][CORE]Unifying Positive Start
8ba3b28 [UNIFYING][CORE] Typo Fix
48f83c0 [UNIFYING][CORE]Introduce separate 'generate' RPC, call leaves these
dfb17a1 [UNIFYING][CORE]Remove fSkipProofOfWork
5f099b6 [UNIFYING][CORE]Remove UNITTEST params
1ff056d [UNIFYING][CORE]Move Only
209568e [UNIFYING][CORE]arith_uint256 is still new
c534d58 [UNIFYING][CORE]Introducing Consensus::Params class
d18078c [UNIFYING][CORE]Introducing Consensus::Params class
4dbccf3 [UNIFYING][CORE]Store mapCheckpoints in CCheckpointData
e6cb72d [UNIFYING][CORE]Created consensus/consensus.h with some constants
271356e [UNIFYING][CORE]Show zero value txouts in listunspent.
6b5e82e [UNIFYING][CORE]Fix listunspent code indentation
765ce01 [UNIFYING][CORE]Push down RPC reqWallet flag
66ae88b [UNIFYING][CORE]Moving listunspent to wallet/rpcwallet.cpp
c641f7d [UNIFYING][CORE]String change in wallet.cpp
d9f8cc7 [UNIFYING][CORE]Defining CTransaction::IsEquivalentTo functions
1f7b3fb [UNIFYING][CORE]Start re-implementing AUXPOW function
a47945b [UNIFYING][CORE]Start re-implementing AUXPOW function
a723542 [UNIFYING][CORE]Temporarily removing AUXPOW implementation.
a41b372 [UNIFYING][CORE]New Regression test for ResendWalletTransactions
1cb4ca6 [UNIFYING][CORE]Restriction to disable transaction broadcast
bc7e8bf [UNIFYING][CORE]Main.h will not be used from anyother header
6a60c6a  [UNIFYING][CORE]New Regression test for ResendWalletTransactions
9ad3913 [UNIFYING][CORE]Main.h will not be used from anyother header
4a141ef [UNIFYING][CORE]New Regression test for ResendWalletTransactions
60db097 [UNIFYING][CORE]Main.h will not be used from anyother header.
22da0b5 [UNIFYING][CORE]Moving more method definitions out of wallet.h
767e583 [UNIFYING][CORE] use constant references for strings in functions
215afb4 [UNIFYING][CORE] sort pending wallet transactions before reaccepting
25708e8 [UNIFYING][CORE] refactoring: move bdb (bitdb) interaction
1adaf82 [OSX] Finder Icon Fix
7f40eaf [OSX] Library issue fix OSX > 10.10
2f3a6bd [COMPILE] boost 1.66 compile error fix
a4dd450 [ORGANIZE] Move wallet related things to src/wallet/
3c9c455 [ORGANIZE] Move wallet related things to src/wallet/
929bfbd Unontanium-qt usage message
a5283eb Help messages unificiation
611b402 1) Updated Hard-Coded Seed Nodes

Please support development efforts:

UNO : ub6bVwcpR2uXeKU8QBjpVjg9roKojdUuXB
BTC : 17kCPd1ShEC2yWRkdndeKRhJbYBftVhmR2

Credits & Shout-out
-------------------

To the amazing fellow developers and the entire Unobtanium community.
