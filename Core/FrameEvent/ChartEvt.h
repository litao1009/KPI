#pragma once

#include "FrameEvent.h"

class	ChartEvt : public TFrameEvent<ChartEvt>
{
public:

	std::vector<std::tuple<int, int, int>>	DataList_;
	int		DayBegin_{};
	bool	Clear_{};
};