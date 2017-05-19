#include "ChartController.h"

#include "Frame/OgreEnv.h"

#include "Ogre.h"
#include "Compositor/OgreCompositorManager2.h"
#include "Compositor/OgreCompositorWorkspace.h"
#include "Compositor/OgreCompositorChannel.h"

#include "Frame/Extension/RectExt.h"
#include "Frame/Extension/TexNumber.h"

enum ERenderGroup
{
	ERG_Node = Ogre::RENDER_QUEUE_MAIN + 1
};

static const auto nodeSize = 30.f;
static const auto nodeRange = 100.f;
static const auto valueBeg = -nodeRange * 4;
static const auto valueEnd = nodeRange * 3;

static float	CalcuValue(float nr)
{
	auto f = nr / 100.f;
	return valueBeg + ( valueEnd - valueBeg ) * f;
}

class 	ChartController::Imp
{
public:

	Ogre::RenderWindow*			RT_{};
	Ogre::SceneManager*			Smgr_{};
	Ogre::CompositorWorkspace*	WorkSpce_{};
	Ogre::Camera*				Camera_{};
};

ChartController::ChartController( Ogre::RenderWindow *rt ):ImpUPtr_( new Imp )
{
	auto& imp_ = *ImpUPtr_;
	imp_.RT_ = rt;

	imp_.Smgr_ = Ogre::Root::getSingletonPtr()->createSceneManager( Ogre::ST_GENERIC, 1, Ogre::INSTANCING_CULLING_SINGLETHREAD, "ChartScene" );

	auto sceneHeight = 1024.f;
	auto sceneWidth = 2048.f;

	auto camera = imp_.Smgr_->createCamera( "MainCamera" );
	camera->setAutoAspectRatio( true );
	camera->setFOVy( Ogre::Degree( 60.f ) );
	camera->setNearClipDistance( 5.f );
	camera->setFarClipDistance( 5000.f );
	camera->setProjectionType( Ogre::PT_ORTHOGRAPHIC );
	camera->setOrthoWindowHeight( sceneHeight );

	auto cameraNode = imp_.Smgr_->getRootSceneNode()->createChildSceneNode();
	camera->detachFromParent();
	cameraNode->attachObject( camera );
	camera->setDirection( Ogre::Vector3::NEGATIVE_UNIT_Z );
	cameraNode->setPosition( Ogre::Vector3( 0, 0, 2000 ) );
	imp_.Camera_ = camera;

	auto comMgr = Ogre::Root::getSingletonPtr()->getCompositorManager2();

	imp_.WorkSpce_ = comMgr->addWorkspace(imp_.Smgr_, imp_.RT_, camera, "ChartWorkspace", true);

	{
		auto sRootNode = imp_.Smgr_->getRootSceneNode()->createChildSceneNode();
		sRootNode->setPosition(-sceneHeight, 0.f, 0.f);

		auto cbNode = sRootNode->createChildSceneNode();
		cbNode->setScale(sceneHeight, sceneHeight, 1.f);
		auto rect = RectExtFactory::CreateInstance(imp_.Smgr_);
		rect->SetMaterial("Chart/s/BG");
		cbNode->attachObject(rect);

		{
			auto tnode = sRootNode->createChildSceneNode();
			auto t = RectExtFactory::CreateInstance(imp_.Smgr_);
			t->SetMaterial("Chart/Node");
			t->setRenderQueueGroup(ERG_Node);
			tnode->attachObject(t);
			tnode->setScale(nodeSize, nodeSize, 1.f);
			tnode->setPosition(-nodeRange * 4, CalcuValue(0 * 100 / 8.f), 0.f);
		}

		{
			auto tnode = sRootNode->createChildSceneNode();
			auto t = RectExtFactory::CreateInstance(imp_.Smgr_);
			t->SetMaterial("Chart/Node");
			t->setRenderQueueGroup(ERG_Node);
			tnode->attachObject(t);
			tnode->setScale(nodeSize, nodeSize, 1.f);
			tnode->setPosition(-nodeRange * 3, CalcuValue(1 * 100 / 8.f), 0.f);
		}

		{
			auto tnode = sRootNode->createChildSceneNode();
			auto t = RectExtFactory::CreateInstance(imp_.Smgr_);
			t->SetMaterial("Chart/Node");
			t->setRenderQueueGroup(ERG_Node);
			tnode->attachObject(t);
			tnode->setScale(nodeSize, nodeSize, 1.f);
			tnode->setPosition(-nodeRange * 2, CalcuValue(2 * 100 / 8.f), 0.f);
		}

		{
			auto tnode = sRootNode->createChildSceneNode();
			auto t = RectExtFactory::CreateInstance(imp_.Smgr_);
			t->SetMaterial("Chart/Node");
			t->setRenderQueueGroup(ERG_Node);
			tnode->attachObject(t);
			tnode->setScale(nodeSize, nodeSize, 1.f);
			tnode->setPosition(-nodeRange * 1, CalcuValue(3 * 100 / 8.f), 0.f);
		}

		{
			auto tnode = sRootNode->createChildSceneNode();
			auto t = RectExtFactory::CreateInstance(imp_.Smgr_);
			t->SetMaterial("Chart/Node");
			t->setRenderQueueGroup(ERG_Node);
			tnode->attachObject(t);
			tnode->setScale(nodeSize, nodeSize, 1.f);
			tnode->setPosition(nodeRange * 0, CalcuValue(4 * 100 / 8.f), 0.f);
		}

		{
			auto tnode = sRootNode->createChildSceneNode();
			auto t = RectExtFactory::CreateInstance(imp_.Smgr_);
			t->SetMaterial("Chart/Node");
			t->setRenderQueueGroup(ERG_Node);
			tnode->attachObject(t);
			tnode->setScale(nodeSize, nodeSize, 1.f);
			tnode->setPosition(nodeRange * 1, CalcuValue(5 * 100 / 8.f), 0.f);
		}

		{
			auto tnode = sRootNode->createChildSceneNode();
			auto t = RectExtFactory::CreateInstance(imp_.Smgr_);
			t->SetMaterial("Chart/Node");
			t->setRenderQueueGroup(ERG_Node);
			tnode->attachObject(t);
			tnode->setScale(nodeSize, nodeSize, 1.f);
			tnode->setPosition(nodeRange * 2, CalcuValue(6 * 100 / 8.f), 0.f);
		}

		{
			auto tnode = sRootNode->createChildSceneNode();
			auto t = RectExtFactory::CreateInstance(imp_.Smgr_);
			t->SetMaterial("Chart/Node");
			t->setRenderQueueGroup(ERG_Node);
			tnode->attachObject(t);
			tnode->setScale(nodeSize, nodeSize, 1.f);
			tnode->setPosition(nodeRange * 3, CalcuValue(7 * 100 / 8.f), 0.f);
		}
	}

	{
		auto yRootNode = imp_.Smgr_->getRootSceneNode()->createChildSceneNode();
		yRootNode->setPosition(-0.f, 0.f, 0.f);

		auto cbNode = yRootNode->createChildSceneNode();
		cbNode->setScale(sceneHeight, sceneHeight, 1.f);
		auto rect = RectExtFactory::CreateInstance(imp_.Smgr_);
		rect->SetMaterial("Chart/y/BG");
		cbNode->attachObject(rect);
	}

	{
		auto hRootNode = imp_.Smgr_->getRootSceneNode()->createChildSceneNode();
		hRootNode->setPosition(sceneHeight, 0.f, 0.f);

		auto cbNode = hRootNode->createChildSceneNode();
		cbNode->setScale(sceneHeight, sceneHeight, 1.f);
		auto rect = RectExtFactory::CreateInstance(imp_.Smgr_);
		rect->SetMaterial("Chart/h/BG");
		cbNode->attachObject(rect);
	}
}

ChartController::~ChartController()
{
	auto& imp_ = *ImpUPtr_;

	Unload();
	
	auto comMgr = Ogre::Root::getSingletonPtr()->getCompositorManager2();
	comMgr->removeWorkspace( imp_.WorkSpce_ );
	Ogre::Root::getSingletonPtr()->destroySceneManager( imp_.Smgr_ );
}

void ChartController::_FrameStart( const Ogre::FrameEvent& fevt )
{
	auto& imp_ = *ImpUPtr_;

	auto& evtRecorder = GetSysEventRecorder();
}