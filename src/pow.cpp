// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Nautiluscoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "pow.h"

#include "chain.h"
#include "chainparams.h"
#include "primitives/block.h"
#include "auxpow.h"
#include "uint256.h"
#include "util.h"

// Special thanks to jyap808 (NautilusCoin) for solving the CBigNum issue.

unsigned int static GetNextWorkRequired_V1(const CBlockIndex* pindexLast, const CBlockHeader *pblock)
{
    unsigned int nProofOfWorkLimit = cbnProofOfWorkLimit.GetCompact();

    // Genesis block
    if (pindexLast == NULL)
        return nProofOfWorkLimit;
        
    if (pindexLast->nHeight+1 < nAveragingInterval) 
        return nProofOfWorkLimit;

    // Only change once per interval
    if ((pindexLast->nHeight+1) % nInterval != 0)
    {
    	if (Params().AllowMinDifficultyBlocks() && Params().MineBlocksOnDemand()) 
        {
            // Special difficulty rule for testnet:
            // If the new block's timestamp is more than 2* 10 minutes
            // then allow mining of a min-difficulty block.
            if (pblock->nTime > pindexLast->nTime + nTargetSpacing*2)
                return nProofOfWorkLimit;
            else
            {
                // Return the last non-special-min-difficulty-rules-block
                const CBlockIndex* pindex = pindexLast;
                while (pindex->pprev && pindex->nHeight % nInterval != 0 && pindex->nBits == nProofOfWorkLimit)
                    pindex = pindex->pprev;
                return pindex->nBits;
            }
        }
        return pindexLast->nBits;
    }

    // Go back by what we want to be nAveragingInterval blocks
    const CBlockIndex* pindexFirst = pindexLast;
    for (int i = 0; pindexFirst && i < nAveragingInterval-1; i++)
        pindexFirst = pindexFirst->pprev;
    assert(pindexFirst);

    // Limit adjustment step
    int64_t nActualTimespan = pindexLast->GetBlockTime() - pindexFirst->GetBlockTime();
    LogPrintf("  nActualTimespan = %d  before bounds \n", nActualTimespan);
    if (nActualTimespan < nMinActualTimespan)
        nActualTimespan = nMinActualTimespan;
    if (nActualTimespan > nMaxActualTimespan)
        nActualTimespan = nMaxActualTimespan;

    // Retarget
    CBigNum bnNew;
    bnNew.SetCompact(pindexLast->nBits);
    bnNew *= nActualTimespan;
    bnNew /= nAveragingTargetTimespan;

    if (bnNew > cbnProofOfWorkLimit)
        bnNew = cbnProofOfWorkLimit;

    /// debug print
    LogPrintf("GetNextWorkRequired RETARGET, Height: %d \n", pindexLast->nHeight);
    LogPrintf("nTargetTimespan = %d    nActualTimespan = %d \n", nAveragingTargetTimespan, nActualTimespan);
    LogPrintf("Before: %08x  %s\n", pindexLast->nBits, CBigNum().SetCompact(pindexLast->nBits).getuint256().ToString().c_str());
    LogPrintf("After:  %08x  %s\n", bnNew.GetCompact(), bnNew.getuint256().ToString().c_str());

    return bnNew.GetCompact();
}

