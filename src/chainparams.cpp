// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */
static Checkpoints::MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        ( 0,        uint256S("0x000004c2fc5fffb810dccc197d603690099a68305232e552d96ccbe8e2c52b75"))
        ( 10000,    uint256S("0x000000000009cac39f4ba7dc3dc3bdaabcfdfdea35769fa4475ead20982c5ddf"))
        ( 25000,    uint256S("0x00000000000e71ca092325be6f2049903245deb75a3a90b428ecdd51a2dfae9c"))
        ( 50000,    uint256S("0x000000000002b1b79ab02f97c7e7e0f219ae648484fa1ba8a6efcac2a19d197a"))
        ( 100000,   uint256S("0x0000000000040fb1542b598085adf40d9b69f5284f2ef9305cb2071f7714e681"))
		( 150000,   uint256S("0x00000000000038517177bde8b937af2eed16424e64af730690401e08c8a5e00c"))
		( 200000,	uint256S("0x0000000000007a29a6d40e353c54d3de868f8f8f47b9cf5834cdcaf0dc214023"))
		( 250000,	uint256S("0x00000000000002f102d009610190f6bcf356823259600c7cdc8106ba47b3ee89"))
		( 300000,	uint256S("0x00000000000011c7eec259d9be4694b4460217fc82929ce1e380de371ccf3131"))
		( 350000,	uint256S("0x00000000000078d00a08c6e655d95cbf5011b10676f1b94a106ddb3b9df62202"))
        ( 400000,   uint256S("0x0000000000001833336d69645601662b9252d09d64426e518c1bcf22eca46013"))
        ( 449999,	uint256S("0x000000000000abc7c4e2a51394faa3a6dddbfaf4b8a961724ba47b332356b9de"))	
        ( 450000,   uint256S("0x00000000000037801b25318e156bd65082c6b25758da742df8a4431a4e3350a0"))
        ( 450001,	uint256S("0x00000000000031e9eb8de67ba3299f4d2d96fde10349542a6aab48b46d31e35d"))
        ( 475000,	uint256S("0x0000000000001d0bbf2f2cf5b4994dd13e97a232ef943c3cd6f17270886eefa9"))
        ( 500000,	uint256S("0x0000000000000e8c9abf99b54350a546e6350443fb418db11205688fa09ab594"))
        ( 525000,	uint256S("0x0000000000000b5244cf2d5a8836a76fbbc838573710688fa3739686dc129f21"))
        ( 550000,	uint256S("0x0000000000000c4faf48d3ebafcebe74d016a2e932b634dd88b97588907692e3"))
        ( 630000,	uint256S("0xf16ef330597e3e6ba6f3e425400433f5bbc8e5eab7ff77744c29a24d6c1a632d"))
        ;
static const Checkpoints::CCheckpointData data = {
        &mapCheckpoints,
        1436478823, // * UNIX timestamp of last checkpoint block
        793171,     // * total number of transactions between genesis and last checkpoint
                    //   (the tx=... number in the SetBestChain debug.log lines)
        2880        // * estimated number of transactions per day after checkpoint
   };

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
        ( 0, uint256S("0x000007b02afb00ae826d948d88f4973c00073425f965917f6298b6d280bde021"))
        //( 10000, uint256S("0x0000000d0ad0fcd14d0642755a1ebdabc418dba2bbbb6c9d48f9f5304dd99dff"))
        //( 25000, uint256S("0x00000008a54b0d3e8bcd84b131253009422104de8ecc16ac9fe53fa1a39c2fe4"))
        ;
static const Checkpoints::CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        1531487000,  //1436994107,
        0, //25044,
        0  //2880
    };

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
        boost::assign::map_list_of
        ( 0, uint256S("0f9188f13cb7b2c71f2a335e3a4fc328bf5beb436012afca590b1a11466e2206"))
        ;
