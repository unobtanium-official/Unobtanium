// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_POW_H
#define BITCOIN_POW_H

#include <stdint.h>
#include <cmath>
#include "bignum.h"

class CBlockHeader;
class CBlockIndex;
class uint256;

unsigned int GetNextWorkRequired(const CBlockIndex* pindexLast, const CBlockHeader *pblock);

/** Check whether a block hash satisfies the proof-of-work requirement specified by nBits */
bool CheckProofOfWork(uint256 hash, unsigned int nBits);
bool CheckBlockProofOfWork(const CBlockHeader *pblock);
uint256 GetBlockProof(const CBlockIndex& block);
static const int PROOF_OF_WORK_FORK_BLOCK_MAINNET = 450000;
static const int PROOF_OF_WORK_FORK_BLOCK_TESTNET = 50;
static const CBigNum cbnProofOfWorkLimit(~uint256(0) >> 20);

static const int64_t nTargetTimespan = 3 * 60; // 3 minutes
static const int64_t nTargetSpacing = 60; // 30 seconds
static const int64_t nInterval = nTargetTimespan / nTargetSpacing; 

static const int64_t nAveragingInterval = nInterval * 20;
static const int64_t nAveragingTargetTimespan = nAveragingInterval * nTargetSpacing; 

static const int64_t nMaxAdjustDown = 20; // 20% adjustment down
static const int64_t nMaxAdjustUp = 10; // 10% adjustment up

static const int64_t nTargetTimespanAdjDown = nTargetTimespan * (100 + nMaxAdjustDown) / 100;

static const int64_t nMinActualTimespan = nAveragingTargetTimespan * (100 - nMaxAdjustUp) / 100;
static const int64_t nMaxActualTimespan = nAveragingTargetTimespan * (100 + nMaxAdjustDown) / 100;


#endif // BITCOIN_POW_H
