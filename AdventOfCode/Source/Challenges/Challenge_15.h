#pragma once

#include "Common/Challenge.h"

class CChallenge_15 : public CChallenge
{
private:
    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    EErrorCode LoadStartingNumbers();
    int GetSpokenNumber(size_t const turnNumber) const;

    static std::string const sm_inputFilePath;
    std::map<int, std::vector<size_t>> m_spokenNumberMap;
    size_t m_startingNumberCount = 0;
    int m_lastStartingNumber = 0;
};
