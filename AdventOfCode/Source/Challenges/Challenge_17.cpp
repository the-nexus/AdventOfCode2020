#include "Challenge_17.h"
#include "../Helpers/FileHelpers.h"

#define DRAW_DEBUGS false


////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_17::sm_inputFilePath = "Inputs/Input_Challenge_17.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_17::SetUp_FirstPart()
{
    return LoadInitialState();
}

EErrorCode CChallenge_17::Run_FirstPart()
{
    static size_t const cycleCount = 6;

    if (DRAW_DEBUGS)
    {
        std::cout << "Initial state" << std::endl << std::endl;
        DrawCubeGrid();
        std::cout << std::endl << std::endl;
    }

    size_t activeCubeCount = 0;
    for (size_t currentCycle = 1; currentCycle <= cycleCount; ++currentCycle)
    {
        activeCubeCount = CycleCubeGrid();

        if (DRAW_DEBUGS)
        {
            std::cout << "Cycle #" << currentCycle << std::endl << std::endl;
            DrawCubeGrid();
            std::cout << std::endl << std::endl;
        }
    }

    std::cout << "Active cubeCount = " << activeCubeCount << std::endl;
    return EErrorCode::Success;
}

EErrorCode CChallenge_17::CleanUp_FirstPart()
{
    DestroyCubeGrid();
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_17::SetUp_SecondPart()
{
    return LoadInitialState();
}

EErrorCode CChallenge_17::Run_SecondPart()
{
    return EErrorCode::NotImplemented;
}

EErrorCode CChallenge_17::CleanUp_SecondPart()
{
    DestroyCubeGrid();
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_17::LoadInitialState()
{
    static size_t const gridSizeMultiplier = 7;

    std::vector<std::string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    size_t const inputGridSizeX = lines[0].size();
    size_t const inputGridSizeY = lines.size();
    size_t const inputGridSize = gridSizeMultiplier * (inputGridSizeY > inputGridSizeX ? inputGridSizeY : inputGridSizeX);
    CreateCubeGrid(inputGridSize);

    size_t const anchorX = (inputGridSize - inputGridSizeX) / 2;
    size_t const anchorY = (inputGridSize - inputGridSizeY) / 2;
    size_t const anchorZ = (inputGridSize - 1) / 2;

    for (size_t y = 0; y < inputGridSizeY; ++y)
    {
        std::string const& line = lines[y];

        for (size_t x = 0; x < inputGridSizeX; ++x)
        {
            bool const isCubeActive = line[x] == '#';
            m_cubeGrid[anchorZ][anchorY + y][anchorX + x] = isCubeActive;
            m_altCubeGrid[anchorZ][anchorY + y][anchorX + x] = isCubeActive;
        }
    }

    return EErrorCode::Success;
}

void CChallenge_17::CreateCubeGrid(size_t const gridSize)
{
    m_cubeGrid = new bool**[gridSize];
    m_altCubeGrid = new bool**[gridSize];

    for (size_t z = 0; z < gridSize; ++z)
    {
        m_cubeGrid[z] = new bool*[gridSize];
        m_altCubeGrid[z] = new bool*[gridSize];

        for (size_t y = 0; y < gridSize; ++y)
        {
            m_cubeGrid[z][y] = new bool[gridSize];
            m_altCubeGrid[z][y] = new bool[gridSize];

            for (size_t x = 0; x < gridSize; ++x)
            {
                m_cubeGrid[z][y][x] = false;
                m_altCubeGrid[z][y][x] = false;
            }
        }
    }

    m_cubeGridSize = gridSize;
}

void CChallenge_17::DestroyCubeGrid()
{
    for (size_t z = 0; z < m_cubeGridSize; ++z)
    {
        for (size_t y = 0; y < m_cubeGridSize; ++y)
        {
            delete[] m_cubeGrid[z][y];
            delete[] m_altCubeGrid[z][y];
        }

        delete[] m_cubeGrid[z];
        delete[] m_altCubeGrid[z];
    }

    delete[] m_cubeGrid;
    delete[] m_altCubeGrid;

    m_cubeGridSize = 0;
}

size_t CChallenge_17::CycleCubeGrid()
{
    size_t activeCubeCount = 0;

    for (size_t z = 1; z < m_cubeGridSize - 1; ++z)
    {
        for (size_t y = 1; y < m_cubeGridSize - 1; ++y)
        {
            for (size_t x = 1; x < m_cubeGridSize - 1; ++x)
            {
                bool cubeState = m_cubeGrid[z][y][x];
                size_t const activeNeighbourCount = CountActiveNeighbours(x, y, z);

                if (cubeState)
                {
                    if (activeNeighbourCount < 2 || activeNeighbourCount > 3)
                    {
                        cubeState = false;
                    }
                }
                else
                {
                    if (activeNeighbourCount == 3)
                    {
                        cubeState = true;
                    }
                }

                m_altCubeGrid[z][y][x] = cubeState;
                if (cubeState)
                {
                    ++activeCubeCount;
                }
            }
        }
    }

    std::swap(m_cubeGrid, m_altCubeGrid);
    return activeCubeCount;
}

size_t CChallenge_17::CountActiveNeighbours(size_t const anchorX, size_t const anchorY, size_t const anchorZ) const
{
    size_t activeNeighbourCount = 0;

    for (size_t z = anchorZ - 1; z <= anchorZ + 1; ++z)
    {
        for (size_t y = anchorY - 1; y <= anchorY + 1; ++y)
        {
            for (size_t x = anchorX - 1; x <= anchorX + 1; ++x)
            {
                if (x != anchorX || y != anchorY || z != anchorZ)
                {
                    if (m_cubeGrid[z][y][x])
                    {
                        ++activeNeighbourCount;
                    }
                }
            }
        }
    }

    return activeNeighbourCount;
}

void CChallenge_17::DrawCubeGrid() const
{
    for (size_t y = 0; y < m_cubeGridSize; ++y)
    {
        for (size_t z = 0; z < m_cubeGridSize; ++z)
        {
            for (size_t x = 0; x < m_cubeGridSize; ++x)
            {
                char const stateSymbol = m_cubeGrid[z][y][x] ? '#' : '.';
                std::cout << stateSymbol;
            }
            std::cout << "  ";
        }
        std::cout << std::endl;
    }
}
