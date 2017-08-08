#include "IndicatorController.h"

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
static const auto introductionOffset = 70.f;
static const auto resultOffset = -200.f;
static const auto texOffset = -5.f;
static const auto charWidth = 30.f;
static const auto charHeight = 60.f;
static const auto introductionScale = 1.2f;

enum ERenderGroup
{
	ERG_Panel = Ogre::RENDER_QUEUE_MAIN,
	ERG_Pointer,
	ERG_Num
};

class 	IndicatorController::Imp
{
public:

	Ogre::RenderWindow*			RT_{};
	Ogre::SceneManager*			Smgr_{};
	Ogre::CompositorWorkspace*	WorkSpce_{};
	Ogre::Camera*				Camera_{};

	Ogre::SceneNode*			Ind1Node_{};
	Ogre::SceneNode*			Ind2Node_{};
	Ogre::SceneNode*			Ind3Node_{};

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

	TexNumber*					SumNum1_{};
	TexNumber*					SumNum2_{};
	TexNumber*					SumNum3_{};
	TexNumber*					SumNum4_{};
	TexNumber*					SumNum5_{};

	Ogre::SceneNode*			ResultNode_{};

	RectExt*					S_{};
	RectExt*					Y_{};
	RectExt*					H_{};

	TexNumber*					ComN1_{};
	TexNumber*					ComN2_{};
	TexNumber*					ComN3_{};

	Ogre::SceneNode*			SexNode_{};
	Ogre::SceneNode*			AgeNode_{};

public:

	void	SetSex(bool male)
	{
		if ( male )
		{
			Sex_->SetUV(2 / 10.f, 3 / 10.f, 0.f, 1.f);
		}
		else
		{
			Sex_->SetUV(3 / 10.f, 4 / 10.f, 0.f, 1.f);
		}
	}

	void	SetAge(int age)
	{
		auto a1 = age % 10;
		auto a2 = ( age / 10 ) % 10;
		auto a3 = ( age / 100 ) % 10;

		Age1_->SetIndex(a3 == 0 ? -1 : a3);
		
		if ( a2 == 0 )
		{
			Age2_->SetIndex( a3 == 0 ? -1 : a2 );
		}
		else
		{
			Age2_->SetIndex( a2 );
		}
		
		Age3_->SetIndex(a1);

		if ( age < 10 )
		{
			SumNum1_->SetIndex(-1);
			SumNum2_->SetIndex(0);
			SumNum3_->SetIndex(-1);
			SumNum4_->SetIndex(-1);
			SumNum5_->SetIndex(9);
		}
		else if ( age < 20 )
		{
			SumNum1_->SetIndex(1);
			SumNum2_->SetIndex(0);
			SumNum3_->SetIndex(-1);
			SumNum4_->SetIndex(1);
			SumNum5_->SetIndex(9);
		}
		else if ( age < 30 )
		{
			SumNum1_->SetIndex(2);
			SumNum2_->SetIndex(0);
			SumNum3_->SetIndex(-1);
			SumNum4_->SetIndex(2);
			SumNum5_->SetIndex(9);
		}
		else if ( age < 40 )
		{
			SumNum1_->SetIndex(3);
			SumNum2_->SetIndex(0);
			SumNum3_->SetIndex(-1);
			SumNum4_->SetIndex(3);
			SumNum5_->SetIndex(9);
		}
		else if ( age < 50 )
		{
			SumNum1_->SetIndex(4);
			SumNum2_->SetIndex(0);
			SumNum3_->SetIndex(-1);
			SumNum4_->SetIndex(4);
			SumNum5_->SetIndex(9);
		}
		else if ( age < 60 )
		{
			SumNum1_->SetIndex(5);
			SumNum2_->SetIndex(0);
			SumNum3_->SetIndex(-1);
			SumNum4_->SetIndex(5);
			SumNum5_->SetIndex(9);
		}
		else if ( age < 70 )
		{
			SumNum1_->SetIndex(6);
			SumNum2_->SetIndex(0);
			SumNum3_->SetIndex(-1);
			SumNum4_->SetIndex(6);
			SumNum5_->SetIndex(9);
		}
		else if ( age < 80 )
		{
			SumNum1_->SetIndex(7);
			SumNum2_->SetIndex(0);
			SumNum3_->SetIndex(-1);
			SumNum4_->SetIndex(7);
			SumNum5_->SetIndex(9);
		}
		else if ( age < 90 )
		{
			SumNum1_->SetIndex(8);
			SumNum2_->SetIndex(0);
			SumNum3_->SetIndex(-1);
			SumNum4_->SetIndex(8);
			SumNum5_->SetIndex(9);
		}
		else
		{
			SumNum1_->SetIndex(9);
			SumNum2_->SetIndex(0);
			SumNum3_->SetIndex(1);
			SumNum4_->SetIndex(0);
			SumNum5_->SetIndex(0);
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

			if ( moisture < 30 )
			{
				S_->SetMaterial( "S1" );
			}
			else if ( moisture <= 55 )
			{
				S_->SetMaterial( "S2" );
			}
			else
			{
				S_->SetMaterial( "S3" );
			}
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

			if ( fat < 50 )
			{
				Y_->SetMaterial( "Y2" );
			}
			else
			{
				Y_->SetMaterial( "Y3" );
			}
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

			if ( melanin <= 9 )
			{
				H_->SetMaterial( "H1" );
			}
			else if ( melanin <= 14 )
			{
				H_->SetMaterial( "H2" );
			}
			else if ( melanin <= 22 )
			{
				H_->SetMaterial( "H3" );
			}
			else if ( melanin <= 30 )
			{
				H_->SetMaterial( "H4" );
			}
			else if ( melanin <= 40 )
			{
				H_->SetMaterial( "H5" );
			}
			else
			{
				H_->SetMaterial( "H6" );
			}
		}
		
		{
			auto compVal = moisture - .2f * fat - .1f * melanin;
			compVal = std::max( compVal, 0.f );
			compVal = std::min( compVal, 100.f );
			auto comValInt = static_cast<int>( compVal );

			auto p1 = ( comValInt ) % 10;
			auto p2 = ( comValInt / 10 ) % 10;
			auto p3 = ( comValInt / 100 ) % 10;

			if ( comValInt == 100 )
			{
				ComN1_->SetIndex( 1 );
				ComN2_->SetIndex( 0 );
				ComN3_->SetIndex( 0 );
			}
			else if ( comValInt < 10 )
			{
				ComN1_->SetIndex( -1 );
				ComN2_->SetIndex( -1 );
				ComN3_->SetIndex( p1 );
			}
			else
			{
				ComN1_->SetIndex( -1 );
				ComN2_->SetIndex( p2 );
				ComN3_->SetIndex( p1 );
			}
		}
		

		ResultNode_->setVisible( true );
		SexNode_->setVisible( false );
		AgeNode_->setVisible( false );
	}
};

