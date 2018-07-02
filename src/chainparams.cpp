// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds array into usable address objects.
static void convertSeeds(std::vector<CAddress> &vSeedsOut, const unsigned int *data, unsigned int count, int port)
{
     // It'll only connect to one or two seed nodes because once it connects,
     // it'll get a pile of addresses with newer timestamps.
     // Seed nodes are given a random 'last seen time' of between one and two
     // weeks ago.
     const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int k = 0; k < count; ++k)
    {
        struct in_addr ip;
        unsigned int i = data[k], t;
        
        // -- convert to big endian
        t =   (i & 0x000000ff) << 24u
            | (i & 0x0000ff00) << 8u
            | (i & 0x00ff0000) >> 8u
            | (i & 0xff000000) >> 24u;
        
        memcpy(&ip, &t, sizeof(ip));
        
        CAddress addr(CService(ip, port));
        addr.nTime = GetTime()-GetRand(nOneWeek)-nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xe8;
        pchMessageStart[1] = 0xd4;
        pchMessageStart[2] = 0x91;
        pchMessageStart[3] = 0xc7;
        vAlertPubKey = ParseHex("04eb12b902dbdbb7b64167cd9cabc2e77974a65936a8e3bb08dde1da3c5a920968d56c1e4e54ebbbf00569ca57af1e4860eef0b85944878ef821b77fdf6340991f");
        nDefaultPort = 16000;
        nRPCPort = 15000;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);

        const char* pszTimestamp = "FIFA World cup 2018 started Jun 14, 2018";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1530125490, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1530125490;
        genesis.nBits    = 520159231; 
        genesis.nNonce   = 101282;


        hashGenesisBlock = genesis.GetHash();
/*
        if (genesis.GetHash() != uint256("0x0000097549d8efc4630e67e175d648cb7ec1cea81cf7c859dd4aab5a4aaf6ddb")) {
			//CBigNum bnTarget;
		    //bnTarget.SetCompact(block.nBits);
//            uint256 hashTarget = genesis.nBits; // CBigNum().SetCompact(block.nBits).getuint256();
            uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
            while (genesis.GetHash() > hashTarget)
            {
                ++genesis.nNonce;
                if (genesis.nNonce == 0)
                {
                    printf("NONCE WRAPPED, incrementing time");
                	++genesis.nTime;
            	}
				else 
				printf("Nnonce: %u \n", genesis.nNonce);
        	}
		}

		printf("Voila! Block Generated\n");
        printf("block.GetHash() == %s\n", genesis.GetHash().ToString().c_str());
        printf("block.hashMerkleRoot == %s\n", genesis.hashMerkleRoot.ToString().c_str());
        printf("block.nTime = %u \n", genesis.nTime);
        printf("block.nNonce = %u \n", genesis.nNonce);
*/

        assert(hashGenesisBlock == uint256("0x000090b286ea9c1f0084f31097f31a2f7233f9b7668199b561af87dc40bf7c2a"));
        assert(genesis.hashMerkleRoot == uint256("0xf99b63e014c3ab8cde4422622aa9206d3e1d0be1c4ae9e8372c8a8b9d135a7dc"));
        

        
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,50);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,85);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,153);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,40);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        vSeeds.push_back(CDNSSeedData("0","seed.mastercoin.one"));
        vSeeds.push_back(CDNSSeedData("1","seed1.mastercoin.one"));
        vSeeds.push_back(CDNSSeedData("2","seed2.mastercoin.one"));
        vSeeds.push_back(CDNSSeedData("3","seed3.mastercoin.one"));

        convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);

        nPoolMaxTransactions = 3;
        strDarksendPoolDummyAddress = "MEGD9bnp76AJLNQ3oF24ggHJBPDEMEezoX";
        nLastPOWBlock = 20001;
        nPOSStartBlock = 20001;
        nMasternodePaymentStartBlock = 65;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x62;
        pchMessageStart[1] = 0x84;
        pchMessageStart[2] = 0xbd;
        pchMessageStart[3] = 0xd5;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("04913b5b6119ade87b6c0d870793fa02ab4ae11db2986b3177b31beb4af04325b077f47b549913ceac78a936f2a09d5af1ae54d1093aef96730ffadc72a471db52");
        nDefaultPort = 14000;
        nRPCPort = 13000;
        strDataDir = "testnet";

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,110);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,239);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,40);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        convertSeeds(vFixedSeeds, pnTestnetSeed, ARRAYLEN(pnTestnetSeed), nDefaultPort);

        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    
    bool fTestNet = GetBoolArg("-testnet", false);
    
    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
