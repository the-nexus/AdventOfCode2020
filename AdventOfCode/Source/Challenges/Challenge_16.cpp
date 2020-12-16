#include "Challenge_16.h"
#include "../Helpers/FileHelpers.h"



////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_16::sm_inputFilePath = "Inputs/Input_Challenge_16.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_16::SetUp_FirstPart()
{
    return LoadTickets();
}

EErrorCode CChallenge_16::Run_FirstPart()
{
    int errorRate = 0;
    for (std::vector<int> const& nearbyTicketItems : m_nearbyTickets)
    {
        for (int const ticketItem : nearbyTicketItems)
        {
            if (m_ruleMap.find(ticketItem) == m_ruleMap.end())
            {
                errorRate += ticketItem;
            }
        }
    }

    std::cout << "Ticket scanning error rate = " << errorRate << std::endl;
    return EErrorCode::Success;
}

EErrorCode CChallenge_16::CleanUp_FirstPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_16::SetUp_SecondPart()
{
    return LoadTickets();
}

EErrorCode CChallenge_16::Run_SecondPart()
{
    std::vector<std::vector<size_t>> validRulesForMyTicket;
    validRulesForMyTicket.resize(m_myTicket.size());
    for (size_t ticketItemIdx = 0; ticketItemIdx < validRulesForMyTicket.size(); ++ticketItemIdx)
    {
        int const ticketItem = m_myTicket[ticketItemIdx];
        auto rulesIt = m_ruleMap.find(ticketItem);
        validRulesForMyTicket[ticketItemIdx] = rulesIt->second;
    }

    for (std::vector<int> const& nearbyTicketItems : m_nearbyTickets)
    {
        if (!IsValidTicket(nearbyTicketItems))
        {
            continue;
        }

        bool hasRemainingRulesToRemove = false;
        for (size_t ticketItemIdx = 0; ticketItemIdx < nearbyTicketItems.size(); ++ticketItemIdx)
        {
            std::vector<size_t>& remainingRules = validRulesForMyTicket[ticketItemIdx];
            if (remainingRules.size() == 1)
            {
                continue;
            }

            hasRemainingRulesToRemove = true;

            auto rulesIt = m_ruleMap.find(nearbyTicketItems[ticketItemIdx]);
            for (size_t ruleIdx = 0; ruleIdx < remainingRules.size(); ++ruleIdx)
            {
                if (std::find(rulesIt->second.begin(), rulesIt->second.end(), remainingRules[ruleIdx]) == rulesIt->second.end())
                {
                    std::swap(remainingRules[ruleIdx], remainingRules[remainingRules.size() - 1]);
                    remainingRules.pop_back();
                    --ruleIdx;
                }
            }
        }

        if (!hasRemainingRulesToRemove)
        {
            break;
        }
    }

    std::vector<bool> ticketItemIdentified;
    ticketItemIdentified.resize(m_myTicket.size());
    for (size_t ticketItemIdx = 0; ticketItemIdx < ticketItemIdentified.size(); ++ticketItemIdx)
    {
        ticketItemIdentified[ticketItemIdx] = false;
    }

    size_t ticketItemIdx = 0;
    size_t identifiedTicketItemCount = 0;
    while (identifiedTicketItemCount < m_myTicket.size())
    {
        if (ticketItemIdentified[ticketItemIdx])
        {
            ++identifiedTicketItemCount;
        }
        else
        {
            if (validRulesForMyTicket[ticketItemIdx].size() == 1)
            {
                identifiedTicketItemCount = 1;
                ticketItemIdentified[ticketItemIdx] = true;

                size_t const ruleIdx = validRulesForMyTicket[ticketItemIdx][0];
                for (size_t validRulesIdx = 0; validRulesIdx < validRulesForMyTicket.size(); ++validRulesIdx)
                {
                    if (!ticketItemIdentified[validRulesIdx])
                    {
                        auto firstRuleIt = validRulesForMyTicket[validRulesIdx].begin();
                        auto lastRuleIt = validRulesForMyTicket[validRulesIdx].end();
                        auto ruleIt = std::find(firstRuleIt, lastRuleIt, ruleIdx);

                        if (ruleIt != lastRuleIt)
                        {
                            std::swap(*ruleIt, *(lastRuleIt - 1));
                            validRulesForMyTicket[validRulesIdx].pop_back();
                        }
                    }
                }

            }
        }

        ticketItemIdx = (ticketItemIdx + 1) % m_myTicket.size();
    }

    size_t departureProduct = 1;
    for (size_t ticketItemIdx = 0; ticketItemIdx < m_myTicket.size(); ++ticketItemIdx)
    {
        std::vector<size_t> const& ticketItemRules = validRulesForMyTicket[ticketItemIdx];
        std::cout << std::setw(5) << m_myTicket[ticketItemIdx] << "  :  ";

        if (ticketItemRules.size() > 0)
        {
            for (size_t const ticketItemRule : ticketItemRules)
            {
                std::cout << "[" << m_ruleNames[ticketItemRule] << "]  ";
            }

            std::string const& itemRuleName = m_ruleNames[ticketItemRules[0]];
            if (itemRuleName.find("departure") < itemRuleName.size())
            {
                departureProduct *= m_myTicket[ticketItemIdx];
            }
        }
        std::cout << std::endl;
    }

    std::cout << std::endl << "Product of 'departure' items = " << departureProduct;
    return EErrorCode::Success;
}

