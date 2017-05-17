#pragma once

#include "Frame/IController.h"

#include "OgrePrerequisites.h"

class ChartController : public IController
{
	class 	Imp;
	std::unique_ptr<Imp>	ImpUPtr_;

public:

	ChartController( Ogre::RenderWindow* rt );

	~ChartController();

private:

	virtual void	_FrameStart(const Ogre::FrameEvent& fevt) override;
};

