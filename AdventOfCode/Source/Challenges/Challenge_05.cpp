#include "Challenge_05.h"
#include "../Helpers/FileHelpers.h"



////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_05::sm_inputFilePath = "Inputs/Input_Challenge_05.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_05::SetUp_FirstPart()
{
    return FileHelper::ReadLines(sm_inputFilePath, m_boardingPasses);
}

EErrorCode CChallenge_05::Run_FirstPart()
{
	int const heightCharCount = 7;
	int const widthCharCount = 3;

	int highestSeatId = 0;

	size_t seatIdx = 0;
	for (std::string const& boardingPass : m_boardingPasses)
	{
		int x = 0;
		for (size_t widthIdx = 0; widthIdx < widthCharCount; ++widthIdx)
		{
			if (boardingPass[boardingPass.size() - widthIdx - 1] == 'R')
			{
				x += static_cast<int>(powf(2.f, static_cast<float>(widthIdx)));
			}
		}

		int y = 0;
		for (size_t heightIdx = 0; heightIdx < heightCharCount; ++heightIdx)
		{
			if (boardingPass[boardingPass.size() - heightIdx - widthCharCount - 1] == 'B')
			{
				y += static_cast<int>(powf(2.f, static_cast<float>(heightIdx)));
			}
		}

		int const seatId = y * 8 + x;
		if (seatId > highestSeatId)
		{
			highestSeatId = seatId;
		}
	}

	std::cout << "Highest seat ID = " << highestSeatId << std::endl;
    return EErrorCode::Success;
}

EErrorCode CChallenge_05::CleanUp_FirstPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_05::SetUp_SecondPart()
{
	return FileHelper::ReadLines(sm_inputFilePath, m_boardingPasses);
}

EErrorCode CChallenge_05::Run_SecondPart()
{
	int const heightCharCount = 7;
	int const widthCharCount = 3;

	int highestSeatId = 0;

	std::vector<int> seatIdList;
	seatIdList.reserve(m_boardingPasses.size());

	size_t seatIdx = 0;
	for (std::string const& boardingPass : m_boardingPasses)
	{
		int x = 0;
		for (size_t widthIdx = 0; widthIdx < widthCharCount; ++widthIdx)
		{
			if (boardingPass[boardingPass.size() - widthIdx - 1] == 'R')
			{
				x += static_cast<int>(powf(2.f, static_cast<float>(widthIdx)));
			}
		}

		int y = 0;
		for (size_t heightIdx = 0; heightIdx < heightCharCount; ++heightIdx)
		{
			if (boardingPass[boardingPass.size() - heightIdx - widthCharCount - 1] == 'B')
			{
				y += static_cast<int>(powf(2.f, static_cast<float>(heightIdx)));
			}
		}

		int const seatId = y * 8 + x;
		seatIdList.push_back(seatId);
	}

	std::sort(seatIdList.begin(), seatIdList.end());


	for (size_t seatIdx = 0; seatIdx < seatIdList.size(); ++seatIdx)
	{
		if (seatIdx < 8 || seatIdx > 1015)
		{
			continue;
		}

		if (seatIdList[seatIdx] + 2 == seatIdList[seatIdx + 1])
		{
			int const mySeatId = seatIdList[seatIdx] + 1;
			std::cout << "My seat ID = " << mySeatId << std::endl;
			break;
		}
	}

    return EErrorCode::Success;
}

EErrorCode CChallenge_05::CleanUp_SecondPart()
{
    return EErrorCode::Success;
}
