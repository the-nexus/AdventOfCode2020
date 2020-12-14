#include "Challenge_14.h"
#include "../Helpers/FileHelpers.h"



////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_14::sm_inputFilePath = "Inputs/Input_Challenge_14.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_14::SetUp_FirstPart()
{
    return FileHelper::ReadLines(sm_inputFilePath, m_lines);
}

EErrorCode CChallenge_14::Run_FirstPart()
{
    std::map<size_t, IntType> memoryMap;

    std::string maskStr = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
    IntType bitMasks[BIT_MASK_36];
    CreateBitMasks(bitMasks);

    for (std::string const& line : m_lines)
    {
        std::vector<std::string> items;
        FileHelper::SplitLine(line, " = ", items);

        if (items[0].compare("mask") == 0)
        {
            maskStr = items[1];
        }
        else
        {
            size_t const startIdx = items[0].find('[') + 1;
            size_t const endIdx = items[0].find(']', startIdx);
            std::string const memoryAddressStr = items[0].substr(startIdx, endIdx - startIdx);

            size_t const memoryAddress = atoll(memoryAddressStr.c_str());
            IntType const memoryValue = atoll(items[1].c_str());

            IntType maskedMemoryValue;
            GetMaskedMemoryValue(memoryValue, maskStr, bitMasks, maskedMemoryValue);

            memoryMap[memoryAddress] = maskedMemoryValue;
        }
    }

    IntType memorySum = 0;
    for (std::pair<size_t, IntType> const& memoryPair : memoryMap)
    {
        memorySum += memoryPair.second;
    }

    std::cout << "Memory sum = " << memorySum << std::endl;
    return EErrorCode::Success;
}

EErrorCode CChallenge_14::CleanUp_FirstPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_14::SetUp_SecondPart()
{
    return FileHelper::ReadLines(sm_inputFilePath, m_lines);
}

EErrorCode CChallenge_14::Run_SecondPart()
{
    std::map<size_t, IntType> memoryMap;

    std::string maskStr = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
    IntType bitMasks[BIT_MASK_36];
    CreateBitMasks(bitMasks);

    for (std::string const& line : m_lines)
    {
        std::vector<std::string> items;
        FileHelper::SplitLine(line, " = ", items);

        if (items[0].compare("mask") == 0)
        {
            maskStr = items[1];
        }
        else
        {
            size_t const startIdx = items[0].find('[') + 1;
            size_t const endIdx = items[0].find(']', startIdx);
            std::string const memoryAddressStr = items[0].substr(startIdx, endIdx - startIdx);

            size_t const memoryAddress = atoll(memoryAddressStr.c_str());
            IntType const memoryValue = atoll(items[1].c_str());

            std::vector<size_t> maskedMemoryAddresses;
            GetMaskedMemoryAddresses(memoryAddress, maskStr, bitMasks, maskedMemoryAddresses);

            for (size_t const maskedMemoryAddress : maskedMemoryAddresses)
            {
                memoryMap[maskedMemoryAddress] = memoryValue;
            }
        }
    }

    IntType memorySum = 0;
    for (std::pair<size_t, IntType> const& memoryPair : memoryMap)
    {
        memorySum += memoryPair.second;
    }

    std::cout << "Memory sum = " << memorySum << std::endl;
    return EErrorCode::Success;
}

EErrorCode CChallenge_14::CleanUp_SecondPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
void CChallenge_14::CreateBitMasks(IntType (&outBitMasks)[BIT_MASK_36])
{
    size_t const lastIdx = BIT_MASK_36 - 1;
    IntType bitMask = 1;

    for (size_t bitIdx = 0; bitIdx < BIT_MASK_36; ++bitIdx)
    {
        outBitMasks[lastIdx - bitIdx] = bitMask;
        bitMask *= 2;
    }
}

void CChallenge_14::GetMaskedMemoryValue(IntType const memoryValue, std::string const& maskStr, IntType const (&bitMasks)[BIT_MASK_36], IntType& outMaskedMemoryValue)
{
    size_t firstBitIdx = 0;
    while ((memoryValue && bitMasks[firstBitIdx]) == 0)
    {
        ++firstBitIdx;
    }

    outMaskedMemoryValue = 0;
    for (size_t bitIdx = firstBitIdx; bitIdx < BIT_MASK_36; ++bitIdx)
    {
        char const maskTypeChar = maskStr[bitIdx];
        IntType const bitMask = bitMasks[bitIdx];

        if (maskTypeChar == '1')
        {
            outMaskedMemoryValue += bitMask;
        }
        else if (maskTypeChar == 'X')
        {
            outMaskedMemoryValue += memoryValue & bitMask;
        }
    }
}

void CChallenge_14::GetMaskedMemoryAddresses(IntType const memoryAddress, std::string const& maskStr, IntType const (&bitMasks)[BIT_MASK_36], std::vector<size_t>& outMaskedMemoryAddresses)
{
    size_t firstBitIdx = 0;
    while ((memoryAddress && bitMasks[firstBitIdx]) == 0)
    {
        ++firstBitIdx;
    }

    outMaskedMemoryAddresses.push_back(0);
    for (size_t bitIdx = firstBitIdx; bitIdx < BIT_MASK_36; ++bitIdx)
    {
        char const maskTypeChar = maskStr[bitIdx];
        IntType const bitMask = bitMasks[bitIdx];

        if (maskTypeChar == '0')
        {
            size_t const addressCount = outMaskedMemoryAddresses.size();
            for (size_t addressIdx = 0; addressIdx < addressCount; ++addressIdx)
            {
                outMaskedMemoryAddresses[addressIdx] += memoryAddress & bitMask;
            }
        }
        else if (maskTypeChar == '1')
        {
            size_t const addressCount = outMaskedMemoryAddresses.size();
            for (size_t addressIdx = 0; addressIdx < addressCount; ++addressIdx)
            {
                outMaskedMemoryAddresses[addressIdx] += bitMask;
            }
        }
        else
        {
            size_t const initialAddressCount = outMaskedMemoryAddresses.size();
            for (size_t addressIdx = 0; addressIdx < initialAddressCount; ++addressIdx)
            {
                outMaskedMemoryAddresses.push_back(outMaskedMemoryAddresses[addressIdx]);
            }

            size_t const newAddressCount = outMaskedMemoryAddresses.size();
            for (size_t addressIdx = initialAddressCount; addressIdx < newAddressCount; ++addressIdx)
            {
                outMaskedMemoryAddresses[addressIdx] += bitMask;
            }
        }
    }
}
