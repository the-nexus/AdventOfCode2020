#include "Challenge_10.h"
#include "../Helpers/FileHelpers.h"



////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_10::sm_inputFilePath = "Inputs/Input_Challenge_10.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_10::SetUp_FirstPart()
{
    return LoadAdapters();
}

EErrorCode CChallenge_10::Run_FirstPart()
{
    std::map<int, int> m_adapterDifferenceMap;
    m_adapterDifferenceMap.insert(std::pair<int, int>(1, 0));
    m_adapterDifferenceMap.insert(std::pair<int, int>(2, 0));
    m_adapterDifferenceMap.insert(std::pair<int, int>(3, 0));

    int lastAdapterJolts = 0;
    for (int const adapterJolts : m_adapters)
    {
        ++m_adapterDifferenceMap[adapterJolts - lastAdapterJolts];
        lastAdapterJolts = adapterJolts;
    }

    int const joltDifferenceProduct = m_adapterDifferenceMap[1] * m_adapterDifferenceMap[3];
    std::cout << "Product of 1-jolt and 3-jolt differences = " << joltDifferenceProduct << std::endl;

    return EErrorCode::Success;
}

EErrorCode CChallenge_10::CleanUp_FirstPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_10::SetUp_SecondPart()
{
    return LoadAdapters();
}

EErrorCode CChallenge_10::Run_SecondPart()
{
    //std::vector<int> m_combinationPossibilities;
    //m_combinationPossibilities.resize(m_adapters.size());

    //for (size_t adapterIdx = 0; adapterIdx < m_adapters.size(); ++adapterIdx)
    //{
    //    size_t const adapterReverseIdx = m_adapters.size() - adapterIdx - 1;

    //    int const combinations = 1;
    //    size_t nextAdapterIdx = adapterReverseIdx - 1;
    //    while ()
    //}

    return EErrorCode::NotImplemented;
}

EErrorCode CChallenge_10::CleanUp_SecondPart()
{
    return EErrorCode::NotImplemented;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_10::LoadAdapters()
{
    std::vector<std::string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    m_adapters.reserve(lines.size() + 1);
    for (std::string const& line : lines)
    {
        int const adapterJolts = atoi(line.c_str());
        m_adapters.push_back(adapterJolts);
    }

    std::sort(m_adapters.begin(), m_adapters.end());

    int const builtInAdapterJolts = m_adapters.back() + 3;
    m_adapters.push_back(builtInAdapterJolts);

    return EErrorCode::Success;
}
