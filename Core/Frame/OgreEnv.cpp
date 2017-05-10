#include "OgreEnv.h"
#include "SysEventRecorder.h"
#include "SysEvent.h"
#include "OgreWndWrapper.h"
#include "IController.h"

#include "FrameEvent/FrameEvent.h"
#include "Extension/ExtensionUtil.h"

#include "OgreGLPlugin.h"
#include "Ogre.h"

#include "OgreOverlaySystem.h"

#include <vector>
#include <mutex>

class	OgreEnv::Imp : public Ogre::FrameListener
{
public:

	std::vector<IControllerSPtr>	ChildList_;
	std::vector<std::unique_ptr<Ogre::Plugin>>		Plugins_;
	Ogre::RenderWindow*				ContextWnd_{};
	HGLRC							Context_{};
	FrameEventResponser				UIResponser_;
	std::vector<FrameEvent>			FrameEventList_;
	std::mutex						FrameEventMutex_;
	std::unique_ptr<Ogre::OverlaySystem>	OverlaySys_;

public:

	virtual bool frameStarted(const Ogre::FrameEvent& evt) override
	{
		decltype( FrameEventList_ ) tmpList;
		{
			std::unique_lock<std::mutex> lock(FrameEventMutex_);
			tmpList.swap(FrameEventList_);
		}

		for ( auto& curChild : ChildList_ )
		{
			for ( auto& curFE : tmpList )
			{
				curChild->HandleFrameEvent(curFE);
			}
		}

		for (auto& curChild : ChildList_)
		{
			curChild->FrameStart(evt);
		}

		return true;
	}

	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt) override
	{
		for (auto& curChild : ChildList_)
		{
			curChild->FrameQueue(evt);
		}

		return true;
	}

	virtual bool frameEnded(const Ogre::FrameEvent& evt) override
	{
		for (auto& curChild : ChildList_)
		{
			curChild->FrameEnd(evt);
		}

		return true;
	}
};

OgreEnv::OgreEnv():ImpUPtr_(new Imp)
{ }

OgreEnv::~OgreEnv()
{ }

OgreEnv& OgreEnv::GetInstance()
{
	static OgreEnv sins;
	return  sins;
}

void OgreEnv::Init()
{
	auto& imp_ = *ImpUPtr_;

	auto root = new Ogre::Root("", "");
	
	imp_.Plugins_.emplace_back(std::make_unique<Ogre::GLPlugin>());

	for (auto& curPlugin : imp_.Plugins_ )
	{
		root->installPlugin(curPlugin.get());
	}

	root->addFrameListener(ImpUPtr_.get());

	root->setRenderSystem(root->getAvailableRenderers().front());
	root->initialise(false);

	imp_.OverlaySys_ = std::make_unique<Ogre::OverlaySystem>();

#ifdef _DEBUG
	Ogre::ConfigFile cfg;
	{
		std::ifstream ifs( "Data/resources.cfg", std::ios::binary );
		Ogre::DataStreamPtr srcData( new Ogre::FileStreamDataStream( &ifs, false ) );
		cfg.load( srcData );
	}

	auto sectionItor = cfg.getSectionIterator();
	for ( auto& curSec : sectionItor )
	{
		auto sec = curSec.first;
		for ( auto& curSet : *( curSec.second ) )
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation( curSet.second, curSet.first, sec );
		}
	}
#else
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation( "res.db", "Zip", "General" );
#endif

	Ogre::NameValuePairList params;
	params.emplace("title", "ContextWnd");
	params.emplace("hidden", "true");
	params.emplace("FSAA", std::to_string(4));

	imp_.ContextWnd_ = Ogre::Root::getSingletonPtr()->createRenderWindow("contextWnd", 16, 16, false, &params);
	imp_.Context_ = wglGetCurrentContext();

	Ogre::ResourceGroupManager::getSingletonPtr()->initialiseAllResourceGroups();

	ExtensionUtil::GetInstance().Init();
}

