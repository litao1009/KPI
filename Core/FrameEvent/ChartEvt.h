#pragma once

#include "FrameEvent.h"

class	ChartEvt : public TFrameEvent<ChartEvt>
{
public:

	float	Moisture{};
	float	Fat{};
	float	Melanin{};
	int		Day_{};
	bool	Clear_{};
};