#include "Challenge_07.h"
#include "../Helpers/FileHelpers.h"



////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_07::sm_inputFilePath = "Inputs/Input_Challenge_07.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_07::SetUp_FirstPart()
{
    return LoadBagRules();
}

EErrorCode CChallenge_07::Run_FirstPart()
{
    int bagCount = 0;
    for (auto nodeIt = m_graph.GetBeginIt(); nodeIt != m_graph.GetEndIt(); ++nodeIt)
    {
        CNodeGraph<std::string>::SNode const* node = nodeIt->second;
        if (HasChildNode("shiny gold", node))
        {
            ++bagCount;
        }
    }

    std::cout << "Bag count = " << bagCount << std::endl;
    return EErrorCode::Success;
}

EErrorCode CChallenge_07::CleanUp_FirstPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_07::SetUp_SecondPart()
{
    return LoadBagRules();
}

EErrorCode CChallenge_07::Run_SecondPart()
{
    CNodeGraph<std::string>::SNode const* node = m_graph.GetNodeFromValue("shiny gold");
    unsigned int const bagCount = CountMaxChildren(node);

    std::cout << "Bag count = " << bagCount << std::endl;
    return EErrorCode::Success;
}

EErrorCode CChallenge_07::CleanUp_SecondPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_07::LoadBagRules()
{
    std::vector<std::string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    for (std::string const& line : lines)
    {
        std::vector<std::string> ruleArgs;
        FileHelper::SplitLine(line, " bags contain ", ruleArgs);
        m_graph.Insert(ruleArgs[0]);

        CNodeGraph<std::string>::SNode* srcNode = m_graph.GetNodeFromValue(ruleArgs[0]);

        std::vector<std::string> containedBags;
        FileHelper::SplitLine(ruleArgs[1], ", ", containedBags);
        for (std::string const& bagStr : containedBags)
        {
            size_t const firstSpaceIdx = bagStr.find(' ');
            std::string const countStr = bagStr.substr(0, firstSpaceIdx);
            if (countStr.compare("no") == 0)
            {
                break;
            }

            size_t const lastSpaceIdx = bagStr.find(" bag", firstSpaceIdx);
            size_t const bagColorStrSize = lastSpaceIdx - (firstSpaceIdx + 1);
            std::string const bagColorStr = bagStr.substr(firstSpaceIdx + 1, bagColorStrSize);
            m_graph.Insert(bagColorStr);

            CNodeGraph<std::string>::SNode* dstNode = m_graph.GetNodeFromValue(bagColorStr);
            srcNode->AddLink(dstNode, atoi(countStr.c_str()));
        }
    }

    return EErrorCode::Success;
}

bool CChallenge_07::HasChildNode(std::string const& childNodeValue, CNodeGraph<std::string>::SNode const* parentNode)
{
    for (std::pair<CNodeGraph<std::string>::SNode*, unsigned int> const& childNodePair : parentNode->m_linkedNodes)
    {
        if (childNodePair.first->m_value.compare(childNodeValue) == 0 || HasChildNode(childNodeValue, childNodePair.first))
        {
            return true;
        }
    }
    return false;
}

unsigned int CChallenge_07::CountMaxChildren(CNodeGraph<std::string>::SNode const* parentNode)
{
    unsigned int totalChildren = 0;
    for (std::pair<CNodeGraph<std::string>::SNode*, unsigned int> const& childNodePair : parentNode->m_linkedNodes)
    {
        totalChildren += childNodePair.second * (CountMaxChildren(childNodePair.first) + 1);
    }
    return totalChildren;
}
