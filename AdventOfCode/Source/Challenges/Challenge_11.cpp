#include "Challenge_11.h"
#include "../Helpers/FileHelpers.h"

#define DRAW_DEBUGS false



////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_11::sm_inputFilePath = "Inputs/Input_Challenge_11.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_11::SetUp_FirstPart()
{
    return LoadBuffers();
}

EErrorCode CChallenge_11::Run_FirstPart()
{
    if (DRAW_DEBUGS)
    {
        DrawBuffer();
        std::cout << std::endl;
    }

    // Simulate until stable
    int changedSeatCount = 1;
    int stepCount = 0;
    while (changedSeatCount > 0)
    {
        changedSeatCount = StepSimulation(4, false);

        if (DRAW_DEBUGS)
        {
            std::cout << "Simulation Step #" << ++stepCount << " changed seats = " << changedSeatCount << std::endl;
            DrawBuffer();
            std::cout << std::endl;
        }
    }

    // Count occupied seats
    int occupiedSeatCount = 0;
    for (size_t bufferY = 0; bufferY < m_bufferHeight; ++bufferY)
    {
        for (size_t bufferX = 0; bufferX < m_bufferWidth; ++bufferX)
        {
            if (m_mainBuffer[bufferY][bufferX] == 1)
            {
                ++occupiedSeatCount;
            }
        }
    }

    std::cout << "Occupied seats = " << occupiedSeatCount << std::endl;
    return EErrorCode::Success;
}