IndicatorController::IndicatorController( Ogre::RenderWindow *rt ):ImpUPtr_( new Imp )
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
		imp_.ResultNode_ = imp_.Smgr_->getRootSceneNode()->createChildSceneNode();
		imp_.ResultNode_->setPosition( ( sceneWidth / 2 ) - ( comparisonAreaWidth / 2 ), 0.f, 0.f );

		auto rect = RectExtFactory::CreateInstance( imp_.Smgr_ );
		rect->SetMaterial( cmat->getName() );

		auto scaleNode = imp_.ResultNode_->createChildSceneNode();
		scaleNode->setScale( ctex->getWidth(), ctex->getHeight(), 1.f );
		scaleNode->attachObject( rect );

		{//sex
			imp_.SexNode_ = imp_.ResultNode_->createChildSceneNode();
			imp_.SexNode_->setPosition( 0.f, 392.f, 0.f );

			{
				auto sex1Node = imp_.SexNode_->createChildSceneNode();
				sex1Node->setPosition(-90.f, 0.f, 0.f);
				sex1Node->setScale(90.f, 45.f, 1.f);
				auto sexRect = RectExtFactory::CreateInstance(imp_.Smgr_);
				sexRect->SetMaterial("TexChar");
				sexRect->SetUV(0.f, 2 / 10.f, 0.f, 1.f);
				sex1Node->attachObject(sexRect);
			}

			{
				auto sex2Node = imp_.SexNode_->createChildSceneNode();
				sex2Node->setPosition(50.f, 0.f, 0.f);
				sex2Node->setScale(45.f, 45.f, 1.f);
				imp_.Sex_ = RectExtFactory::CreateInstance(imp_.Smgr_);
				imp_.Sex_->SetMaterial("TexChar");
				imp_.SetSex(true);
				sex2Node->attachObject(imp_.Sex_);
			}
		}

		{//age
			imp_.AgeNode_ = imp_.ResultNode_->createChildSceneNode();
			imp_.AgeNode_->setPosition( 0.f, 342.f, 0.f );

			{//tex
				auto texNode = imp_.AgeNode_->createChildSceneNode();
				texNode->setPosition(-90.f, 0.f, 0.f);
				texNode->setScale(90.f, 45.f, 1.f);
				auto ageRect = RectExtFactory::CreateInstance(imp_.Smgr_);
				ageRect->SetMaterial("TexChar");
				ageRect->SetUV(5 / 10.f, 7 / 10.f, 0.f, 1.f);
				texNode->attachObject(ageRect);
			}

			auto numNode = imp_.AgeNode_->createChildSceneNode();
			numNode->setPosition(50.f, 0.f, 0.f);
			{//num
				auto n1Node = numNode->createChildSceneNode();
				n1Node->setScale(40.f, 40.f, 1.f);
				n1Node->setPosition(-60.f, 0.f, 0.f);
				imp_.Age1_ = TexNumberFactory::CreateInstance(imp_.Smgr_);
				n1Node->attachObject(imp_.Age1_);

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
		}

		{//nr
			imp_.ComN3_ = TexNumberFactory::CreateInstance( imp_.Smgr_ );
			imp_.ComN3_->SetIndex( 1 );
			auto n1Node = imp_.ResultNode_->createChildSceneNode();
			n1Node->setPosition( 0.f, -20.f, 0.f );
			n1Node->setScale( 35.f, 55.f, 1.f );
			n1Node->attachObject( imp_.ComN3_ );

			imp_.ComN2_ = TexNumberFactory::CreateInstance( imp_.Smgr_ );
			imp_.ComN2_->SetIndex( 2 );
			auto n2Node = imp_.ResultNode_->createChildSceneNode();
			n2Node->setPosition( -35.f, -20.f, 0.f );
			n2Node->setScale( 35.f, 55.f, 1.f );
			n2Node->attachObject( imp_.ComN2_ );

			imp_.ComN1_ = TexNumberFactory::CreateInstance( imp_.Smgr_ );
			imp_.ComN1_->SetIndex( 1 );
			auto n3Node = imp_.ResultNode_->createChildSceneNode();
			n3Node->setPosition( -70.f, -20.f, 0.f );
			n3Node->setScale( 35.f, 55.f, 1.f );
			n3Node->attachObject( imp_.ComN1_ );
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
			imp_.Ind1Node_ = indicatorRootNode->createChildSceneNode();
			imp_.Ind1Node_->setPosition( -singleIndicatorArea, 0.f, 0.f );

			{//panel
				auto panelPosNode = imp_.Ind1Node_->createChildSceneNode();
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
				auto introdNode = imp_.Ind1Node_->createChildSceneNode();
				introdNode->setPosition( 0.f, introductionOffset, 0.f );

				auto tex = Ogre::TextureManager::getSingleton().load( "s.png", "General" );

				auto introidScaleNode = introdNode->createChildSceneNode();
				introidScaleNode->setScale( tex->getWidth() * introductionScale, tex->getHeight()* introductionScale, 1.f );

				auto introd = RectExtFactory::CreateInstance( imp_.Smgr_ );
				introd->SetMaterial( "S" );
				introidScaleNode->attachObject( introd );

				auto resultNode = imp_.Ind1Node_->createChildSceneNode();
				resultNode->setPosition( 0.f, resultOffset, 0.f );

				auto reslutScaleNode = resultNode->createChildSceneNode();
				reslutScaleNode->setScale( introdTex->getWidth(), introdTex->getHeight(), 1.f );

				imp_.S_ = RectExtFactory::CreateInstance( imp_.Smgr_ );
				imp_.S_->SetMaterial( introdMat->getName() );
				reslutScaleNode->attachObject( imp_.S_ );
			}
		}

		{//indicator2
			imp_.Ind2Node_ = indicatorRootNode->createChildSceneNode();
			imp_.Ind2Node_->setPosition( 0, 0.f, 0.f );

			{//panel
				auto panelPosNode = imp_.Ind2Node_->createChildSceneNode();
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
				auto introdNode = imp_.Ind2Node_->createChildSceneNode();
				introdNode->setPosition( 0.f, introductionOffset, 0.f );

				auto tex = Ogre::TextureManager::getSingleton().load( "y.png", "General" );

				auto introidScaleNode = introdNode->createChildSceneNode();
				introidScaleNode->setScale( tex->getWidth() * introductionScale, tex->getHeight()* introductionScale, 1.f );

				auto introd = RectExtFactory::CreateInstance( imp_.Smgr_ );
				introd->SetMaterial( "Y" );
				introidScaleNode->attachObject( introd );


				auto resultNode = imp_.Ind2Node_->createChildSceneNode();
				resultNode->setPosition( 0.f, resultOffset, 0.f );

				auto reslutScaleNode = resultNode->createChildSceneNode();
				reslutScaleNode->setScale( introdTex->getWidth(), introdTex->getHeight(), 1.f );

				imp_.Y_ = RectExtFactory::CreateInstance( imp_.Smgr_ );
				imp_.Y_->SetMaterial( introdMat->getName() );
				reslutScaleNode->attachObject( imp_.Y_ );
			}
		}


		{//indicator3
			imp_.Ind3Node_ = indicatorRootNode->createChildSceneNode();
			imp_.Ind3Node_->setPosition( singleIndicatorArea, 0.f, 0.f );

			{//panel
				auto panelPosNode = imp_.Ind3Node_->createChildSceneNode();
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
				auto introdNode = imp_.Ind3Node_->createChildSceneNode();
				introdNode->setPosition( 0.f, introductionOffset, 0.f );

				auto tex = Ogre::TextureManager::getSingleton().load( "h.png", "General" );

				auto introidScaleNode = introdNode->createChildSceneNode();
				introidScaleNode->setScale( tex->getWidth() * introductionScale, tex->getHeight()* introductionScale, 1.f );

				auto introd = RectExtFactory::CreateInstance( imp_.Smgr_ );
				introd->SetMaterial( "H" );
				introidScaleNode->attachObject( introd );


				auto resultNode = imp_.Ind3Node_->createChildSceneNode();
				resultNode->setPosition( 0.f, resultOffset, 0.f );

				auto reslutScaleNode = resultNode->createChildSceneNode();
				reslutScaleNode->setScale( introdTex->getWidth(), introdTex->getHeight(), 1.f );

				imp_.H_ = RectExtFactory::CreateInstance( imp_.Smgr_ );
				imp_.H_->SetMaterial( introdMat->getName() );
				reslutScaleNode->attachObject( imp_.H_ );
			}
		}
	}

	//imp_.SetAge( 0 );
	imp_.UpdateValue( 0, 0, 0 );
	imp_.ResultNode_->setVisible( false );
	imp_.S_->SetMaterial( "Introduction" );
	imp_.Y_->SetMaterial( "Introduction" );
	imp_.H_->SetMaterial( "Introduction" );
}

