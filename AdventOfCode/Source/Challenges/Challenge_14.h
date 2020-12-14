#pragma once

#include "Common/Challenge.h"

#define BIT_MASK_36 36

class CChallenge_14 : public CChallenge
{
private:
    typedef unsigned long long IntType;

    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    static void CreateBitMasks(IntType (&outBitMasks)[BIT_MASK_36]);
    static void GetMaskedMemoryValue(IntType const memoryValue, std::string const& maskStr, IntType const (&bitMasks)[BIT_MASK_36], IntType& outMaskedMemoryValue);
    static void GetMaskedMemoryAddresses(IntType const memoryAddress, std::string const& maskStr, IntType const (&bitMasks)[BIT_MASK_36], std::vector<size_t>& outMaskedMemoryAddresses);

    static std::string const sm_inputFilePath;
    std::vector<std::string> m_lines;
};
