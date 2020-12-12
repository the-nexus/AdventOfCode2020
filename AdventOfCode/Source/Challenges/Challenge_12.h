#pragma once

#include "Common/Challenge.h"

class CChallenge_12 : public CChallenge
{
private:

    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    static void RotatePosAroundOrigin(int const stepCount, int& waypointX, int& waypointY);

    static std::string const sm_inputFilePath;
    std::vector<std::string> m_instructions;
};