EErrorCode CChallenge_16::CleanUp_SecondPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_16::LoadTickets()
{
    std::vector<std::string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    size_t const lineCount = lines.size();
    size_t lineIdx = 0;

    // Rules
    while (lineIdx < lineCount)
    {
        std::string const& ruleStr = lines[lineIdx];
        if (ruleStr.empty())
        {
            break;
        }

        size_t const colonIdx = ruleStr.find(':');
        size_t const firstRangeStartIdx = colonIdx + 2;
        size_t const firstRangeSeparatorIdx = ruleStr.find('-', firstRangeStartIdx);
        size_t const firstRangeEndIdx = ruleStr.find(' ', firstRangeSeparatorIdx);
        size_t const secondRangeStartIdx = firstRangeEndIdx + 4;
        size_t const secondRangeSeparatorIdx = ruleStr.find('-', secondRangeStartIdx);
        size_t const secondRangeEndIdx = ruleStr.size();

        m_ruleNames.push_back(ruleStr.substr(0, colonIdx));
        size_t const ruleNameIdx = m_ruleNames.size() - 1;

        int const firstRangeStartNumber = atoi(ruleStr.substr(firstRangeStartIdx, firstRangeSeparatorIdx - firstRangeStartIdx).c_str());
        int const firstRangeEndNumber = atoi(ruleStr.substr(firstRangeSeparatorIdx + 1, firstRangeEndIdx - (firstRangeSeparatorIdx + 1)).c_str());
        for (int number = firstRangeStartNumber; number <= firstRangeEndNumber; ++number)
        {
            m_ruleMap[number].push_back(ruleNameIdx);
        }

        int const secondRangeStartNumber = atoi(ruleStr.substr(secondRangeStartIdx, secondRangeSeparatorIdx - secondRangeStartIdx).c_str());
        int const secondRangeEndNumber = atoi(ruleStr.substr(secondRangeSeparatorIdx + 1, secondRangeEndIdx - (secondRangeSeparatorIdx + 1)).c_str());
        for (int number = secondRangeStartNumber; number <= secondRangeEndNumber; ++number)
        {
            m_ruleMap[number].push_back(ruleNameIdx);
        }

        ++lineIdx;
    }

    lineIdx += 2;

    // My ticket
    std::vector<std::string> myTicketItems;
    FileHelper::SplitLine(lines[lineIdx], ",", myTicketItems);
    m_myTicket.reserve(myTicketItems.size());
    for (std::string const& ticketItem : myTicketItems)
    {
        m_myTicket.push_back(atoi(ticketItem.c_str()));
    }

    lineIdx += 3;

    // Nearby tickets
    while (lineIdx < lineCount)
    {
        m_nearbyTickets.push_back(std::vector<int>());
        std::vector<int>& nearbyTicket = m_nearbyTickets.back();

        std::vector<std::string> nearbyTicketItems;
        FileHelper::SplitLine(lines[lineIdx], ",", nearbyTicketItems);
        nearbyTicket.reserve(nearbyTicketItems.size());
        for (std::string const& ticketItem : nearbyTicketItems)
        {
            nearbyTicket.push_back(atoi(ticketItem.c_str()));
        }

        ++lineIdx;
    }

    return EErrorCode::Success;
}

bool CChallenge_16::IsValidTicket(std::vector<int> const& ticketItems) const
{
    for (int const ticketItem : ticketItems)
    {
        if (m_ruleMap.find(ticketItem) == m_ruleMap.end())
        {
            return false;
        }
    }
    return true;
}