void OgreEnv::UnInit()
{
	auto& imp_ = *ImpUPtr_;

	imp_.ChildList_.clear();

	imp_.OverlaySys_.reset();

	delete Ogre::Root::getSingletonPtr();

	ExtensionUtil::GetInstance().UnInit();

	imp_.Plugins_.clear();
}

void OgreEnv::RenderOneFrame()
{
	static auto s_LastTime = 0U;

	auto& root = *Ogre::Root::getSingletonPtr();

	auto curTime = root.getTimer()->getMicroseconds();
	auto frameTime = curTime - s_LastTime;
	auto limitFPS = 10;
	auto limitFrameTime = 1E6 / static_cast<float >(limitFPS);

	if ( frameTime < limitFrameTime )
	{
		return;
	}

	s_LastTime = curTime;

	root.renderOneFrame();
}

Ogre::OverlaySystem* OgreEnv::GetOverlaySystem() const
{
	auto& imp_ = *ImpUPtr_;

	return imp_.OverlaySys_.get();
}

OgreWndWrapperUPtr OgreEnv::CreateRenderWindow(uint32_t handle, uint32_t width, uint32_t height)
{
	auto& imp_ = *ImpUPtr_;

	Ogre::NameValuePairList params;
	params.emplace("externalWindowHandle", std::to_string(handle));
	params.emplace("externalGLContext", std::to_string(reinterpret_cast<uint32_t>( imp_.Context_ )));
	params.emplace("FSAA", std::to_string(4));

	auto renderWnd = Ogre::Root::getSingletonPtr()->createRenderWindow(std::to_string(handle), width, height, false, &params);

	return std::make_unique<OgreWndWrapper>(renderWnd);
}

void OgreEnv::PostSysEventTo3D(const OgreWndWrapper& wnd, const SSysEvent& evt)
{
	auto& imp_ = *ImpUPtr_;

	if ( evt.EventType == SSysEvent::EET_Mouse )
	{
		if ( evt.MouseEvt.Moved )
		{
			SysEventRecorder::CachedMouseState() = evt.MouseEvt.State;
		}
	}

	for ( auto& curChild : imp_.ChildList_ )
	{
		curChild->HandleSysEvent(evt);
	}
}

void OgreEnv::PostFrameEventTo3D(const OgreWndWrapper& wnd, const FrameEvent& evt)
{
	auto& imp_ = *ImpUPtr_;

	{
		std::unique_lock<std::mutex> lock(imp_.FrameEventMutex_);
		imp_.FrameEventList_.push_back(evt);
	}
}

void OgreEnv::PostFrameEventTo3D(const FrameEvent& evt)
{
	auto& imp_ = *ImpUPtr_;

	{
		std::unique_lock<std::mutex> lock(imp_.FrameEventMutex_);
		imp_.FrameEventList_.push_back(evt);
	}
}

void OgreEnv::PostFrameEventToUI(const FrameEvent& evt)
{
	auto& imp_ = *ImpUPtr_;

	if ( imp_.UIResponser_ )
	{
		imp_.UIResponser_(evt);
	}
}

void OgreEnv::SetUIFrameEventResponser(const FrameEventResponser& responser)
{
	auto& imp_ = *ImpUPtr_;

	imp_.UIResponser_ = responser;
}

void OgreEnv::AddController( const IControllerSPtr &frameListener )
{
	auto& imp_ = *ImpUPtr_;

	imp_.ChildList_.push_back(frameListener);
}

void OgreEnv::RemoveController(const IControllerSPtr &frameListener)
{
	auto& imp_ = *ImpUPtr_;

	auto itor = std::remove(imp_.ChildList_.begin(), imp_.ChildList_.end(), frameListener);
	imp_.ChildList_.erase(itor, imp_.ChildList_.end());
}

void OgreEnv::RemoveAllController()
{
	auto& imp_ = *ImpUPtr_;

	imp_.ChildList_.clear();
}