IndicatorController::~IndicatorController()
{
	auto& imp_ = *ImpUPtr_;

	Unload();
	
	auto comMgr = Ogre::Root::getSingletonPtr()->getCompositorManager2();
	comMgr->removeWorkspace( imp_.WorkSpce_ );
	Ogre::Root::getSingletonPtr()->destroySceneManager( imp_.Smgr_ );
}

void IndicatorController::_FrameStart( const Ogre::FrameEvent& fevt )
{
	auto& imp_ = *ImpUPtr_;

	auto& evtRecorder = GetSysEventRecorder();

	{
		auto evt = PopFrameEvent<IndicatorEvt>();
		if ( evt )
		{
			switch ( evt->DisplayType )
			{
			case 0:
			{
				imp_.Ind1Node_->setVisible( true );
				imp_.Ind2Node_->setVisible( true );
				imp_.Ind3Node_->setVisible( true );
			}
			break;
			case 1:
			{
				imp_.Ind1Node_->setVisible( true );
				imp_.Ind2Node_->setVisible( false );
				imp_.Ind3Node_->setVisible( false );
			}
			break;
			case 2:
			{
				imp_.Ind1Node_->setVisible( false );
				imp_.Ind2Node_->setVisible( true );
				imp_.Ind3Node_->setVisible( false );
			}
			break;
			case 3:
			{
				imp_.Ind1Node_->setVisible( false );
				imp_.Ind2Node_->setVisible( false );
				imp_.Ind3Node_->setVisible( true );
			}
			break;
			default:
			break;
			}

			imp_.UpdateValue( evt->Moisture, evt->Fat, evt->Melanin );
			imp_.SetSex( evt->Male );
			//imp_.SetAge( evt->Age );
			
			switch ( evt->DisplayType )
			{
			case 0:
			{
				//imp_.Ind1Node_->setVisible( true );
				//imp_.Ind2Node_->setVisible( true );
				//imp_.Ind3Node_->setVisible( true );
			}
			break;
			case 1:
			{
				//imp_.Ind1Node_->setVisible( true );
				imp_.Ind2Node_->setVisible( false );
				imp_.Ind3Node_->setVisible( false );
			}
			break;
			case 2:
			{
				imp_.Ind1Node_->setVisible( false );
				//imp_.Ind2Node_->setVisible( true );
				imp_.Ind3Node_->setVisible( false );
			}
			break;
			case 3:
			{
				imp_.Ind1Node_->setVisible( false );
				imp_.Ind2Node_->setVisible( false );
				//imp_.Ind3Node_->setVisible( true );
			}
			break;
			default:
			break;
			}
		}
	}

	{
		auto evt = PopFrameEvent<ClearEvt>();
		if ( evt )
		{
			//imp_.SetAge( 0 );
			imp_.UpdateValue( 0, 0, 0 );
			imp_.ResultNode_->setVisible( false );
			imp_.S_->SetMaterial( "Introduction" );
			imp_.Y_->SetMaterial( "Introduction" );
			imp_.H_->SetMaterial( "Introduction" );
		}
	}
}