Version 0.11.6 is now available.
===

Features:  
* Updated info in getblockchain info rpc call - now returns **pruned:** _false_ and **initialblocksdownloaded:** _true/false_
* Updated getrawtransaction - can now accept bool for verbose output as well as numeric values ( any number but 0 is true ).
* Updated bitrpc.py changed ports to unobtanium ports - though probably will remove this file later as bitcoin did due to other issues.
* Added getblockheader rpc call - _Alternative to getblock that works even when the block itself has been pruned, returning all available information. Right now the fact that you can't get this information in pruned mode makes pruned nodes quite a bit less useful for some applications._
* Converted entire source tree from json_spirit to UniValue, Brings uno closer to a full 12.0 release
* Fixed rpcmining/getblocktemplate univalue transition logic error

**NOTES**    
* _Although getblockheader isn't actually needed right now since there is no pruning enabled, some projects use getblockheader and will make porting them easier_

Donate to show appreciation for this update:    
**Unobtanium-**    
```uVVuwXm2mDK9pr9XkWT5k7ihQyoSC8y2MW```     
**Bitcoin-**   
```bc1qqfv8rh0n0fr9c8kut584lxk0403pypm0rk7ygs```    

__Download:__
---

_Release Binaries will be available from Unobtanium.uno, or the official unobtanium uno if not there yet:_
