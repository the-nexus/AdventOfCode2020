#pragma once

#include "Common/Challenge.h"

class CChallenge_01 : public CChallenge
{
private:
    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    EErrorCode BuildExpenseReport();
    int FindMultipliedExpenses(int const entriesCount, size_t const startingIdx = 0, int const sum = 0, int const mul = 1) const;

    static std::string const sm_inputFilePath;
    size_t m_expenseReportSize = 0;
    int* m_expenseReport = nullptr;
};
