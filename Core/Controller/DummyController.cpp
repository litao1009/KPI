#include "DummyController.h"

#include "Frame/OgreEnv.h"

#include "Ogre.h"
#include "Compositor/OgreCompositorManager2.h"
#include "Compositor/OgreCompositorWorkspace.h"
#include "Compositor/OgreCompositorChannel.h"

#include "Frame/Extension/RectExt.h"

#include "OgreOverlayManager.h"
#include "OgreOverlay.h"
#include "OgreOverlayContainer.h"
#include "OgreOverlaySystem.h"

enum ERenderGroup
{
	ERG_Scale = Ogre::RENDER_QUEUE_MAIN,
	ERG_Pointer,
	ERG_Panel
};

class 	DummyController::Imp
{
public:

	Ogre::RenderWindow*			RT_{};
	Ogre::SceneManager*			Smgr_{};
	Ogre::CompositorWorkspace*	WorkSpce_{};
	Ogre::Camera*				Camera_{};

	Ogre::SceneNode*			Pointer1Node_{};
	Ogre::SceneNode*			Pointer2Node_{};
	Ogre::SceneNode*			Pointer3Node_{};

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

	imp_.WorkSpce_ = comMgr->addWorkspace(imp_.Smgr_, imp_.RT_, camera, "IndicatorWorkspace", true);

	auto pieceWidth = imp_.RT_->getWidth() / 4.f;

	{//comparison
		auto node = imp_.Smgr_->getRootSceneNode()->createChildSceneNode();
		node->setScale(200, 200, 1);
		node->setPosition(pieceWidth * 1.5f, 0, 0);

		auto rect = RectExtFactory::CreateInstance(imp_.Smgr_);
		rect->SetMaterial("Comparison");
		node->attachObject(rect);
	}

	{//panel1
		auto node = imp_.Smgr_->getRootSceneNode()->createChildSceneNode();
		node->setScale(200, 200, 1);
		node->setPosition(-pieceWidth * 1.5f, 200, 0);

		auto panel1 = RectExtFactory::CreateInstance(imp_.Smgr_);
		panel1->SetMaterial("Mat/Base/Color/WithoutLight");
		panel1->setCustomParameter(0, Ogre::Vector4(1, 0, 0, 1));
		panel1->setRenderQueueGroup(ERG_Scale);
		node->attachObject(panel1);

		imp_.Pointer1Node_ = node->createChildSceneNode();
		auto pointer1 = RectExtFactory::CreateInstance(imp_.Smgr_);
		pointer1->SetMaterial("Mat/Base/Color/WithoutLight");
		pointer1->setCustomParameter(0, Ogre::Vector4(0, 1, 0, 1));
		pointer1->setRenderQueueGroup(ERG_Pointer);
		imp_.Pointer1Node_->attachObject(pointer1);

		imp_.Pointer1Node_->setScale(.1f, 1.f, 1.f);

		Ogre::Quaternion qua;
		qua.FromAngleAxis(Ogre::Degree(30), Ogre::Vector3::NEGATIVE_UNIT_Z);

		imp_.Pointer1Node_->setOrientation(qua);
	}

	{//panel2
		auto node = imp_.Smgr_->getRootSceneNode()->createChildSceneNode();
		node->setScale(200, 200, 1);
		node->setPosition(-pieceWidth * .5f, 200, 0);

		auto panel1 = RectExtFactory::CreateInstance(imp_.Smgr_);
		panel1->SetMaterial("Mat/Base/Color/WithoutLight");
		panel1->setCustomParameter(0, Ogre::Vector4(1, 0, 0, 1));
		node->attachObject(panel1);
	}

	{//panel3
		auto node = imp_.Smgr_->getRootSceneNode()->createChildSceneNode();
		node->setScale(200, 200, 1);
		node->setPosition(pieceWidth * .5f, 200, 0);

		auto panel1 = RectExtFactory::CreateInstance(imp_.Smgr_);
		panel1->SetMaterial("Mat/Base/Color/WithoutLight");
		panel1->setCustomParameter(0, Ogre::Vector4(1, 0, 0, 1));
		node->attachObject(panel1);
	}
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
