#include "DummyController.h"

#include "Frame/OgreEnv.h"

#include "Ogre.h"
#include "Compositor/OgreCompositorManager2.h"
#include "Compositor/OgreCompositorWorkspace.h"
#include "Compositor/OgreCompositorChannel.h"

#include "Frame/Extension/RectExt.h"
#include "Frame/Extension/TexNumber.h"
#include "FrameEvent/IndicatorEvt.h"

#include "OgreOverlayManager.h"
#include "OgreOverlay.h"
#include "OgreOverlayContainer.h"
#include "OgreOverlaySystem.h"

#include <vector>

static const auto panelOffset = 264.f;
static const auto introductionOffset = -188.f;
static const auto texOffset = -10.f;
static const auto charWidth = 40.f;
static const auto charHeight = 80.f;

enum ERenderGroup
{
	ERG_Panel = Ogre::RENDER_QUEUE_MAIN,
	ERG_Pointer,
	ERG_Num
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

	Ogre::SceneNode*			Ind1Char1Node_{};
	Ogre::SceneNode*			Ind1Char2Node_{};
	Ogre::SceneNode*			Ind1Char3Node_{};
	Ogre::SceneNode*			Ind1Char4Node_{};
	TexNumber*					Ind1Char1_{};
	TexNumber*					Ind1Char2_{};
	TexNumber*					Ind1Char3_{};

	Ogre::SceneNode*			Ind2Char1Node_{};
	Ogre::SceneNode*			Ind2Char2Node_{};
	Ogre::SceneNode*			Ind2Char3Node_{};
	Ogre::SceneNode*			Ind2Char4Node_{};
	TexNumber*					Ind2Char1_{};
	TexNumber*					Ind2Char2_{};
	TexNumber*					Ind2Char3_{};

	Ogre::SceneNode*			Ind3Char1Node_{};
	Ogre::SceneNode*			Ind3Char2Node_{};
	Ogre::SceneNode*			Ind3Char3Node_{};
	Ogre::SceneNode*			Ind3Char4Node_{};
	TexNumber*					Ind3Char1_{};
	TexNumber*					Ind3Char2_{};
	TexNumber*					Ind3Char3_{};

	RectExt*					Sex_{};
	TexNumber*					Age1_{};
	TexNumber*					Age2_{};
	TexNumber*					Age3_{};
	Ogre::SceneNode*			Age1Node_{};

public:

	void	SetSex(bool male)
	{
		if ( male )
		{
			Sex_->SetUV(2 / 8.f, 3 / 8.f, 0.f, 1.f);
		}
		else
		{
			Sex_->SetUV(3 / 8.f, 4 / 8.f, 0.f, 1.f);
		}
	}

	void	SetAge(int age)
	{
		auto a1 = age % 10;
		auto a2 = ( age / 10 ) % 10;
		auto a3 = ( age / 100 ) % 10;

		Age1_->SetIndex(a3);
		Age2_->SetIndex(a2);
		Age3_->SetIndex(a1);

		if ( a3 == 0 )
		{
			Age1Node_->setVisible(false);
		}
		else
		{
			Age1Node_->setVisible(true);
		}
	}

