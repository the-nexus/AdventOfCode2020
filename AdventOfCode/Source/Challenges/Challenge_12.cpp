#include "Challenge_12.h"
#include "../Helpers/FileHelpers.h"



////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_12::sm_inputFilePath = "Inputs/Input_Challenge_12.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_12::SetUp_FirstPart()
{
    return FileHelper::ReadLines(sm_inputFilePath, m_instructions);
}

EErrorCode CChallenge_12::Run_FirstPart()
{
    int shipPosX = 0;
    int shipPosY = 0;

    int waypointPosX = 1;
    int waypointPosY = 0;

    for (std::string const& instruction : m_instructions)
    {
        char const operation = instruction[0];
        int const parameter = atoi(instruction.substr(1).c_str());

        switch (operation)
        {
        case 'L':
            RotatePosAroundOrigin(4 - parameter / 90, waypointPosX, waypointPosY);
            break;

        case 'R':
            RotatePosAroundOrigin(parameter / 90, waypointPosX, waypointPosY);
            break;

        case 'F':
            shipPosX += waypointPosX * parameter;
            shipPosY += waypointPosY * parameter;
            break;

        case 'N':
            shipPosY += parameter;
            break;

        case 'E':
            shipPosX += parameter;
            break;

        case 'S':
            shipPosY -= parameter;
            break;

        case 'W':
            shipPosX -= parameter;
            break;

        default:
            return EErrorCode::Undefined;
        }
    }

    int const manhattanDistance = abs(shipPosX) + abs(shipPosY);
    std::cout << "Manhattan distance = " << manhattanDistance << std::endl;

    return EErrorCode::Success;
}

EErrorCode CChallenge_12::CleanUp_FirstPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_12::SetUp_SecondPart()
{
    return FileHelper::ReadLines(sm_inputFilePath, m_instructions);
}

EErrorCode CChallenge_12::Run_SecondPart()
{
    int shipPosX = 0;
    int shipPosY = 0;

    int waypointPosX = 10;
    int waypointPosY = 1;

    for (std::string const& instruction : m_instructions)
    {
        char const operation = instruction[0];
        int const parameter = atoi(instruction.substr(1).c_str());

        switch (operation)
        {
        case 'L':
            RotatePosAroundOrigin(4 - parameter / 90, waypointPosX, waypointPosY);
            break;

        case 'R':
            RotatePosAroundOrigin(parameter / 90, waypointPosX, waypointPosY);
            break;

        case 'F':
            shipPosX += waypointPosX * parameter;
            shipPosY += waypointPosY * parameter;
            break;

        case 'N':
            waypointPosY += parameter;
            break;

        case 'E':
            waypointPosX += parameter;
            break;

        case 'S':
            waypointPosY -= parameter;
            break;

        case 'W':
            waypointPosX -= parameter;
            break;

        default:
            return EErrorCode::Undefined;
        }
    }

    int const manhattanDistance = abs(shipPosX) + abs(shipPosY);
    std::cout << "Manhattan distance = " << manhattanDistance << std::endl;

    return EErrorCode::Success;
}

EErrorCode CChallenge_12::CleanUp_SecondPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
void CChallenge_12::RotatePosAroundOrigin(int const stepCount, int& waypointX, int& waypointY)
{
    int newWaypointX = waypointX;
    int newWaypointY = waypointY;

    if (stepCount == 1)
    {
        newWaypointX = waypointY;
        newWaypointY = -waypointX;
    }
    else if (stepCount == 2)
    {
        newWaypointX = -waypointX;
        newWaypointY = -waypointY;
    }
    else if (stepCount == 3)
    {
        newWaypointX = -waypointY;
        newWaypointY = waypointX;
    }

    waypointX = newWaypointX;
    waypointY = newWaypointY;
}
