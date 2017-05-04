#include "DummyController.h"

#include "Ogre.h"
#include "Compositor/OgreCompositorManager2.h"
#include "Compositor/OgreCompositorWorkspace.h"
#include "Compositor/OgreCompositorChannel.h"

class 	DummyController::Imp
{
public:

	Ogre::RenderWindow*			RT_{};
	Ogre::SceneManager*			Smgr_{};
	Ogre::CompositorWorkspace*	WorkSpce_{};
	Ogre::Camera*				Camera_{};

public:
};

DummyController::DummyController(Ogre::RenderWindow *rt) :ImpUPtr_(new Imp)
{
	auto& imp_ = *ImpUPtr_;
	imp_.RT_ = rt;
	
	imp_.Smgr_ = Ogre::Root::getSingletonPtr()->createSceneManager(Ogre::ST_GENERIC, 1, Ogre::INSTANCING_CULLING_SINGLETHREAD, "DummyScene");

	auto camera = imp_.Smgr_->createCamera("MainCamera");
	camera->setAutoAspectRatio(true);
	camera->setFOVy(Ogre::Degree(60));
	camera->setNearClipDistance(5.f);
	camera->setFarClipDistance(5000.f);
	camera->setProjectionType(Ogre::PT_ORTHOGRAPHIC);
	camera->setOrthoWindowHeight(imp_.RT_->getHeight());
	
	auto cameraNode = imp_.Smgr_->getRootSceneNode()->createChildSceneNode();
	camera->detachFromParent();
	cameraNode->attachObject(camera);
	camera->setDirection(Ogre::Vector3::NEGATIVE_UNIT_Z);
	cameraNode->setPosition(Ogre::Vector3(0, 0, 2000));
	imp_.Camera_ = camera;
	
	auto comMgr = Ogre::Root::getSingletonPtr()->getCompositorManager2();

	imp_.WorkSpce_ = comMgr->addWorkspace(imp_.Smgr_, imp_.RT_, camera, "deformation2DWorkspace", true);
}

DummyController::~DummyController()
{
	auto& imp_ = *ImpUPtr_;

	Unload();

	auto comMgr = Ogre::Root::getSingletonPtr()->getCompositorManager2();
	comMgr->removeWorkspace(imp_.WorkSpce_);
	Ogre::Root::getSingletonPtr()->destroySceneManager(imp_.Smgr_);
}

void DummyController::_FrameStart(const Ogre::FrameEvent& fevt)
{
	auto& imp_ = *ImpUPtr_;

	auto& evtRecorder = GetSysEventRecorder();
}
