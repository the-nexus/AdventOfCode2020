#include "Challenge_01.h"
#include "../Helpers/FileHelpers.h"



////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_01::sm_inputFilePath = "Inputs/Input_Challenge_01.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_01::SetUp_FirstPart()
{
    return BuildExpenseReport();
}

EErrorCode CChallenge_01::Run_FirstPart()
{
    int const multipliedExpenses = FindMultipliedExpenses(2);
    if (multipliedExpenses > 0)
    {
        std::cout << "Multiplied expenses = " << multipliedExpenses << std::endl;
    }

    return EErrorCode::Success;
}

EErrorCode CChallenge_01::CleanUp_FirstPart()
{
    delete[] m_expenseReport;
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_01::SetUp_SecondPart()
{
    return BuildExpenseReport();
}

EErrorCode CChallenge_01::Run_SecondPart()
{
    int const multipliedExpenses = FindMultipliedExpenses(3);
    if (multipliedExpenses > 0)
    {
        std::cout << "Multiplied expenses = " << multipliedExpenses << std::endl;
    }

    return EErrorCode::Success;
}

EErrorCode CChallenge_01::CleanUp_SecondPart()
{
    delete[] m_expenseReport;
    return EErrorCode::NotImplemented;
}

EErrorCode CChallenge_01::BuildExpenseReport()
{
    std::vector<std::string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    size_t const expenseReportSize = lines.size();
    m_expenseReportSize = expenseReportSize;
    m_expenseReport = new int[expenseReportSize];

    for (size_t entryIdx = 0; entryIdx < expenseReportSize; ++entryIdx)
    {
        m_expenseReport[entryIdx] = atoi(lines[entryIdx].c_str());
    }

    std::sort(m_expenseReport, m_expenseReport + m_expenseReportSize);

    return EErrorCode::Success;
}

int CChallenge_01::FindMultipliedExpenses(int const entriesCount, size_t const startingIdx, int const sum, int const mul) const
{
    if (entriesCount == 0)
    {
        if (sum == 2020)
        {
            return mul;
        }
    }
    else
    {
        for (size_t entryIdx = startingIdx; entryIdx < m_expenseReportSize; ++entryIdx)
        {
            int const multipliedExpenses = FindMultipliedExpenses(
                entriesCount - 1,
                entryIdx + 1,
                sum + m_expenseReport[entryIdx],
                mul * m_expenseReport[entryIdx]
            );

            if (multipliedExpenses > 0)
            {
                return multipliedExpenses;
            }
        }
    }

    return 0;
}