	void	UpdateValue( int moisture, int fat, int melanin )
	{
		moisture = std::max( 0, moisture );
		moisture = std::min( moisture, 100 );
		fat = std::max( 0, fat );
		fat = std::min( fat, 100 );
		melanin = std::max( 0, melanin );
		melanin = std::min( melanin, 100 );

		{
			auto p1 = ( moisture ) % 10;
			auto p2 = ( moisture / 10 ) % 10;
			auto p3 = ( moisture / 100 ) % 10;

			if ( moisture == 100 )
			{
				Ind1Char1_->SetIndex( p3 );
				Ind1Char2_->SetIndex( p2 );
				Ind1Char3_->SetIndex( p1 );

				Ind1Char1Node_->setVisible( true );
				Ind1Char2Node_->setVisible( true );
				Ind1Char3Node_->setVisible( true );
				Ind1Char4Node_->setVisible( true );

				Ind1Char1Node_->setPosition( -charWidth * 1.5f, 0.f, 0.f );
				Ind1Char2Node_->setPosition( -charWidth * .5f, 0.f, 0.f );
				Ind1Char3Node_->setPosition( charWidth * .5f, 0.f, 0.f );
				Ind1Char4Node_->setPosition( charWidth * 1.5f, 0.f, 0.f );
			}
			else if ( moisture < 10 )
			{
				Ind1Char3_->SetIndex( p1 );

				Ind1Char1Node_->setVisible( false );
				Ind1Char2Node_->setVisible( false );
				Ind1Char3Node_->setVisible( true );
				Ind1Char4Node_->setVisible( true );

				//Ind1Char1Node_->setPosition( -charWidth, 0.f, 0.f );
				Ind1Char3Node_->setPosition( -charWidth * .5f, 0.f, 0.f );
				Ind1Char4Node_->setPosition( charWidth * .5f, 0.f, 0.f );
			}
			else
			{
				Ind1Char2_->SetIndex( p2 );
				Ind1Char3_->SetIndex( p1 );

				Ind1Char1Node_->setVisible( false );
				Ind1Char2Node_->setVisible( true );
				Ind1Char3Node_->setVisible( true );
				Ind1Char4Node_->setVisible( true );

				Ind1Char2Node_->setPosition( -charWidth, 0.f, 0.f );
				Ind1Char3Node_->setPosition( 0.f, 0.f, 0.f );
				Ind1Char4Node_->setPosition( charWidth, 0.f, 0.f );
			}

			Ogre::Quaternion qua;
			qua.FromAngleAxis( Ogre::Degree( moisture * 1.8f ), Ogre::Vector3::NEGATIVE_UNIT_Z );
			Pointer1Node_->setOrientation( qua );
		}


		{
			auto p1 = ( fat ) % 10;
			auto p2 = ( fat / 10 ) % 10;
			auto p3 = ( fat / 100 ) % 10;

			if ( fat == 100 )
			{
				Ind2Char1_->SetIndex( p3 );
				Ind2Char2_->SetIndex( p2 );
				Ind2Char3_->SetIndex( p1 );

				Ind2Char1Node_->setVisible( true );
				Ind2Char2Node_->setVisible( true );
				Ind2Char3Node_->setVisible( true );
				Ind2Char4Node_->setVisible( true );

				Ind2Char1Node_->setPosition( -charWidth * 1.5f, 0.f, 0.f );
				Ind2Char2Node_->setPosition( -charWidth * .5f, 0.f, 0.f );
				Ind2Char3Node_->setPosition( charWidth * .5f, 0.f, 0.f );
				Ind2Char4Node_->setPosition( charWidth * 1.5f, 0.f, 0.f );
			}
			else if ( fat < 10 )
			{
				Ind2Char3_->SetIndex( p1 );

				Ind2Char1Node_->setVisible( false );
				Ind2Char2Node_->setVisible( false );
				Ind2Char3Node_->setVisible( true );
				Ind2Char4Node_->setVisible( true );

				Ind2Char3Node_->setPosition( -charWidth * .5f, 0.f, 0.f );
				Ind2Char4Node_->setPosition( charWidth * .5f, 0.f, 0.f );
			}
			else
			{
				Ind2Char2_->SetIndex( p2 );
				Ind2Char3_->SetIndex( p1 );

				Ind2Char1Node_->setVisible( false );
				Ind2Char2Node_->setVisible( true );
				Ind2Char3Node_->setVisible( true );
				Ind2Char4Node_->setVisible( true );

				Ind2Char2Node_->setPosition( -charWidth, 0.f, 0.f );
				Ind2Char3Node_->setPosition( 0.f, 0.f, 0.f );
				Ind2Char4Node_->setPosition( charWidth, 0.f, 0.f );
			}

			Ogre::Quaternion qua;
			qua.FromAngleAxis( Ogre::Degree( fat * 1.8f ), Ogre::Vector3::NEGATIVE_UNIT_Z );
			Pointer2Node_->setOrientation( qua );
		}


		{
			auto p1 = ( melanin ) % 10;
			auto p2 = ( melanin / 10 ) % 10;
			auto p3 = ( melanin / 100 ) % 10;

			if ( melanin == 100 )
			{
				Ind3Char1_->SetIndex( p3 );
				Ind3Char2_->SetIndex( p2 );
				Ind3Char3_->SetIndex( p1 );

				Ind3Char1Node_->setVisible( true );
				Ind3Char2Node_->setVisible( true );
				Ind3Char3Node_->setVisible( true );
				Ind3Char4Node_->setVisible( true );

				Ind3Char1Node_->setPosition( -charWidth * 1.5f, 0.f, 0.f );
				Ind3Char2Node_->setPosition( -charWidth * .5f, 0.f, 0.f );
				Ind3Char3Node_->setPosition( charWidth * .5f, 0.f, 0.f );
				Ind3Char4Node_->setPosition( charWidth * 1.5f, 0.f, 0.f );
			}
			else if ( melanin < 10 )
			{
				Ind3Char3_->SetIndex( p1 );

				Ind3Char1Node_->setVisible( false );
				Ind3Char2Node_->setVisible( false );
				Ind3Char3Node_->setVisible( true );
				Ind3Char4Node_->setVisible( true );

				Ind3Char3Node_->setPosition( -charWidth * .5f, 0.f, 0.f );
				Ind3Char4Node_->setPosition( charWidth * .5f, 0.f, 0.f );
			}
			else
			{
				Ind3Char2_->SetIndex( p2 );
				Ind3Char3_->SetIndex( p1 );

				Ind3Char1Node_->setVisible( false );
				Ind3Char2Node_->setVisible( true );
				Ind3Char3Node_->setVisible( true );
				Ind3Char4Node_->setVisible( true );

				Ind3Char2Node_->setPosition( -charWidth, 0.f, 0.f );
				Ind3Char3Node_->setPosition( 0.f, 0.f, 0.f );
				Ind3Char4Node_->setPosition( charWidth, 0.f, 0.f );
			}

			Ogre::Quaternion qua;
			qua.FromAngleAxis( Ogre::Degree( melanin * 1.8f ), Ogre::Vector3::NEGATIVE_UNIT_Z );
			Pointer3Node_->setOrientation( qua );
		}
	}
};

