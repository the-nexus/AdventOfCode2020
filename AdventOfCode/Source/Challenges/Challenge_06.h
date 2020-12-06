#pragma once

#include "Common/Challenge.h"

class CChallenge_06 : public CChallenge
{
private:
    typedef std::pair<char, int> MapPairType;
    typedef std::map<char, int> MapType;

    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    EErrorCode LoadOccurenceGroups();

    static std::string const sm_inputFilePath;
    std::vector<MapType> m_occurenceGroups;
};
