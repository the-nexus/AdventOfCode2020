#pragma once

#include "Common/Challenge.h"

class CChallenge_17 : public CChallenge
{
private:
    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    EErrorCode LoadInitialState();
    void CreateCubeGrid(size_t const gridSize);
    void DestroyCubeGrid();
    size_t CycleCubeGrid();
    size_t CountActiveNeighbours(size_t const anchorX, size_t const anchorY, size_t const anchorZ) const;
    void DrawCubeGrid() const;

    static std::string const sm_inputFilePath;
    bool*** m_cubeGrid = nullptr;
    bool*** m_altCubeGrid = nullptr;
    size_t m_cubeGridSize = 0;
};
