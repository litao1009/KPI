#pragma once

#include "FrameEvent.h"


class	ResizeEvt : public TFrameEvent<ResizeEvt>
{
public:

};

class	IndicatorEvt : public TFrameEvent<IndicatorEvt>
{
public:

	float	Moisture{};
	float	Fat{};
	float	Melanin{};
	bool	Male{};
	int		Age_{};
};