#pragma once

#include "Common/Challenge.h"

class CChallenge_13 : public CChallenge
{
private:
    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    EErrorCode LoadBusData();
    bool FindConsecutiveBusTimes(unsigned long long const currentTime, size_t const busTimeIdx);

    static std::string const sm_inputFilePath;
    std::vector<unsigned long long> m_busTimes;
    unsigned long long m_minDepartureTime = 0;
};
