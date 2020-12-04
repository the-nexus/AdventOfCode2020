#include "Challenge_04.h"
#include "../Helpers/FileHelpers.h"



////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_04::sm_inputFilePath = "Inputs/Input_Challenge_04.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_04::SetUp_FirstPart()
{
    return LoadPassportData();
}

EErrorCode CChallenge_04::Run_FirstPart()
{
    std::string const countryTag = "cid";
    int validPassports = 0;

    for (StringMapType const& entry : m_passports)
    {
        size_t const propertyCount = entry.size();
        if (propertyCount == 8)
        {
            ++validPassports;
        }
        else if (propertyCount == 7 && entry.find(countryTag) == entry.end())
        {
            ++validPassports;
        }
    }

    std::cout << "Valid passports = " << validPassports << std::endl;
    return EErrorCode::Success;
}

EErrorCode CChallenge_04::CleanUp_FirstPart()
{
    return EErrorCode::NotImplemented;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_04::SetUp_SecondPart()
{
    return LoadPassportData();
}

EErrorCode CChallenge_04::Run_SecondPart()
{
    std::string const birthYearTag = "byr";
    std::string const issueYearTag = "iyr";
    std::string const expirationYearTag = "eyr";
    std::string const heightTag = "hgt";
    std::string const hairColorTag = "hcl";
    std::string const eyeColorTag = "ecl";
    std::string const passportIdTag = "pid";
    std::string const countryTag = "cid";

    int validPassports = 0;

    for (StringMapType const& entry : m_passports)
    {
        if (entry.size() == 7 || entry.size() == 8)
        {
            auto const birthYearIt = entry.find(birthYearTag);
            if (birthYearIt == entry.end() || !IsValidBirthYear(birthYearIt->second))
            {
                continue;
            }

            auto const issueYearIt = entry.find(issueYearTag);
            if (issueYearIt == entry.end() || !IsValidIssueYear(issueYearIt->second))
            {
                continue;
            }

            auto const expirationYearIt = entry.find(expirationYearTag);
            if (expirationYearIt == entry.end() || !IsValidExpirationYear(expirationYearIt->second))
            {
                continue;
            }

            auto const heightIt = entry.find(heightTag);
            if (heightIt == entry.end() || !IsValidHeight(heightIt->second))
            {
                continue;
            }

            auto const hairColorIt = entry.find(hairColorTag);
            if (hairColorIt == entry.end() || !IsValidHairColor(hairColorIt->second))
            {
                continue;
            }

            auto const eyeColorIt = entry.find(eyeColorTag);
            if (eyeColorIt == entry.end() || !IsValidEyeColor(eyeColorIt->second))
            {
                continue;
            }

            auto const passportIdIt = entry.find(passportIdTag);
            if (passportIdIt == entry.end() || !IsValidPassportId(passportIdIt->second))
            {
                continue;
            }

            ++validPassports;
        }
    }

    std::cout << "Valid passports = " << validPassports << std::endl;
    return EErrorCode::Success;
}

EErrorCode CChallenge_04::CleanUp_SecondPart()
{
    return EErrorCode::NotImplemented;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_04::LoadPassportData()
{
    std::vector<std::string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    if (lines.size() > 0)
    {
        m_passports.push_back(StringMapType());
        for (std::string const& line : lines)
        {
            if (line.empty())
            {
                m_passports.push_back(StringMapType());
            }
            else
            {
                std::vector<std::string> items;
                FileHelper::SplitLine(line, " ", items);

                for (std::string const& item : items)
                {
                    size_t const colonIdx = item.find(':');
                    std::string const key = item.substr(0, colonIdx);
                    std::string const value = item.substr(colonIdx + 1);
                    m_passports.rbegin()->insert(StringPairType(key, value));
                }
            }
        }
    }

    return EErrorCode::Success;
}

bool CChallenge_04::IsValidBirthYear(std::string const& birthYearStr)
{
    int const birthYear = atoi(birthYearStr.c_str());
    return birthYear >= 1920 && birthYear <= 2002;
}

bool CChallenge_04::IsValidIssueYear(std::string const& issueYearStr)
{
    int const issueYear = atoi(issueYearStr.c_str());
    return issueYear >= 2010 && issueYear <= 2020;
}

bool CChallenge_04::IsValidExpirationYear(std::string const& exiprationYearStr)
{
    int const expirationYear = atoi(exiprationYearStr.c_str());
    return expirationYear >= 2020 && expirationYear <= 2030;
}

bool CChallenge_04::IsValidHeight(std::string const& heightStr)
{
    size_t const strSize = heightStr.size();
    if (strSize > 3)
    {
        if (heightStr[strSize - 2] == 'c' && heightStr[strSize - 1] == 'm')
        {
            int const height = atoi(heightStr.substr(0, strSize - 2).c_str());
            return height >= 150 && height <= 193;
        }
        else if (heightStr[strSize - 2] == 'i' && heightStr[strSize - 1] == 'n')
        {
            int const height = atoi(heightStr.substr(0, strSize - 2).c_str());
            return height >= 59 && height <= 76;
        }
    }
    return false;
}

bool CChallenge_04::IsValidHairColor(std::string const& hairColorStr)
{
    size_t const strSize = hairColorStr.size();
    if (strSize != 7 || hairColorStr[0] != '#')
    {
        return false;
    }

    for (size_t strIdx = 1; strIdx < strSize; ++strIdx)
    {
        char const strChararacter = hairColorStr[strIdx];
        if (!(strChararacter >= '0' && strChararacter <= '9') &&
            !(strChararacter >= 'a' && strChararacter <= 'f'))
        {
            return false;
        }
    }

    return true;
}

bool CChallenge_04::IsValidEyeColor(std::string const& eyeColorStr)
{
    return eyeColorStr.compare("amb") == 0
        || eyeColorStr.compare("blu") == 0
        || eyeColorStr.compare("brn") == 0
        || eyeColorStr.compare("gry") == 0
        || eyeColorStr.compare("grn") == 0
        || eyeColorStr.compare("hzl") == 0
        || eyeColorStr.compare("oth") == 0;
}

bool CChallenge_04::IsValidPassportId(std::string const& passportIdStr)
{
    if (passportIdStr.size() != 9)
    {
        return false;
    }

    for (char const strChararacter : passportIdStr)
    {
        if (strChararacter < '0' || strChararacter > '9')
        {
            return false;
        }
    }

    return true;
}
