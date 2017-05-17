#pragma once

#include "Frame/IController.h"

#include "OgrePrerequisites.h"

class IndicatorController : public IController
{
	class 	Imp;
	std::unique_ptr<Imp>	ImpUPtr_;

public:

	IndicatorController(Ogre::RenderWindow* rt);

	~IndicatorController();

private:

	virtual void	_FrameStart(const Ogre::FrameEvent& fevt) override;
};

