#pragma once

#include "Common/Challenge.h"

class CChallenge_09 : public CChallenge
{
private:
    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    EErrorCode LoadPortData();
    bool HasValidNumber(size_t const dataIdx) const;

    static std::string const sm_inputFilePath;
    long long* m_portData = nullptr;
    size_t m_portDataSize = 0;
};
