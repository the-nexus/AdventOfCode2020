#pragma once

#include "Common/Challenge.h"

class CChallenge_16 : public CChallenge
{
private:
    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    EErrorCode LoadTickets();
    bool IsValidTicket(std::vector<int> const& ticketItems) const;

    static std::string const sm_inputFilePath;
    std::vector<int> m_myTicket;
    std::vector<std::vector<int>> m_nearbyTickets;
    std::vector<std::string> m_ruleNames;
    std::map<int, std::vector<size_t>> m_ruleMap;
};
