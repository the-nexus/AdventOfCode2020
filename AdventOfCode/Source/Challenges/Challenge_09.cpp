#include "Challenge_09.h"
#include "../Helpers/FileHelpers.h"



////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_09::sm_inputFilePath = "Inputs/Input_Challenge_09.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_09::SetUp_FirstPart()
{
    return LoadPortData();
}

EErrorCode CChallenge_09::Run_FirstPart()
{
    for (size_t dataIdx = 25; dataIdx < m_portDataSize; ++dataIdx)
    {
        if (!HasValidNumber(dataIdx))
        {
            std::cout << "Invalid number = " << m_portData[dataIdx] << std::endl;
            break;
        }
    }

    return EErrorCode::Success;
}

EErrorCode CChallenge_09::CleanUp_FirstPart()
{
    delete[] m_portData;
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_09::SetUp_SecondPart()
{
    return LoadPortData();
}

EErrorCode CChallenge_09::Run_SecondPart()
{
    long long invalidNumber = -1;
    for (size_t dataIdx = 25; dataIdx < m_portDataSize; ++dataIdx)
    {
        if (!HasValidNumber(dataIdx))
        {
            invalidNumber = m_portData[dataIdx];
            std::cout << "Invalid number = " << m_portData[dataIdx] << std::endl;
            break;
        }
    }

    size_t rangeStartIdx = 0;
    size_t rangeEndIdx = 1;
    long long rangeSum = m_portData[0] + m_portData[1];
    while (rangeEndIdx < m_portDataSize && rangeStartIdx < rangeEndIdx)
    {
        if (rangeSum == invalidNumber)
        {
            std::cout << "Invalid number sum range = (" << rangeStartIdx << ", " << rangeEndIdx << ")" <<std::endl;
            break;
        }
        else if (rangeSum > invalidNumber)
        {
            rangeSum -= m_portData[rangeStartIdx];
            ++rangeStartIdx;
        }
        else if (rangeSum < invalidNumber)
        {
            ++rangeEndIdx;
            rangeSum += m_portData[rangeEndIdx];
        }
    }

    long long minNumber = invalidNumber;
    long long maxNumber = -1;
    for (size_t dataIdx = rangeStartIdx; dataIdx <= rangeEndIdx; ++dataIdx)
    {
        long long const dataNumber = m_portData[dataIdx];

        if (dataNumber < minNumber)
        {
            minNumber = dataNumber;
        }

        if (dataNumber > maxNumber)
        {
            maxNumber = dataNumber;
        }
    }

    long long const minMaxSum = minNumber + maxNumber;
    std::cout << "Sum of min and max number in range = " << minMaxSum << std::endl;

    return EErrorCode::Success;
}

EErrorCode CChallenge_09::CleanUp_SecondPart()
{
    delete[] m_portData;
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_09::LoadPortData()
{
    std::vector<std::string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    size_t const lineSize = lines.size();
    m_portDataSize = lineSize;
    m_portData = new long long[lineSize];

    for (size_t lineIdx = 0; lineIdx < lineSize; ++lineIdx)
    {
        m_portData[lineIdx] = atoll(lines[lineIdx].c_str());
    }

    return EErrorCode::Success;
}

bool CChallenge_09::HasValidNumber(size_t const dataIdx) const
{
    long long const dataNumber = m_portData[dataIdx];
    for (size_t firstIdx = dataIdx - 25; firstIdx < dataIdx; ++firstIdx)
    {
        long long const firstNumber = m_portData[firstIdx];
        for (size_t secondIdx = dataIdx - 25; secondIdx < dataIdx; ++secondIdx)
        {
            long long const secondNumber = m_portData[secondIdx];
            if (firstNumber != secondNumber && (firstNumber + secondNumber) == dataNumber)
            {
                return true;
            }
        }
    }
    return false;
}