static const Checkpoints::CCheckpointData dataRegtest = {
        &mapCheckpointsRegtest,
        0,
        0,
        0
    };

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        /** 
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x03;
        pchMessageStart[1] = 0xd5;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0x03;
        vAlertPubKey = ParseHex("04fd68acb6a895f3462d91b43eef0da845f0d531958a858554feab3ac330562bf76910700b3f7c29ee273ddc4da2bb5b953858f6958a50e8831eb43ee30c32f21d");
        nDefaultPort = 65534;
        bnProofOfWorkLimit = ~uint256(0) >> 20;
        nSubsidyHalvingInterval = 100000;


        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
		nTargetTimespan = 3 * 60; // 3 minutes
		nTargetSpacing = 60; // 30 seconds

        const char* pszTimestamp = "San Francisco plaza evacuated after suspicious package is found";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 1 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock.SetNull();
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1375548986;
        genesis.nBits    = 0x1e0fffff;
        genesis.nNonce   = 1211565;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256S("0x000004c2fc5fffb810dccc197d603690099a68305232e552d96ccbe8e2c52b75"));
        assert(genesis.hashMerkleRoot == uint256S("0x36a192e90f70131a884fe541a1e8a5643a28ba4cb24cbb2924bd0ee483f7f484"));

        vSeeds.push_back(CDNSSeedData("node1.unobtanium.uno", "node1.unobtanium.uno"));
        vSeeds.push_back(CDNSSeedData("node2.unobtanium.uno", "node2.unobtanium.uno"));
        vSeeds.push_back(CDNSSeedData("unobtanium.cryptap.us", "unobtanium.cryptap.us"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,130);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,30);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,224);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fDefaultCheckMemPool = false;
        fAllowMinDifficultyBlocks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {

        strNetworkID = "test";
        pchMessageStart[0] = 0x01;
        pchMessageStart[1] = 0x02;
        pchMessageStart[2] = 0x03;
        pchMessageStart[3] = 0x04;
        vAlertPubKey = ParseHex("0450a15957f7e05910a9ca54fd84a0b555a3563561f3ecbdb6f844f752917f8a8d0041d579022044bb9398dbb7babec4601444fc60870826f3f15afae074213bf4");
        nDefaultPort = 65522;

        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
		nTargetTimespan = 3 * 60; // 3 minutes
		nTargetSpacing = 60; // 30 seconds

        //! Modify the testnet genesis block so the timestamp is valid for a later start.

        /*
	  python genesis.py -z "San Francisco plaza evacuated after suspicious package is found" -t 1531487000 -b 0x1e0fffff -v 100000000

04ffff001d01043f53616e204672616e636973636f20706c617a612065766163756174656420616674657220737573706963696f7573207061636b61676520697320666f756e64
	  algorithm: SHA256
	  merkle hash: 36a192e90f70131a884fe541a1e8a5643a28ba4cb24cbb2924bd0ee483f7f484
	  pszTimestamp: San Francisco plaza evacuated after suspicious package is found
	  pubkey: 04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f
	  time: 1531487000
	  bits: 0x1e0fffff
	  Searching for genesis hash..
	  141232.0 hash/s, estimate: 8.4 h
	  genesis hash found!
	  nonce: 1746468
	  genesis hash: 0x000007b02afb00ae826d948d88f4973c00073425f965917f6298b6d280bde021
        */

        genesis.nTime = 1531487000;//13/07/2018
        genesis.nNonce = 1746468;
        genesis.nBits = 0x1e0fffff;
	//merkle hash: 36a192e90f70131a884fe541a1e8a5643a28ba4cb24cbb2924bd0ee483f7f484
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256S("0x000007b02afb00ae826d948d88f4973c00073425f965917f6298b6d280bde021"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("23skidoo.info", "23skidoo.info"));//Change
        vSeeds.push_back(CDNSSeedData("testnet.unobtanium.uno", "testnet.unobtanium.uno"));//change

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,68);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,30);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x86)(0xCE).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x82)(0x93).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fDefaultCheckMemPool = false;
        fAllowMinDifficultyBlocks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x04;
        pchMessageStart[1] = 0x03;
        pchMessageStart[2] = 0x02;
        pchMessageStart[3] = 0x01;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
		nTargetTimespan = 3 * 60; // 3 minutes
		nTargetSpacing = 60; // 30 seconds
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1375548985;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 1;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 18444;
        assert(hashGenesisBlock == uint256S("0x3868bcc735f32cdd9b42971cdee7bc620c50fada5e3ac5fdfd35630aaf2eb64e"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,0);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,5);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,128);

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultCheckMemPool = true;
        fAllowMinDifficultyBlocks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams {
public:
    CUnitTestParams() {
        strNetworkID = "unittest";
        nDefaultPort = 18444;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultCheckMemPool = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval)  { nSubsidyHalvingInterval=anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority)  { nEnforceBlockUpgradeMajority=anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority)  { nRejectBlockOutdatedMajority=anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority)  { nToCheckBlockUpgradeMajority=anToCheckBlockUpgradeMajority; }
    virtual void setDefaultCheckMemPool(bool afDefaultCheckMemPool)  { fDefaultCheckMemPool=afDefaultCheckMemPool; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) {  fAllowMinDifficultyBlocks=afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams *pCurrentParams = 0;

CModifiableParams *ModifiableParams()
{
   assert(pCurrentParams);
   assert(pCurrentParams==&unitTestParams);
   return (CModifiableParams*)&unitTestParams;
}

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams &Params(CBaseChainParams::Network network) {
    switch (network) {
        case CBaseChainParams::MAIN:
            return mainParams;
        case CBaseChainParams::TESTNET:
            return testNetParams;
        case CBaseChainParams::REGTEST:
            return regTestParams;
        case CBaseChainParams::UNITTEST:
            return unitTestParams;
        default:
            assert(false && "Unimplemented network");
            return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network) {
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
