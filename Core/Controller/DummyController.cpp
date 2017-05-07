#include "DummyController.h"

#include "Frame/OgreEnv.h"

#include "Ogre.h"
#include "Compositor/OgreCompositorManager2.h"
#include "Compositor/OgreCompositorWorkspace.h"
#include "Compositor/OgreCompositorChannel.h"

#include "Frame/Extension/RectExt.h"
#include "Frame/Extension/TexNumber.h"

#include "OgreOverlayManager.h"
#include "OgreOverlay.h"
#include "OgreOverlayContainer.h"
#include "OgreOverlaySystem.h"

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

public:

	void	UpdateValue()
	{

	}
};

DummyController::DummyController(Ogre::RenderWindow *rt) :ImpUPtr_(new Imp)
{
	auto& imp_ = *ImpUPtr_;
	imp_.RT_ = rt;
	
	imp_.Smgr_ = Ogre::Root::getSingletonPtr()->createSceneManager(Ogre::ST_GENERIC, 1, Ogre::INSTANCING_CULLING_SINGLETHREAD, "DummyScene");

	auto sceneHeight = 1024.f;
	auto sceneWidth = 2048.f;

	auto camera = imp_.Smgr_->createCamera("MainCamera");
	camera->setAutoAspectRatio(true);
	camera->setFOVy(Ogre::Degree(60.f));
	camera->setNearClipDistance(5.f);
	camera->setFarClipDistance(5000.f);
	camera->setProjectionType(Ogre::PT_ORTHOGRAPHIC);
	camera->setOrthoWindowHeight( sceneHeight );
	
	auto cameraNode = imp_.Smgr_->getRootSceneNode()->createChildSceneNode();
	camera->detachFromParent();
	cameraNode->attachObject(camera);
	camera->setDirection(Ogre::Vector3::NEGATIVE_UNIT_Z);
	cameraNode->setPosition(Ogre::Vector3(0, 0, 2000));
	imp_.Camera_ = camera;
	
	auto comMgr = Ogre::Root::getSingletonPtr()->getCompositorManager2();

	imp_.WorkSpce_ = comMgr->addWorkspace(imp_.Smgr_, imp_.RT_, camera, "IndicatorWorkspace", true);

	auto indicatorAreaWidth = 1600.f;
	auto comparisonAreaWidth = sceneWidth - indicatorAreaWidth;

	{//comparison
		auto posNode = imp_.Smgr_->getRootSceneNode()->createChildSceneNode();
		posNode->setPosition( ( sceneWidth / 2 ) - ( comparisonAreaWidth / 2 ), 0.f, 0.f );

		auto mat = Ogre::MaterialManager::getSingleton().getByName( "Comparison" );
		mat->load();
		auto tex = mat->getTechnique( 0 )->getPass( 0 )->getTextureUnitState( 0 )->_getTexturePtr();

		auto rect = RectExtFactory::CreateInstance(imp_.Smgr_);
		rect->SetMaterial( mat->getName() );

		auto scaleNode = posNode->createChildSceneNode();
		scaleNode->setScale( tex->getWidth(), tex->getHeight(), 1.f );

		scaleNode->attachObject( rect );
	}

	auto singleIndicatorArea = indicatorAreaWidth / 3;
	auto panelOffset = 264.f;
	auto introductionOffset = -188.f;
	auto texOffset = -45.f;

	{//indicator
		auto indicatorRootNode = imp_.Smgr_->getRootSceneNode()->createChildSceneNode();
		indicatorRootNode->setPosition( ( indicatorAreaWidth / 2 ) - ( sceneWidth / 2 ), 0.f, 0.f );

		auto panelMat = Ogre::MaterialManager::getSingleton().getByName( "Panel" );
		panelMat->load();
		auto panelTex = panelMat->getTechnique( 0 )->getPass( 0 )->getTextureUnitState( 0 )->_getTexturePtr();

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

					Ogre::Quaternion qua;
					qua.FromAngleAxis( Ogre::Degree( 60.f ), Ogre::Vector3::NEGATIVE_UNIT_Z );
					pointerNode->setOrientation( qua );
				}
				
				{
					auto charPosNode = panelPosNode->createChildSceneNode();
					charPosNode->setPosition( 0.f, texOffset, 0.f );

					auto char1Node = charPosNode->createChildSceneNode();
					auto char1 = TexNumberFactory::CreateInstance( imp_.Smgr_ );
					char1->SetIndex( 1 );
					char1->setRenderQueueGroup( ERG_Num );
					char1Node->setScale( 40.f, 80.f, 1.f );
					char1Node->attachObject( char1 );
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
