#include "Challenge_02.h"
#include "../Helpers/FileHelpers.h"



////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_02::sm_inputFilePath = "Inputs/Input_Challenge_02.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_02::SetUp_FirstPart()
{
    return FileHelper::ReadLines(sm_inputFilePath, m_passwordPolicies);
}

EErrorCode CChallenge_02::Run_FirstPart()
{
    int validPasswordCount = 0;
    for (std::string const& passwordPolicy : m_passwordPolicies)
    {
        size_t const dashSeparatorIdx = passwordPolicy.find('-');
        size_t const spaceSeparatorIdx = passwordPolicy.find(' ', dashSeparatorIdx);
        size_t const colonSeparatorIdx = passwordPolicy.find(':', spaceSeparatorIdx);

        std::string const password = passwordPolicy.substr(colonSeparatorIdx + 2);
        char const requiredChar = passwordPolicy[spaceSeparatorIdx + 1];
        int const minCharCount = atoi(passwordPolicy.substr(0, dashSeparatorIdx).c_str());
        int const maxCharCount = atoi(passwordPolicy.substr(dashSeparatorIdx + 1, spaceSeparatorIdx).c_str());

        if (IsValidSledPassword(password, requiredChar, minCharCount, maxCharCount))
        {
            validPasswordCount++;
        }
    }

    std::cout << "Valid password count = " << validPasswordCount << std::endl;
    return EErrorCode::Success;
}

EErrorCode CChallenge_02::CleanUp_FirstPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_02::SetUp_SecondPart()
{
    return FileHelper::ReadLines(sm_inputFilePath, m_passwordPolicies);
}

EErrorCode CChallenge_02::Run_SecondPart()
{
    int validPasswordCount = 0;
    for (std::string const& passwordPolicy : m_passwordPolicies)
    {
        size_t const dashSeparatorIdx = passwordPolicy.find('-');
        size_t const spaceSeparatorIdx = passwordPolicy.find(' ', dashSeparatorIdx);
        size_t const colonSeparatorIdx = passwordPolicy.find(':', spaceSeparatorIdx);

        std::string const password = passwordPolicy.substr(colonSeparatorIdx + 2);
        char const requiredChar = passwordPolicy[spaceSeparatorIdx + 1];
        size_t const firstPos = atoi(passwordPolicy.substr(0, dashSeparatorIdx).c_str()) - 1;
        size_t const secondPos = atoi(passwordPolicy.substr(dashSeparatorIdx + 1, spaceSeparatorIdx).c_str()) - 1;

        if (IsValidTobogganPassword(password, requiredChar, firstPos, secondPos))
        {
            validPasswordCount++;
        }
    }

    std::cout << "Valid password count = " << validPasswordCount << std::endl;
    return EErrorCode::Success;
}

EErrorCode CChallenge_02::CleanUp_SecondPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
bool CChallenge_02::IsValidSledPassword(std::string const& password, char const requiredChar, int const minCharCount, int const maxCharCount)
{
    int charCount = 0;
    for (char const& passwordCharacter : password)
    {
        if (passwordCharacter == requiredChar)
        {
            ++charCount;
            if (charCount > maxCharCount)
            {
                return false;
            }
        }
    }
    return charCount >= minCharCount;
}

bool CChallenge_02::IsValidTobogganPassword(std::string const& password, char const requiredChar, size_t const firstPos, size_t const secondPos)
{
    size_t const passwordSize = password.size();
    int charCount = 0;

    if (firstPos < passwordSize && password[firstPos] == requiredChar)
    {
        ++charCount;
    }

    if (secondPos < passwordSize && password[secondPos] == requiredChar)
    {
        ++charCount;
    }

    return charCount == 1;
}
