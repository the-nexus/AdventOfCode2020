#pragma once

#include "Common/Challenge.h"

class CChallenge_08 : public CChallenge
{
private:
    struct SInstruction
    {
        std::string m_operation = "";
        int m_parameter = 0;
    };

    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    EErrorCode LoadInstructions();
    bool RunInstructions();

    static std::string const sm_inputFilePath;
    SInstruction* m_instructions = nullptr;
    size_t m_instructionCount = 0;
};
