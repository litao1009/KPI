#include "ChartController.h"

#include "Frame/OgreEnv.h"

#include "Ogre.h"
#include "Compositor/OgreCompositorManager2.h"
#include "Compositor/OgreCompositorWorkspace.h"
#include "Compositor/OgreCompositorChannel.h"

#include "Frame/Extension/RectExt.h"
#include "Frame/Extension/Line2D.h"

#include <random>

enum ERenderGroup
{
	ERG_Node = Ogre::RENDER_QUEUE_MAIN + 1
};

static const auto CircleSize = 30.f;
static const auto CircleStepRange = 100.f;
static const auto valueBeg = -CircleStepRange * 4;
static const auto valueEnd = CircleStepRange * 3;
static const auto circleCount = 8;

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

	Ogre::SceneNode*			SNode_{};
	Ogre::SceneNode*			YNode_{};
	Ogre::SceneNode*			HNode_{};

	std::vector<Line2D*>		SLineList_;
	std::vector<RectExt*>		SCircleList_;
	std::vector<Line2D*>		YLineList_;
	std::vector<RectExt*>		YCircleList_;
	std::vector<Line2D*>		HLineList_;
	std::vector<RectExt*>		HCircleList_;

	void	SetValue( int syh, int index, int value )
	{
		auto& lineList = ( syh == 0 ) ? SLineList_ : ( ( syh == 1 ) ? YLineList_ : HLineList_ );
		auto& circleList = ( syh == 0 ) ? SCircleList_ : ( ( syh == 1 ) ? YCircleList_ : HCircleList_ );

		auto circleNode = circleList[index]->getParentSceneNode();
		circleNode->setVisible( true );
		auto curPos = circleNode->getPosition();
		circleNode->setPosition( curPos.x, CalcuValue( value ), 0.f );

		auto line = lineList[index];
		line->getParentSceneNode()->setVisible( true );
		if ( index == 0 )
		{
			line->SetStartPoint( { valueBeg - CircleStepRange / 2.2f, CalcuValue( 0 ), 0.f } );
		}
		else
		{
			auto preNode = circleList[index - 1]->getParentSceneNode();
			line->SetStartPoint( preNode->getPosition() );
		}

		line->SetEndPoint( circleNode->getPosition() );
	}
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
		imp_.SNode_ = imp_.Smgr_->getRootSceneNode()->createChildSceneNode();
		imp_.SNode_->setPosition( -sceneHeight, 0.f, 0.f );

		auto cbNode = imp_.SNode_->createChildSceneNode();
		cbNode->setScale(sceneHeight, sceneHeight, 1.f);
		auto rect = RectExtFactory::CreateInstance(imp_.Smgr_);
		rect->SetMaterial("Chart/s/BG");
		cbNode->attachObject(rect);

		for ( auto index = 0; index < circleCount; ++index )
		{
			auto lnode = imp_.SNode_->createChildSceneNode();
			auto l = Line2DFactory::CreateInstance( imp_.Smgr_ );
			lnode->attachObject( l );
			lnode->setVisible( false );
			imp_.SLineList_.push_back( l );
		}

		for ( auto index = 0; index < circleCount; ++index )
		{
			auto tnode = imp_.SNode_->createChildSceneNode();
			auto t = RectExtFactory::CreateInstance( imp_.Smgr_ );
			t->SetMaterial( "Chart/Node" );
			t->setRenderQueueGroup( ERG_Node );
			tnode->attachObject( t );
			tnode->setScale( CircleSize, CircleSize, 1.f );
			tnode->setPosition( valueBeg + index * CircleStepRange, CalcuValue( index * 100 / 8.f ), 0.f );
			tnode->setVisible( false );
			imp_.SCircleList_.push_back( t );
		}
	}

	{
		imp_.YNode_ = imp_.Smgr_->getRootSceneNode()->createChildSceneNode();
		imp_.YNode_->setPosition( -0.f, 0.f, 0.f );

		auto cbNode = imp_.YNode_->createChildSceneNode();
		cbNode->setScale(sceneHeight, sceneHeight, 1.f);
		auto rect = RectExtFactory::CreateInstance(imp_.Smgr_);
		rect->SetMaterial("Chart/y/BG");
		cbNode->attachObject(rect);

		for ( auto index = 0; index < circleCount; ++index )
		{
			auto lnode = imp_.YNode_->createChildSceneNode();
			auto l = Line2DFactory::CreateInstance( imp_.Smgr_ );
			lnode->attachObject( l );
			lnode->setVisible( false );
			imp_.YLineList_.push_back( l );
		}

		for ( auto index = 0; index < circleCount; ++index )
		{
			auto tnode = imp_.YNode_->createChildSceneNode();
			auto t = RectExtFactory::CreateInstance( imp_.Smgr_ );
			t->SetMaterial( "Chart/Node" );
			t->setRenderQueueGroup( ERG_Node );
			tnode->attachObject( t );
			tnode->setScale( CircleSize, CircleSize, 1.f );
			tnode->setPosition( valueBeg + index * CircleStepRange, CalcuValue( index * 100 / 8.f ), 0.f );
			tnode->setVisible( false );
			imp_.YCircleList_.push_back( t );
		}
	}

	{
		imp_.HNode_ = imp_.Smgr_->getRootSceneNode()->createChildSceneNode();
		imp_.HNode_->setPosition( sceneHeight, 0.f, 0.f );

		auto cbNode = imp_.HNode_->createChildSceneNode();
		cbNode->setScale(sceneHeight, sceneHeight, 1.f);
		auto rect = RectExtFactory::CreateInstance(imp_.Smgr_);
		rect->SetMaterial("Chart/h/BG");
		cbNode->attachObject(rect);

		for ( auto index = 0; index < circleCount; ++index )
		{
			auto lnode = imp_.HNode_->createChildSceneNode();
			auto l = Line2DFactory::CreateInstance( imp_.Smgr_ );
			lnode->attachObject( l );
			lnode->setVisible( false );
			imp_.HLineList_.push_back( l );
		}

		for ( auto index = 0; index < circleCount; ++index )
		{
			auto tnode = imp_.HNode_->createChildSceneNode();
			auto t = RectExtFactory::CreateInstance( imp_.Smgr_ );
			t->SetMaterial( "Chart/Node" );
			t->setRenderQueueGroup( ERG_Node );
			tnode->attachObject( t );
			tnode->setScale( CircleSize, CircleSize, 1.f );
			tnode->setPosition( valueBeg + index * CircleStepRange, CalcuValue( index * 100 / 8.f ), 0.f );
			tnode->setVisible( false );
			imp_.HCircleList_.push_back( t );
		}
	}

	std::default_random_engine dre;
	std::uniform_int_distribution<int> uid( 0, 100 );

	imp_.SetValue( 0, 0, uid(dre) );
	imp_.SetValue( 1, 0, uid( dre ) );
	imp_.SetValue( 2, 0, uid( dre ) );

	imp_.SetValue( 0, 1, uid( dre ) );
	imp_.SetValue( 1, 1, uid( dre ) );
	imp_.SetValue( 2, 1, uid( dre ) );

	imp_.SetValue( 0, 2, uid( dre ) );
	imp_.SetValue( 1, 2, uid( dre ) );
	imp_.SetValue( 2, 2, uid( dre ) );

	imp_.SetValue( 0, 3, uid( dre ) );
	imp_.SetValue( 1, 3, uid( dre ) );
	imp_.SetValue( 2, 3, uid( dre ) );

	imp_.SetValue( 0, 4, uid( dre ) );
	imp_.SetValue( 1, 4, uid( dre ) );
	imp_.SetValue( 2, 4, uid( dre ) );

	imp_.SetValue( 0, 5, uid( dre ) );
	imp_.SetValue( 1, 5, uid(dre) );
	imp_.SetValue( 2, 5, uid( dre ) );

	imp_.SetValue( 0, 6, uid( dre ) );
	imp_.SetValue( 1, 6, uid( dre ) );
	imp_.SetValue( 2, 6, uid( dre ) );

	imp_.SetValue( 0, 7, uid( dre ) );
	imp_.SetValue( 1, 7, uid( dre ) );
	imp_.SetValue( 2, 7, uid( dre ) );
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