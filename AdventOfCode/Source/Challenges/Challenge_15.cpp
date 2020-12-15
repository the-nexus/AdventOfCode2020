#include "Challenge_15.h"
#include "../Helpers/FileHelpers.h"



////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_15::sm_inputFilePath = "Inputs/Input_Challenge_15.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_15::SetUp_FirstPart()
{
    return LoadStartingNumbers();
}

EErrorCode CChallenge_15::Run_FirstPart()
{
    size_t const turnNumber = 2020;
    std::cout << turnNumber << "th spoken number = " << GetSpokenNumber(turnNumber) << std::endl;
    return EErrorCode::Success;
}

EErrorCode CChallenge_15::CleanUp_FirstPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_15::SetUp_SecondPart()
{
    return LoadStartingNumbers();
}

EErrorCode CChallenge_15::Run_SecondPart()
{
    size_t const turnNumber = 30000000;
    std::cout << turnNumber << "th spoken number = " << GetSpokenNumber(turnNumber) << std::endl;
    return EErrorCode::Success;
}

EErrorCode CChallenge_15::CleanUp_SecondPart()
{
    return EErrorCode::NotImplemented;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_15::LoadStartingNumbers()
{
    std::string line;
    EErrorCode const readErrorCode = FileHelper::ReadFirstLine(sm_inputFilePath, line);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    std::vector<std::string> items;
    FileHelper::SplitLine(line, ",", items);

    for (size_t spokenNumberIdx = 0; spokenNumberIdx < items.size(); ++spokenNumberIdx)
    {
        int const spokenNumber = atoi(items[spokenNumberIdx].c_str());
        m_spokenNumberMap[spokenNumber].push_back(spokenNumberIdx);
        m_lastStartingNumber = spokenNumber;
        ++m_startingNumberCount;
    }

    return EErrorCode::Success;
}

int CChallenge_15::GetSpokenNumber(size_t const turnNumber) const
{
    std::map<int, std::vector<size_t>> spokenNumberMap = m_spokenNumberMap;
    int lastSpokenNumber = m_lastStartingNumber;
    for (size_t currentTurnNumber = m_startingNumberCount; currentTurnNumber < turnNumber; ++currentTurnNumber)
    {
        int spokenNumber = 0;

        auto const it = spokenNumberMap.find(lastSpokenNumber);
        if (it != spokenNumberMap.cend())
        {
            size_t const lastSpokenNumberCount = it->second.size();
            if (lastSpokenNumberCount > 1)
            {
                spokenNumber = static_cast<int>(it->second[lastSpokenNumberCount - 1] - it->second[lastSpokenNumberCount - 2]);
            }
        }

        spokenNumberMap[spokenNumber].push_back(currentTurnNumber);
        lastSpokenNumber = spokenNumber;
    }
    return lastSpokenNumber;
}
