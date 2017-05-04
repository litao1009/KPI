#pragma once

#include "Frame/IController.h"

#include "OgrePrerequisites.h"

class DummyController : public IController
{
	class 	Imp;
	std::unique_ptr<Imp>	ImpUPtr_;

public:

	DummyController(Ogre::RenderWindow* rt);

	~DummyController();

private:

	virtual void	_FrameStart(const Ogre::FrameEvent& fevt) override;
};

