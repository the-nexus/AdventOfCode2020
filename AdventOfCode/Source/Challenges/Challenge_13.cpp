#include "Challenge_13.h"
#include "../Helpers/FileHelpers.h"



////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_13::sm_inputFilePath = "Inputs/Input_Challenge_13.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_13::SetUp_FirstPart()
{
    return LoadBusData();
}

EErrorCode CChallenge_13::Run_FirstPart()
{
    unsigned long long shortestWaitTime = -1;
    unsigned long long shortestWaitTimeId = 0;

    for (unsigned long long const busTime : m_busTimes)
    {
        unsigned long long nextDepartureTime = m_minDepartureTime - (m_minDepartureTime % busTime) + busTime;
        unsigned long long waitTime = nextDepartureTime - m_minDepartureTime;

        if (waitTime < shortestWaitTime)
        {
            shortestWaitTime = waitTime;
            shortestWaitTimeId = busTime;
        }
    }

    unsigned long long earliestBusProduct = shortestWaitTime * shortestWaitTimeId;
    std::cout << "Earliest bus product = " << earliestBusProduct << std::endl;

    return EErrorCode::Success;
}

EErrorCode CChallenge_13::CleanUp_FirstPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_13::SetUp_SecondPart()
{
    return LoadBusData();
}

EErrorCode CChallenge_13::Run_SecondPart()
{
    std::vector<unsigned long long> smallModulos;
    std::vector<unsigned long long> leftovers;
    unsigned long long biggestModulo = 1;

    for (size_t busTimeIdx = 0; busTimeIdx < m_busTimes.size(); ++busTimeIdx)
    {
        unsigned long long const busTime = m_busTimes[busTimeIdx];
        if (busTime > 0)
        {
            unsigned long long adjustedBusTime = busTime;
            while (adjustedBusTime < busTimeIdx)
            {
                adjustedBusTime += busTime;
            }

            smallModulos.push_back(busTime);
            leftovers.push_back(adjustedBusTime - busTimeIdx);
            biggestModulo *= busTime;
        }
    }

    std::vector<unsigned long long> bigModulos;
    std::vector<unsigned long long> multipliers;
    bigModulos.resize(smallModulos.size());
    multipliers.resize(smallModulos.size());

    for (size_t moduloIdx = 0; moduloIdx < smallModulos.size(); ++moduloIdx)
    {
        bigModulos[moduloIdx] = biggestModulo / smallModulos[moduloIdx];

        multipliers[moduloIdx] = 1;
        while ((multipliers[moduloIdx] * bigModulos[moduloIdx]) % smallModulos[moduloIdx] != 1)
        {
            ++multipliers[moduloIdx];
        }
    }

    unsigned long long targetSum = 0;
    for (size_t moduloIdx = 0; moduloIdx < smallModulos.size(); ++moduloIdx)
    {
        targetSum += leftovers[moduloIdx] * bigModulos[moduloIdx] * multipliers[moduloIdx];
    }

    unsigned long long const targetTime = targetSum % biggestModulo;
    std::cout << "Consecutive bus time = " << targetTime << std::endl;
    return EErrorCode::Success;
}

EErrorCode CChallenge_13::CleanUp_SecondPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_13::LoadBusData()
{
    std::vector<std::string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    m_minDepartureTime = atoi(lines[0].c_str());
    std::vector<std::string> items;
    FileHelper::SplitLine(lines[1], ",", items);

    for (std::string const& item : items)
    {
        if (item[0] == 'x')
        {
            m_busTimes.push_back(0);
        }
        else
        {
            m_busTimes.push_back(atoi(item.c_str()));
        }
    }

    return EErrorCode::Success;
}

bool CChallenge_13::FindConsecutiveBusTimes(unsigned long long const currentTime, size_t const busTimeIdx)
{
    if (busTimeIdx == m_busTimes.size())
    {
        return true;
    }
    else
    {
        unsigned long long const busTime = m_busTimes[busTimeIdx];
        if (busTime == 0 || currentTime % busTime == 0)
        {
            return FindConsecutiveBusTimes(currentTime + 1, busTimeIdx + 1);
        }
    }

    return false;
}
