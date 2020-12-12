#pragma once

#include "Common/Challenge.h"

class CChallenge_11 : public CChallenge
{
private:
    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    EErrorCode LoadBuffers();
    EErrorCode UnloadBuffers();
    void DrawBuffer() const;

    int StepSimulation(int const occupiedSeatTolerance, bool const useLineOfSight);
    int GetNeighbourhoodOccupiedSeatCount(size_t const anchorX, size_t const anchorY, bool const useLineOfSight) const;
    bool HasOccupiedSeatInLineOfSight(size_t const anchorX, size_t const anchorY, size_t const maxStepCount, int const stepX, int const stepY) const;

    static std::string const sm_inputFilePath;
    int** m_mainBuffer = nullptr;
    int** m_altBuffer = nullptr;
    size_t m_bufferWidth = 0;
    size_t m_bufferHeight = 0;
};
