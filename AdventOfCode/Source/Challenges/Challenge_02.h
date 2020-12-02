#pragma once

#include "Common/Challenge.h"

class CChallenge_02 : public CChallenge
{
private:
    struct SPasswordPolicy
    {
        std::string m_password = "";
        char m_requiredCharacter = '\0';
        int m_mininmumRequirement = 0;
        int m_maximumRequirement = 0;
        bool m_isValid = false;
    };

    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    static bool IsValidSledPassword(std::string const& password, char const requiredChar, int const minCharCount, int const maxCharCount);
    static bool IsValidTobogganPassword(std::string const& password, char const requiredChar, size_t const firstPos, size_t const secondPos);

    static std::string const sm_inputFilePath;
    std::vector<std::string> m_passwordPolicies;
};
