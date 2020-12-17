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

    EErrorCode LoadInitialState(bool const is4D);
    void CreateCubeGrid(size_t const sizeX, size_t const sizeY, size_t const sizeZ, size_t const sizeW);
    void DestroyCubeGrid();
    size_t CycleCubeGrid();
    size_t CountActiveNeighbours(size_t const anchorX, size_t const anchorY, size_t const anchorZ, size_t const anchorW) const;
    void DrawCubeGrid() const;

    static std::string const sm_inputFilePath;
    bool**** m_cubeGrid = nullptr;
    bool**** m_altCubeGrid = nullptr;
    size_t m_cubeSizeX = 0;
    size_t m_cubeSizeY = 0;
    size_t m_cubeSizeZ = 0;
    size_t m_cubeSizeW = 0;
};
