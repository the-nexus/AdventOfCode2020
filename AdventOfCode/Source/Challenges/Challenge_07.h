#pragma once

#include "Common/Challenge.h"
#include "../Utilities/NodeGraph.h"

class CChallenge_07 : public CChallenge
{
private:
    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    EErrorCode LoadBagRules();
    static bool HasChildNode(std::string const& childNodeValue, CNodeGraph<std::string>::SNode const* parentNode);
    static unsigned int CountMaxChildren(CNodeGraph<std::string>::SNode const* parentNode);

    static std::string const sm_inputFilePath;
    std::map<std::string, unsigned int> m_colorCountMap;
    CNodeGraph<std::string> m_graph;
};
