#include "Challenge_06.h"
#include "../Helpers/FileHelpers.h"



////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_06::sm_inputFilePath = "Inputs/Input_Challenge_06.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_06::SetUp_FirstPart()
{
    return LoadOccurenceGroups();
}

EErrorCode CChallenge_06::Run_FirstPart()
{
    int totalYesCount = 0;
    for (MapType const& occurenceMap : m_occurenceGroups)
    {
        totalYesCount += static_cast<int>(occurenceMap.size()) - 1; // -1 to remove the '#'
    }

    std::cout << "Total questions where anyone answered 'yes' : " << totalYesCount << std::endl;

    return EErrorCode::Success;
}

EErrorCode CChallenge_06::CleanUp_FirstPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_06::SetUp_SecondPart()
{
    return LoadOccurenceGroups();
}

EErrorCode CChallenge_06::Run_SecondPart()
{
    int totalYesCount = 0;
    for (MapType& occurenceMap : m_occurenceGroups)
    {
        int const groupSize = occurenceMap['#'];
        for (MapPairType const& occurencePair : occurenceMap)
        {
            if (occurencePair.first != '#' && occurencePair.second == groupSize)
            {
                ++totalYesCount;
            }
        }
    }

    std::cout << "Total questions where everyone answered 'yes' : " << totalYesCount << std::endl;

    return EErrorCode::Success;
}

EErrorCode CChallenge_06::CleanUp_SecondPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_06::LoadOccurenceGroups()
{
    std::vector<std::string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    m_occurenceGroups.push_back(MapType());
    m_occurenceGroups.back().insert(MapPairType('#', 0)); // use '#' as the number of passenger in the group
    for (std::string const& line : lines)
    {
        if (line.empty())
        {
            m_occurenceGroups.push_back(MapType());
            m_occurenceGroups.back().insert(MapPairType('#', 0)); // use '#' as the number of passenger in the group
        }
        else
        {
            MapType& occurenceMap = m_occurenceGroups.back();
            ++occurenceMap['#']; // increase the passenger count in the group

            for (char const answerChar : line)
            {
                if (occurenceMap.find(answerChar) == occurenceMap.end())
                {
                    occurenceMap.insert(MapPairType(answerChar, 1));
                }
                else
                {
                    ++occurenceMap[answerChar];
                }
            }
        }
    }

    return EErrorCode::Success;
}
