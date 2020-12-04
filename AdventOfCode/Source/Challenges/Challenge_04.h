#pragma once

#include "Common/Challenge.h"

class CChallenge_04 : public CChallenge
{
private:

    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    EErrorCode LoadPassportData();

    static bool IsValidBirthYear(std::string const& birthYearStr);
    static bool IsValidIssueYear(std::string const& issueYearStr);
    static bool IsValidExpirationYear(std::string const& exiprationYearStr);
    static bool IsValidHeight(std::string const& heightStr);
    static bool IsValidHairColor(std::string const& hairColorStr);
    static bool IsValidEyeColor(std::string const& eyeColorStr);
    static bool IsValidPassportId(std::string const& passportIdStr);

    static std::string const sm_inputFilePath;

    typedef std::pair<std::string, std::string> StringPairType;
    typedef std::map<std::string, std::string> StringMapType;
    std::vector<StringMapType> m_passports;
};