DummyController::DummyController( Ogre::RenderWindow *rt ):ImpUPtr_( new Imp )
{
	auto& imp_ = *ImpUPtr_;
	imp_.RT_ = rt;

	imp_.Smgr_ = Ogre::Root::getSingletonPtr()->createSceneManager( Ogre::ST_GENERIC, 1, Ogre::INSTANCING_CULLING_SINGLETHREAD, "DummyScene" );

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

	imp_.WorkSpce_ = comMgr->addWorkspace( imp_.Smgr_, imp_.RT_, camera, "IndicatorWorkspace", true );

	auto cmat = Ogre::MaterialManager::getSingleton().getByName( "Comparison" );
	cmat->load();
	auto ctex = cmat->getTechnique( 0 )->getPass( 0 )->getTextureUnitState( 0 )->_getTexturePtr();

	auto comparisonAreaWidth = ctex->getWidth();
	auto indicatorAreaWidth = sceneWidth - comparisonAreaWidth;

	{//comparison
		auto posNode = imp_.Smgr_->getRootSceneNode()->createChildSceneNode();
		posNode->setPosition( ( sceneWidth / 2 ) - ( comparisonAreaWidth / 2 ), 0.f, 0.f );

		auto rect = RectExtFactory::CreateInstance( imp_.Smgr_ );
		rect->SetMaterial( cmat->getName() );

		auto scaleNode = posNode->createChildSceneNode();
		scaleNode->setScale( ctex->getWidth(), ctex->getHeight(), 1.f );
		scaleNode->attachObject( rect );

		{//sex
			auto sexNode = posNode->createChildSceneNode();
			sexNode->setPosition(0.f, 392.f, 0.f);

			{
				auto sex1Node = sexNode->createChildSceneNode();
				sex1Node->setPosition(-90.f, 0.f, 0.f);
				sex1Node->setScale(90.f, 45.f, 1.f);
				auto sexRect = RectExtFactory::CreateInstance(imp_.Smgr_);
				sexRect->SetMaterial("TexChar");
				sexRect->SetUV(0.f, 2 / 8.f, 0.f, 1.f);
				sex1Node->attachObject(sexRect);
			}

			{
				auto sex2Node = sexNode->createChildSceneNode();
				sex2Node->setPosition(50.f, 0.f, 0.f);
				sex2Node->setScale(45.f, 45.f, 1.f);
				imp_.Sex_ = RectExtFactory::CreateInstance(imp_.Smgr_);
				imp_.Sex_->SetMaterial("TexChar");
				imp_.SetSex(true);
				sex2Node->attachObject(imp_.Sex_);
			}
		}

		{//age
			auto ageNode = posNode->createChildSceneNode();
			ageNode->setPosition(0.f, 342.f, 0.f);

			{//tex
				auto texNode = ageNode->createChildSceneNode();
				texNode->setPosition(-90.f, 0.f, 0.f);
				texNode->setScale(90.f, 45.f, 1.f);
				auto ageRect = RectExtFactory::CreateInstance(imp_.Smgr_);
				ageRect->SetMaterial("TexChar");
				ageRect->SetUV(4 / 8.f, 6 / 8.f, 0.f, 1.f);
				texNode->attachObject(ageRect);
			}

			auto numNode = ageNode->createChildSceneNode();
			numNode->setPosition(50.f, 0.f, 0.f);
			{//num
				imp_.Age1Node_ = numNode->createChildSceneNode();
				imp_.Age1Node_->setScale(40.f, 40.f, 1.f);
				imp_.Age1Node_->setPosition(-60.f, 0.f, 0.f);
				imp_.Age1_ = TexNumberFactory::CreateInstance(imp_.Smgr_);
				imp_.Age1Node_->attachObject(imp_.Age1_);

				auto n2Node = numNode->createChildSceneNode();
				n2Node->setScale(40.f, 40.f, 1.f);
				n2Node->setPosition(-20.f, 0.f, 0.f);
				imp_.Age2_ = TexNumberFactory::CreateInstance(imp_.Smgr_);
				n2Node->attachObject(imp_.Age2_);

				auto n3Node = numNode->createChildSceneNode();
				n3Node->setScale(40.f, 40.f, 1.f);
				n3Node->setPosition(20.f, 0.f, 0.f);
				imp_.Age3_ = TexNumberFactory::CreateInstance(imp_.Smgr_);
				n3Node->attachObject(imp_.Age3_);
			}

			imp_.SetAge(20);
		}

		{//summy

		}
	}

	auto singleIndicatorArea = indicatorAreaWidth / 3;


	{//indicator
		auto indicatorRootNode = imp_.Smgr_->getRootSceneNode()->createChildSceneNode();
		indicatorRootNode->setPosition( ( indicatorAreaWidth / 2 ) - ( sceneWidth / 2 ), 0.f, 0.f );

		auto introdMat = Ogre::MaterialManager::getSingleton().getByName( "Introduction" );
		introdMat->load();
		auto introdTex = introdMat->getTechnique( 0 )->getPass( 0 )->getTextureUnitState( 0 )->_getTexturePtr();

		{//indicator1
			auto ind = indicatorRootNode->createChildSceneNode();
			ind->setPosition( -singleIndicatorArea, 0.f, 0.f );

			{//panel
				auto panelPosNode = ind->createChildSceneNode();
				panelPosNode->setPosition( 0.f, panelOffset, 0.f );

				{
					auto panelMat = Ogre::MaterialManager::getSingleton().getByName( "Panel1" );
					panelMat->load();
					auto panelTex = panelMat->getTechnique( 0 )->getPass( 0 )->getTextureUnitState( 0 )->_getTexturePtr();

					auto panelScaleNode = panelPosNode->createChildSceneNode();
					panelScaleNode->setScale( panelTex->getWidth(), panelTex->getHeight(), 1.f );

					auto panelRect = RectExtFactory::CreateInstance( imp_.Smgr_ );
					panelRect->SetMaterial( panelMat->getName() );
					panelRect->setRenderQueueGroup( ERG_Panel );
					panelScaleNode->attachObject( panelRect );

					auto pointerNode = panelScaleNode->createChildSceneNode();
					auto pointRect = RectExtFactory::CreateInstance( imp_.Smgr_ );
					pointRect->SetMaterial( "PanelPointer" );
					pointRect->setRenderQueueGroup( ERG_Pointer );
					pointerNode->attachObject( pointRect );

					imp_.Pointer1Node_ = pointerNode;
				}

				{
					auto charPosNode = panelPosNode->createChildSceneNode();
					charPosNode->setPosition( 0.f, texOffset, 0.f );

					auto char1Node = charPosNode->createChildSceneNode();
					auto char1 = TexNumberFactory::CreateInstance( imp_.Smgr_ );
					char1->SetIndex( 1 );
					char1->setRenderQueueGroup( ERG_Num );
					char1Node->setScale( charWidth, charHeight, 1.f );
					char1Node->attachObject( char1 );
					char1Node->setPosition( -charWidth, 0.f, 0.f );

					auto char2Node = charPosNode->createChildSceneNode();
					auto char2 = TexNumberFactory::CreateInstance( imp_.Smgr_ );
					char2->SetIndex( 1 );
					char2->setRenderQueueGroup( ERG_Num );
					char2Node->setScale( charWidth, charHeight, 1.f );
					char2Node->attachObject( char2 );

					auto char3Node = charPosNode->createChildSceneNode();
					auto char3 = TexNumberFactory::CreateInstance( imp_.Smgr_ );
					char3->SetIndex( 1 );
					char3->setRenderQueueGroup( ERG_Num );
					char3Node->setScale( charWidth, charHeight, 1.f );
					char3Node->attachObject( char3 );
					char3Node->setPosition( charWidth, 0.f, 0.f );

					auto char4Node = charPosNode->createChildSceneNode();
					auto char4 = TexNumberFactory::CreateInstance( imp_.Smgr_ );
					char4->SetIndex( 10 );
					char4->setRenderQueueGroup( ERG_Num );
					char4Node->setScale( charWidth, charHeight, 1.f );
					char4Node->attachObject( char4 );
					char4Node->setPosition( charWidth, 0.f, 0.f );

					imp_.Ind1Char1Node_ = char1Node;
					imp_.Ind1Char2Node_ = char2Node;
					imp_.Ind1Char3Node_ = char3Node;
					imp_.Ind1Char4Node_ = char4Node;
					imp_.Ind1Char1_ = char1;
					imp_.Ind1Char2_ = char2;
					imp_.Ind1Char3_ = char3;
				}
			}

			{//introduction
				auto introdPosNode = ind->createChildSceneNode();
				introdPosNode->setPosition( 0.f, introductionOffset, 0.f );

				auto introdScaleNode = introdPosNode->createChildSceneNode();
				introdScaleNode->setScale( introdTex->getWidth(), introdTex->getHeight(), 1.f );

				auto introdRect = RectExtFactory::CreateInstance( imp_.Smgr_ );
				introdRect->SetMaterial( introdMat->getName() );
				introdScaleNode->attachObject( introdRect );
			}
		}

		{//indicator2
			auto ind = indicatorRootNode->createChildSceneNode();
			ind->setPosition( 0, 0.f, 0.f );

			{//panel
				auto panelPosNode = ind->createChildSceneNode();
				panelPosNode->setPosition( 0.f, panelOffset, 0.f );

				{
					auto panelMat = Ogre::MaterialManager::getSingleton().getByName( "Panel2" );
					panelMat->load();
					auto panelTex = panelMat->getTechnique( 0 )->getPass( 0 )->getTextureUnitState( 0 )->_getTexturePtr();

					auto panelScaleNode = panelPosNode->createChildSceneNode();
					panelScaleNode->setScale( panelTex->getWidth(), panelTex->getHeight(), 1.f );

					auto panelRect = RectExtFactory::CreateInstance( imp_.Smgr_ );
					panelRect->SetMaterial( panelMat->getName() );
					panelRect->setRenderQueueGroup( ERG_Panel );
					panelScaleNode->attachObject( panelRect );

					auto pointerNode = panelScaleNode->createChildSceneNode();
					auto pointRect = RectExtFactory::CreateInstance( imp_.Smgr_ );
					pointRect->SetMaterial( "PanelPointer" );
					pointRect->setRenderQueueGroup( ERG_Pointer );
					pointerNode->attachObject( pointRect );

					imp_.Pointer2Node_ = pointerNode;
				}

				{
					auto charPosNode = panelPosNode->createChildSceneNode();
					charPosNode->setPosition( 0.f, texOffset, 0.f );

					auto char1Node = charPosNode->createChildSceneNode();
					auto char1 = TexNumberFactory::CreateInstance( imp_.Smgr_ );
					char1->SetIndex( 1 );
					char1->setRenderQueueGroup( ERG_Num );
					char1Node->setScale( charWidth, charHeight, 1.f );
					char1Node->attachObject( char1 );
					char1Node->setPosition( -charWidth, 0.f, 0.f );

					auto char2Node = charPosNode->createChildSceneNode();
					auto char2 = TexNumberFactory::CreateInstance( imp_.Smgr_ );
					char2->SetIndex( 1 );
					char2->setRenderQueueGroup( ERG_Num );
					char2Node->setScale( charWidth, charHeight, 1.f );
					char2Node->attachObject( char2 );

					auto char3Node = charPosNode->createChildSceneNode();
					auto char3 = TexNumberFactory::CreateInstance( imp_.Smgr_ );
					char3->SetIndex( 1 );
					char3->setRenderQueueGroup( ERG_Num );
					char3Node->setScale( charWidth, charHeight, 1.f );
					char3Node->attachObject( char3 );
					char3Node->setPosition( charWidth, 0.f, 0.f );

					auto char4Node = charPosNode->createChildSceneNode();
					auto char4 = TexNumberFactory::CreateInstance( imp_.Smgr_ );
					char4->SetIndex( 10 );
					char4->setRenderQueueGroup( ERG_Num );
					char4Node->setScale( charWidth, charHeight, 1.f );
					char4Node->attachObject( char4 );
					char4Node->setPosition( charWidth, 0.f, 0.f );

					imp_.Ind2Char1Node_ = char1Node;
					imp_.Ind2Char2Node_ = char2Node;
					imp_.Ind2Char3Node_ = char3Node;
					imp_.Ind2Char4Node_ = char4Node;
					imp_.Ind2Char1_ = char1;
					imp_.Ind2Char2_ = char2;
					imp_.Ind2Char3_ = char3;
				}
			}

			{//introduction
				auto introdPosNode = ind->createChildSceneNode();
				introdPosNode->setPosition( 0.f, introductionOffset, 0.f );

				auto introdScaleNode = introdPosNode->createChildSceneNode();
				introdScaleNode->setScale( introdTex->getWidth(), introdTex->getHeight(), 1.f );

				auto introdRect = RectExtFactory::CreateInstance( imp_.Smgr_ );
				introdRect->SetMaterial( introdMat->getName() );
				introdScaleNode->attachObject( introdRect );
			}
		}


		{//indicator3
			auto ind = indicatorRootNode->createChildSceneNode();
			ind->setPosition( singleIndicatorArea, 0.f, 0.f );

			{//panel
				auto panelPosNode = ind->createChildSceneNode();
				panelPosNode->setPosition( 0.f, panelOffset, 0.f );

				{
					auto panelMat = Ogre::MaterialManager::getSingleton().getByName( "Panel3" );
					panelMat->load();
					auto panelTex = panelMat->getTechnique( 0 )->getPass( 0 )->getTextureUnitState( 0 )->_getTexturePtr();

					auto panelScaleNode = panelPosNode->createChildSceneNode();
					panelScaleNode->setScale( panelTex->getWidth(), panelTex->getHeight(), 1.f );

					auto panelRect = RectExtFactory::CreateInstance( imp_.Smgr_ );
					panelRect->SetMaterial( panelMat->getName() );
					panelRect->setRenderQueueGroup( ERG_Panel );
					panelScaleNode->attachObject( panelRect );

					auto pointerNode = panelScaleNode->createChildSceneNode();
					auto pointRect = RectExtFactory::CreateInstance( imp_.Smgr_ );
					pointRect->SetMaterial( "PanelPointer" );
					pointRect->setRenderQueueGroup( ERG_Pointer );
					pointerNode->attachObject( pointRect );

					imp_.Pointer3Node_ = pointerNode;
				}

				{
					auto charPosNode = panelPosNode->createChildSceneNode();
					charPosNode->setPosition( 0.f, texOffset, 0.f );

					auto char1Node = charPosNode->createChildSceneNode();
					auto char1 = TexNumberFactory::CreateInstance( imp_.Smgr_ );
					char1->SetIndex( 1 );
					char1->setRenderQueueGroup( ERG_Num );
					char1Node->setScale( charWidth, charHeight, 1.f );
					char1Node->attachObject( char1 );
					char1Node->setPosition( -charWidth, 0.f, 0.f );

					auto char2Node = charPosNode->createChildSceneNode();
					auto char2 = TexNumberFactory::CreateInstance( imp_.Smgr_ );
					char2->SetIndex( 1 );
					char2->setRenderQueueGroup( ERG_Num );
					char2Node->setScale( charWidth, charHeight, 1.f );
					char2Node->attachObject( char2 );

					auto char3Node = charPosNode->createChildSceneNode();
					auto char3 = TexNumberFactory::CreateInstance( imp_.Smgr_ );
					char3->SetIndex( 1 );
					char3->setRenderQueueGroup( ERG_Num );
					char3Node->setScale( charWidth, charHeight, 1.f );
					char3Node->attachObject( char3 );
					char3Node->setPosition( charWidth, 0.f, 0.f );

					auto char4Node = charPosNode->createChildSceneNode();
					auto char4 = TexNumberFactory::CreateInstance( imp_.Smgr_ );
					char4->SetIndex( 10 );
					char4->setRenderQueueGroup( ERG_Num );
					char4Node->setScale( charWidth, charHeight, 1.f );
					char4Node->attachObject( char4 );
					char4Node->setPosition( charWidth, 0.f, 0.f );

					imp_.Ind3Char1Node_ = char1Node;
					imp_.Ind3Char2Node_ = char2Node;
					imp_.Ind3Char3Node_ = char3Node;
					imp_.Ind3Char4Node_ = char4Node;
					imp_.Ind3Char1_ = char1;
					imp_.Ind3Char2_ = char2;
					imp_.Ind3Char3_ = char3;
				}
			}

			{//introduction
				auto introdPosNode = ind->createChildSceneNode();
				introdPosNode->setPosition( 0.f, introductionOffset, 0.f );

				auto introdScaleNode = introdPosNode->createChildSceneNode();
				introdScaleNode->setScale( introdTex->getWidth(), introdTex->getHeight(), 1.f );

				auto introdRect = RectExtFactory::CreateInstance( imp_.Smgr_ );
				introdRect->SetMaterial( introdMat->getName() );
				introdScaleNode->attachObject( introdRect );
			}
		}
	}

	imp_.UpdateValue( 5, 20, 100 );
}

DummyController::~DummyController()
{
	auto& imp_ = *ImpUPtr_;

	Unload();
	
	auto comMgr = Ogre::Root::getSingletonPtr()->getCompositorManager2();
	comMgr->removeWorkspace( imp_.WorkSpce_ );
	Ogre::Root::getSingletonPtr()->destroySceneManager( imp_.Smgr_ );
}

void DummyController::_FrameStart( const Ogre::FrameEvent& fevt )
{
	auto& imp_ = *ImpUPtr_;

	auto& evtRecorder = GetSysEventRecorder();

	auto evt = PopFrameEvent<IndicatorEvt>();
	if ( evt )
	{
		imp_.UpdateValue( evt->Moisture, evt->Fat, evt->Melanin );
		imp_.SetSex(evt->Male);
		imp_.SetAge(evt->Age_);
	}
}