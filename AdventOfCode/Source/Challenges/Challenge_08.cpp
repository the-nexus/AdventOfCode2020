#include "Challenge_08.h"
#include "../Helpers/FileHelpers.h"



////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_08::sm_inputFilePath = "Inputs/Input_Challenge_08.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_08::SetUp_FirstPart()
{
    return LoadInstructions();
}

EErrorCode CChallenge_08::Run_FirstPart()
{
    RunInstructions();
    return EErrorCode::Success;
}

EErrorCode CChallenge_08::CleanUp_FirstPart()
{
    delete[] m_instructions;
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_08::SetUp_SecondPart()
{
    return LoadInstructions();
}

EErrorCode CChallenge_08::Run_SecondPart()
{
    for (size_t instructionIdx = 0; instructionIdx < m_instructionCount; ++instructionIdx)
    {
        SInstruction& instruction = m_instructions[instructionIdx];

        bool wasSuccessful = false;
        if (instruction.m_operation.compare("jmp") == 0)
        {
            instruction.m_operation = "nop";
            wasSuccessful = RunInstructions();
            instruction.m_operation = "jmp";
        }
        else if (instruction.m_operation.compare("nop") == 0)
        {
            instruction.m_operation = "jmp";
            wasSuccessful = RunInstructions();
            instruction.m_operation = "nop";
        }

        if (wasSuccessful)
        {
            break;
        }
    }

    return EErrorCode::Success;
}

EErrorCode CChallenge_08::CleanUp_SecondPart()
{
    delete[] m_instructions;
    return EErrorCode::Success;
}


EErrorCode CChallenge_08::LoadInstructions()
{
    std::vector<std::string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    size_t const lineCount = lines.size();
    m_instructionCount = lineCount;
    m_instructions = new SInstruction[lineCount];

    for (size_t lineIdx = 0; lineIdx < lineCount; ++lineIdx)
    {
        SInstruction& instruction = m_instructions[lineIdx];
        std::string const& line = lines[lineIdx];

        instruction.m_operation = line.substr(0, 3);
        instruction.m_parameter = atoi(line.substr(5).c_str());

        if (line[4] == '-')
        {
            instruction.m_parameter *= -1;
        }
    }

    return EErrorCode::Success;
}

bool CChallenge_08::RunInstructions()
{
    bool* executedInstructions = new bool[m_instructionCount];
    for (size_t instructionIdx = 0; instructionIdx < m_instructionCount; ++instructionIdx)
    {
        executedInstructions[instructionIdx] = false;
    }

    int accumulatorValue = 0;
    size_t instructionIdx = 0;

    while (instructionIdx < m_instructionCount)
    {
        SInstruction& instruction = m_instructions[instructionIdx];

        if (executedInstructions[instructionIdx])
        {
            break;
        }
        executedInstructions[instructionIdx] = true;

        if (instruction.m_operation.compare("acc") == 0)
        {
            accumulatorValue += instruction.m_parameter;
            ++instructionIdx;
        }
        else if (instruction.m_operation.compare("jmp") == 0)
        {
            instructionIdx += instruction.m_parameter;
        }
        else if (instruction.m_operation.compare("nop") == 0)
        {
            ++instructionIdx;
        }
        else
        {
            std::cout << "ERROR! Invalid instruction operation = " << instruction.m_operation << std::endl;
            ++instructionIdx;
        }
    }

    delete[] executedInstructions;

    if (instructionIdx < m_instructionCount)
    {
        std::cout << "Loop detected at instruction #" << instructionIdx << " with accumulator value = " << accumulatorValue << std::endl;
        return false;
    }
    else
    {
        std::cout << "Program terminated with accumulator value = " << accumulatorValue << std::endl;
        return true;
    }
}