EErrorCode CChallenge_11::CleanUp_FirstPart()
{
    return UnloadBuffers();
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_11::SetUp_SecondPart()
{
    return LoadBuffers();
}

EErrorCode CChallenge_11::Run_SecondPart()
{
    if (DRAW_DEBUGS)
    {
        DrawBuffer();
        std::cout << std::endl;
    }

    // Simulate until stable
    int changedSeatCount = 1;
    int stepCount = 0;
    while (changedSeatCount > 0)
    {
        changedSeatCount = StepSimulation(5, true);

        if (DRAW_DEBUGS)
        {
            std::cout << "Simulation Step #" << ++stepCount << " changed seats = " << changedSeatCount << std::endl;
            DrawBuffer();
            std::cout << std::endl;
        }
    }

    // Count occupied seats
    int occupiedSeatCount = 0;
    for (size_t bufferY = 0; bufferY < m_bufferHeight; ++bufferY)
    {
        for (size_t bufferX = 0; bufferX < m_bufferWidth; ++bufferX)
        {
            if (m_mainBuffer[bufferY][bufferX] == 1)
            {
                ++occupiedSeatCount;
            }
        }
    }

    std::cout << "Occupied seats = " << occupiedSeatCount << std::endl;
    return EErrorCode::Success;
}

EErrorCode CChallenge_11::CleanUp_SecondPart()
{
    return UnloadBuffers();
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_11::LoadBuffers()
{
    std::vector<std::string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    size_t const height = lines.size();
    size_t const width = lines.size() > 0 ? lines[0].size() : 0;

    m_bufferHeight = height;
    m_bufferWidth = width;

    m_mainBuffer = new int*[height];
    m_altBuffer = new int*[height];

    for (size_t bufferY = 0; bufferY < height; ++bufferY)
    {
        m_mainBuffer[bufferY] = new int[width];
        m_altBuffer[bufferY] = new int[width];

        std::string const& line = lines[bufferY];
        for (size_t bufferX = 0; bufferX < width; ++bufferX)
        {
            char const initialStateChar = line[bufferX];
            if (initialStateChar == '.')
            {
                m_mainBuffer[bufferY][bufferX] = -1;
                m_altBuffer[bufferY][bufferX] = -1;
            }
            else if (initialStateChar == 'L')
            {
                m_mainBuffer[bufferY][bufferX] = 0;
                m_altBuffer[bufferY][bufferX] = 0;
            }
            else if (initialStateChar == '#')
            {
                m_mainBuffer[bufferY][bufferX] = 1;
                m_altBuffer[bufferY][bufferX] = 1;
            }
        }
    }

    return EErrorCode::Success;
}

EErrorCode CChallenge_11::UnloadBuffers()
{
    for (size_t bufferY = 0; bufferY < m_bufferHeight; ++bufferY)
    {
        delete m_mainBuffer[bufferY];
        delete m_altBuffer[bufferY];
    }

    delete[] m_mainBuffer;
    delete[] m_altBuffer;

    return EErrorCode::Success;
}

void CChallenge_11::DrawBuffer() const
{
    for (size_t bufferY = 0; bufferY < m_bufferHeight; ++bufferY)
    {
        for (size_t bufferX = 0; bufferX < m_bufferWidth; ++bufferX)
        {
            if (m_mainBuffer[bufferY][bufferX] == -1)
            {
                std::cout << '.';
            }
            else if (m_mainBuffer[bufferY][bufferX] == 0)
            {
                std::cout << 'L';
            }
            else if (m_mainBuffer[bufferY][bufferX] == 1)
            {
                std::cout << '#';
            }
        }
        std::cout << std::endl;
    }
}

int CChallenge_11::StepSimulation(int const occupiedSeatTolerance, bool const useLineOfSight)
{
    int changedSeatCount = 0;
    for (size_t bufferY = 0; bufferY < m_bufferHeight; ++bufferY)
    {
        for (size_t bufferX = 0; bufferX < m_bufferWidth; ++bufferX)
        {
            int bufferValue = m_mainBuffer[bufferY][bufferX];
            if (bufferValue == 0)
            {
                if (GetNeighbourhoodOccupiedSeatCount(bufferX, bufferY, useLineOfSight) == 0)
                {
                    bufferValue = 1;
                    ++changedSeatCount;
                }
            }
            else if (bufferValue == 1)
            {
                if (GetNeighbourhoodOccupiedSeatCount(bufferX, bufferY, useLineOfSight) >= occupiedSeatTolerance)
                {
                    bufferValue = 0;
                    ++changedSeatCount;
                }
            }
            m_altBuffer[bufferY][bufferX] = bufferValue;
        }
    }

    // Swap buffers
    int** tempBuffer = m_mainBuffer;
    m_mainBuffer = m_altBuffer;
    m_altBuffer = tempBuffer;

    return changedSeatCount;
}

int CChallenge_11::GetNeighbourhoodOccupiedSeatCount(size_t const anchorX, size_t const anchorY, bool const useLineOfSight) const
{
    size_t const maxStepCount = useLineOfSight ? -1 : 1;

    int occupiedSeatCount = 0;
    for (int stepY = -1; stepY <= 1; ++stepY)
    {
        for (int stepX = -1; stepX <= 1; ++stepX)
        {
            if (stepX != 0 || stepY != 0)
            {
                occupiedSeatCount += HasOccupiedSeatInLineOfSight(anchorX, anchorY, maxStepCount, stepX, stepY) ? 1 : 0;
            }
        }
    }

    return occupiedSeatCount;
}

bool CChallenge_11::HasOccupiedSeatInLineOfSight(size_t const anchorX, size_t const anchorY, size_t const maxStepCount, int const stepX, int const stepY) const
{
    size_t currentStep = 1;
    int bufferX = static_cast<int>(anchorX) + stepX;
    int bufferY = static_cast<int>(anchorY) + stepY;

    while (currentStep <= maxStepCount)
    {
        if (bufferX < 0 || bufferX >= m_bufferWidth ||
            bufferY < 0 || bufferY >= m_bufferHeight)
        {
            break;
        }

        if (m_mainBuffer[bufferY][bufferX] == 0)
        {
            return false;
        }
        else if (m_mainBuffer[bufferY][bufferX] == 1)
        {
            return true;
        }

        bufferX += stepX;
        bufferY += stepY;
        ++currentStep;
    }

    return false;
}
