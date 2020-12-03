#pragma once

#include "Common/Challenge.h"

class CChallenge_03 : public CChallenge
{
private:
    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    unsigned int CountTreesOnSlope(size_t const stepX, size_t const stepY) const;

    static std::string const sm_inputFilePath;
    std::vector<std::string> m_treeLines;
};