unsigned int static KimotoGravityWell(const CBlockIndex* pindexLast, const CBlockHeader *pblock, uint64_t TargetBlocksSpacingSeconds, uint64_t PastBlocksMin, uint64_t PastBlocksMax) {
    /* current difficulty formula, megacoin - kimoto gravity well */
    const CBlockIndex *BlockLastSolved = pindexLast;
    const CBlockIndex *BlockReading = pindexLast;
    const CBlockHeader *BlockCreating = pblock;
                                            BlockCreating = BlockCreating;
    uint64_t PastBlocksMass = 0;
    int64_t PastRateActualSeconds = 0;
    int64_t PastRateTargetSeconds = 0;
    double PastRateAdjustmentRatio = double(1);
    CBigNum PastDifficultyAverage;
    CBigNum PastDifficultyAveragePrev;
    double EventHorizonDeviation;
    double EventHorizonDeviationFast;
    double EventHorizonDeviationSlow;

    if (BlockLastSolved == NULL || BlockLastSolved->nHeight == 0 || (uint64_t)BlockLastSolved->nHeight < PastBlocksMin) { return cbnProofOfWorkLimit.GetCompact(); }

        for (unsigned int i = 1; BlockReading && BlockReading->nHeight > 0; i++) {
            if (PastBlocksMax > 0 && i > PastBlocksMax) { break; }
            PastBlocksMass++;

            if (i == 1) { 
                PastDifficultyAverage.SetCompact(BlockReading->nBits);
            } else {
                PastDifficultyAverage = ((CBigNum().SetCompact(BlockReading->nBits) - PastDifficultyAveragePrev) / i) + PastDifficultyAveragePrev;
            }
            PastDifficultyAveragePrev = PastDifficultyAverage;

            PastRateActualSeconds = BlockLastSolved->GetBlockTime() - BlockReading->GetBlockTime();
            PastRateTargetSeconds = TargetBlocksSpacingSeconds * PastBlocksMass;
            PastRateAdjustmentRatio = double(1);
            if (PastRateActualSeconds < 0) { PastRateActualSeconds = 0; }
            if (PastRateActualSeconds != 0 && PastRateTargetSeconds != 0) {
            PastRateAdjustmentRatio = double(PastRateTargetSeconds) / double(PastRateActualSeconds);
            }
            EventHorizonDeviation = 1 + (0.7084 * pow((double(PastBlocksMass)/double(28.2)), -1.228));
            EventHorizonDeviationFast = EventHorizonDeviation;
            EventHorizonDeviationSlow = 1 / EventHorizonDeviation;

            if (PastBlocksMass >= PastBlocksMin) {
                if ((PastRateAdjustmentRatio <= EventHorizonDeviationSlow) || (PastRateAdjustmentRatio >= EventHorizonDeviationFast)) { assert(BlockReading); break; }
            }
            if (BlockReading->pprev == NULL) { assert(BlockReading); break; }
            BlockReading = BlockReading->pprev;
        }

        CBigNum bnNew(PastDifficultyAverage);
        if (PastRateActualSeconds != 0 && PastRateTargetSeconds != 0) {
                bnNew *= PastRateActualSeconds;
                bnNew /= PastRateTargetSeconds;
        }
    if (bnNew > cbnProofOfWorkLimit) { bnNew = cbnProofOfWorkLimit; }

    /// debug print
    LogPrintf("Difficulty Retarget - Kimoto Gravity Well, Height: %d \n", pindexLast->nHeight);
    LogPrintf("PastRateAdjustmentRatio = %g\n", PastRateAdjustmentRatio);
    LogPrintf("Before: %08x %s\n", BlockLastSolved->nBits, CBigNum().SetCompact(BlockLastSolved->nBits).getuint256().ToString().c_str());
    LogPrintf("After: %08x %s\n", bnNew.GetCompact(), bnNew.getuint256().ToString().c_str());

    return bnNew.GetCompact();
}

unsigned int static GetNextWorkRequired_V2(const CBlockIndex* pindexLast, const CBlockHeader *pblock)
{
    static const int64_t BlocksTargetSpacing = 3 * 60; // 60 seconds
    unsigned int TimeDaySeconds = 60 * 60 * 24;
    int64_t PastSecondsMin = TimeDaySeconds * 0.23;
    int64_t PastSecondsMax = TimeDaySeconds * 1;
    uint64_t PastBlocksMin = PastSecondsMin / BlocksTargetSpacing;
    uint64_t PastBlocksMax = PastSecondsMax / BlocksTargetSpacing;
    return KimotoGravityWell(pindexLast, pblock, BlocksTargetSpacing, PastBlocksMin, PastBlocksMax);
}

