#include "Challenge_17.h"
#include "../Helpers/FileHelpers.h"

#define DRAW_DEBUGS false


////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_17::sm_inputFilePath = "Inputs/Input_Challenge_17.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_17::SetUp_FirstPart()
{
    return LoadInitialState(false);
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
    return LoadInitialState(true);
}

EErrorCode CChallenge_17::Run_SecondPart()
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

        std::cout << "Cycle #" << currentCycle << std::endl << std::endl;
        if (DRAW_DEBUGS)
        {
            DrawCubeGrid();
            std::cout << std::endl << std::endl;
        }
    }

    std::cout << "Active cubeCount = " << activeCubeCount << std::endl;
    return EErrorCode::Success;
}

EErrorCode CChallenge_17::CleanUp_SecondPart()
{
    DestroyCubeGrid();
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_17::LoadInitialState(bool const is4D)
{
    static size_t const extraGridSize = 16;

    std::vector<std::string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    size_t const inputGridSizeX = extraGridSize + lines[0].size();
    size_t const inputGridSizeY = extraGridSize + lines.size();
    size_t const inputGridSizeZ = extraGridSize + (inputGridSizeY > inputGridSizeX ? inputGridSizeY : inputGridSizeX);
    size_t const inputGridSizeW = is4D ? inputGridSizeZ : 1;
    CreateCubeGrid(inputGridSizeX, inputGridSizeY, inputGridSizeZ, inputGridSizeW);

    size_t const anchorX = (inputGridSizeX - lines[0].size() - 1) / 2 + 1;
    size_t const anchorY = (inputGridSizeY - lines.size() - 1) / 2 + 1;
    size_t const anchorZ = (inputGridSizeZ - 1) / 2 + 1;
    size_t const anchorW = (inputGridSizeW - 1) / 2 + 1;

    for (size_t y = 0; y < lines.size(); ++y)
    {
        std::string const& line = lines[y];

        for (size_t x = 0; x < lines[0].size(); ++x)
        {
            bool const isCubeActive = line[x] == '#';
            m_cubeGrid[anchorW][anchorZ][anchorY + y][anchorX + x] = isCubeActive;
            m_altCubeGrid[anchorW][anchorZ][anchorY + y][anchorX + x] = isCubeActive;
        }
    }

    return EErrorCode::Success;
}

void CChallenge_17::CreateCubeGrid(size_t const sizeX, size_t const sizeY, size_t const sizeZ, size_t const sizeW)
{
    m_cubeSizeX = sizeX + 2;
    m_cubeSizeY = sizeY + 2;
    m_cubeSizeZ = sizeZ + 2;
    m_cubeSizeW = sizeW + 2;

    m_cubeGrid = new bool***[m_cubeSizeW];
    m_altCubeGrid = new bool***[m_cubeSizeW];

    for (size_t w = 0; w < m_cubeSizeW; ++w)
    {
        m_cubeGrid[w] = new bool**[m_cubeSizeZ];
        m_altCubeGrid[w] = new bool**[m_cubeSizeZ];

        for (size_t z = 0; z < m_cubeSizeZ; ++z)
        {
            m_cubeGrid[w][z] = new bool*[m_cubeSizeY];
            m_altCubeGrid[w][z] = new bool*[m_cubeSizeY];

            for (size_t y = 0; y < m_cubeSizeY; ++y)
            {
                m_cubeGrid[w][z][y] = new bool[m_cubeSizeX];
                m_altCubeGrid[w][z][y] = new bool[m_cubeSizeX];

                for (size_t x = 0; x < m_cubeSizeX; ++x)
                {
                    m_cubeGrid[w][z][y][x] = false;
                    m_altCubeGrid[w][z][y][x] = false;
                }
            }
        }
    }
}

void CChallenge_17::DestroyCubeGrid()
{
    for (size_t w = 0; w < m_cubeSizeW; ++w)
    {
        for (size_t z = 0; z < m_cubeSizeZ; ++z)
        {
            for (size_t y = 0; y < m_cubeSizeY; ++y)
            {
                delete[] m_cubeGrid[w][z][y];
                delete[] m_altCubeGrid[w][z][y];
            }

            delete[] m_cubeGrid[w][z];
            delete[] m_altCubeGrid[w][z];
        }

        delete[] m_cubeGrid[w];
        delete[] m_altCubeGrid[w];
    }

    delete[] m_cubeGrid;
    delete[] m_altCubeGrid;
}

size_t CChallenge_17::CycleCubeGrid()
{
    size_t activeCubeCount = 0;

    for (size_t w = 1; w < m_cubeSizeW - 1; ++w)
    {
        for (size_t z = 1; z < m_cubeSizeZ - 1; ++z)
        {
            for (size_t y = 1; y < m_cubeSizeY - 1; ++y)
            {
                for (size_t x = 1; x < m_cubeSizeX - 1; ++x)
                {
                    bool cubeState = m_cubeGrid[w][z][y][x];
                    size_t const activeNeighbourCount = CountActiveNeighbours(x, y, z, w);

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

                    m_altCubeGrid[w][z][y][x] = cubeState;
                    if (cubeState)
                    {
                        ++activeCubeCount;
                    }
                }
            }
        }
    }

    std::swap(m_cubeGrid, m_altCubeGrid);
    return activeCubeCount;
}

size_t CChallenge_17::CountActiveNeighbours(size_t const anchorX, size_t const anchorY, size_t const anchorZ, size_t const anchorW) const
{
    size_t activeNeighbourCount = 0;

    for (size_t w = anchorW - 1; w <= anchorW + 1; ++w)
    {
        for (size_t z = anchorZ - 1; z <= anchorZ + 1; ++z)
        {
            for (size_t y = anchorY - 1; y <= anchorY + 1; ++y)
            {
                for (size_t x = anchorX - 1; x <= anchorX + 1; ++x)
                {
                    if (x != anchorX || y != anchorY || z != anchorZ || w != anchorW)
                    {
                        if (m_cubeGrid[w][z][y][x])
                        {
                            ++activeNeighbourCount;
                        }
                    }
                }
            }
        }
    }

    return activeNeighbourCount;
}

void CChallenge_17::DrawCubeGrid() const
{
    for (size_t w = 1; w < m_cubeSizeW - 1; ++w)
    {
        for (size_t y = 1; y < m_cubeSizeY - 1; ++y)
        {
            for (size_t z = 1; z < m_cubeSizeZ - 1; ++z)
            {
                for (size_t x = 1; x < m_cubeSizeX - 1; ++x)
                {
                    char const stateSymbol = m_cubeGrid[w][z][y][x] ? '#' : '.';
                    std::cout << stateSymbol;
                }
                std::cout << "  ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}
