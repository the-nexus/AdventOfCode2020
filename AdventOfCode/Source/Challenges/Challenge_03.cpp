#include "Challenge_03.h"
#include "../Helpers/FileHelpers.h"



////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_03::sm_inputFilePath = "Inputs/Input_Challenge_03.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_03::SetUp_FirstPart()
{
    return FileHelper::ReadLines(sm_inputFilePath, m_treeLines);
}

EErrorCode CChallenge_03::Run_FirstPart()
{
    std::cout << "Encountered trees (3, 1) = " << CountTreesOnSlope(3, 1) << std::endl;
    return EErrorCode::Success;
}

EErrorCode CChallenge_03::CleanUp_FirstPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_03::SetUp_SecondPart()
{
    return FileHelper::ReadLines(sm_inputFilePath, m_treeLines);
}

EErrorCode CChallenge_03::Run_SecondPart()
{
    unsigned int encounteredTreeProduct = 1;

    encounteredTreeProduct *= CountTreesOnSlope(1, 1);
    encounteredTreeProduct *= CountTreesOnSlope(3, 1);
    encounteredTreeProduct *= CountTreesOnSlope(5, 1);
    encounteredTreeProduct *= CountTreesOnSlope(7, 1);
    encounteredTreeProduct *= CountTreesOnSlope(1, 2);

    std::cout << "Encountered trees product = " << encounteredTreeProduct << std::endl;
    return EErrorCode::Success;
}

EErrorCode CChallenge_03::CleanUp_SecondPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned int CChallenge_03::CountTreesOnSlope(size_t const stepX, size_t const stepY) const
{
    int encounteredTreeCount = 0;
    size_t x = 0;
    size_t y = 0;

    while (y < m_treeLines.size())
    {
        size_t const lineSize = m_treeLines[y].size();
        bool const hasTree = m_treeLines[y][x] == '#';

        if (hasTree)
        {
            ++encounteredTreeCount;
        }

        x = (x + stepX) % lineSize;
        y += stepY;
    }

    std::cout << "Encountered trees (" << stepX << ", " << stepY << ") = " << encounteredTreeCount << std::endl;

    return encounteredTreeCount;
}