unsigned int GetNextWorkRequired(const CBlockIndex* pindexLast, const CBlockHeader *pblock)
{
        int DiffMode = 1;
        if (Params().AllowMinDifficultyBlocks() && Params().MineBlocksOnDemand()) {
                if (pindexLast->nHeight+1 >= PROOF_OF_WORK_FORK_BLOCK_TESTNET) { DiffMode = 2; }
        }
        else {
                if (pindexLast->nHeight+1 >= PROOF_OF_WORK_FORK_BLOCK_MAINNET) { DiffMode = 2; } // KGW kicks in at block 450,000
        }
        
        if (DiffMode == 1) { return GetNextWorkRequired_V1(pindexLast, pblock); }
        else if (DiffMode == 2) { return GetNextWorkRequired_V2(pindexLast, pblock); }
        return GetNextWorkRequired_V2(pindexLast, pblock);
}

bool CheckProofOfWork(uint256 hash, unsigned int nBits)
{
    CBigNum bnTarget;

    if (Params().SkipProofOfWorkCheck())
       return true;

    bnTarget.SetCompact(nBits);

    // Check range
    if (bnTarget <= 0 || bnTarget > cbnProofOfWorkLimit)
        return error("CheckProofOfWork() : nBits below minimum work");

    // Check proof of work matches claimed amount
    if (hash > bnTarget.getuint256())
        return error("CheckProofOfWork() : hash doesn't match nBits");

    return true;
}

uint256 GetBlockProof(const CBlockIndex& block)
{
    uint256 bnTarget;
    bool fNegative;
    bool fOverflow;
    bnTarget.SetCompact(block.nBits, &fNegative, &fOverflow);
    if (fNegative || fOverflow || bnTarget == 0)
        return 0;
    // We need to compute 2**256 / (bnTarget+1), but we can't represent 2**256
    // as it's too large for a uint256. However, as 2**256 is at least as large
    // as bnTarget+1, it is equal to ((2**256 - bnTarget - 1) / (bnTarget+1)) + 1,
    // or ~bnTarget / (nTarget+1) + 1.
    return (~bnTarget / (bnTarget + 1)) + 1;
}

bool CheckBlockProofOfWork(const CBlockHeader *pblock)
{
	// There's an issue with blocks prior to the auxpow fork reporting an invalid chain ID.
	// As no version earlier than the 0.10 client a) has version 3 blocks and b) 
	//	has auxpow, anything that isn't a version 3 block can be checked normally.
	//	There's probably a more elegant way to implement this.

	if (pblock->nVersion > 2) {
		LogPrintf("nVersion : %d, ChainID : %d, %d\n",pblock->nVersion,pblock->GetChainID(),AUXPOW_CHAIN_ID);
	    if (!Params().AllowMinDifficultyBlocks() && (pblock->nVersion & BLOCK_VERSION_AUXPOW && pblock->GetChainID() != AUXPOW_CHAIN_ID))
	        return error("CheckBlockProofOfWork() : block does not have our chain ID");	

	    if (pblock->auxpow.get() != NULL)
	    {
	        if (!pblock->auxpow->Check(pblock->GetHash(), pblock->GetChainID()))
	            return error("CheckBlockProofOfWork() : AUX POW is not valid");
	        // Check proof of work matches claimed amount
	        if (!CheckProofOfWork(pblock->auxpow->GetParentBlockHash(), pblock->nBits))
	            return error("CheckBlockProofOfWork() : AUX proof of work failed");
	    } 
	    else
	    {
	        // Check proof of work matches claimed amount
	        if (!CheckProofOfWork(pblock->GetHash(), pblock->nBits))
	            return error("CheckBlockProofOfWork() : proof of work failed");
	    }
	}
    else
    {
        // Check proof of work matches claimed amount
        if (!CheckProofOfWork(pblock->GetHash(), pblock->nBits))
            return error("CheckBlockProofOfWork() : proof of work failed");
    }
    return true;
}
