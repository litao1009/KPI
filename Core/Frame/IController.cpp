#include "IController.h"

#include "OgreEnv.h"
#include "SysEventRecorder.h"
#include "FrameEvent/FrameEvent.h"

#include <vector>
#include <algorithm>
#include <unordered_map>

class	IController::Imp
{
public:

	SysEventRecorder							EventRecorder_;
	std::vector<IControllerSPtr >				ChildList_;
	std::vector<IControllerSPtr >				NewChildList_;
	std::vector<IControllerSPtr >				LazyRemoveChildList_;
	IControllerWPtr								Parent_;
	std::unordered_map<std::string, FrameEvent>	FrameEventQueue_;
	std::vector<FrameEvent>						LazyFrameEventQueue_;
};

IController::IController() :IControllerUPtr_(new Imp)
{

}

IController::~IController()
{
	
}

void IController::AddChild(const IControllerSPtr &child)
{
	auto& imp_ = *IControllerUPtr_;
	child->_SetParent(shared_from_this());
	imp_.NewChildList_.push_back(child);
}

void IController::RemoveChild(const IControllerSPtr &child)
{
	auto& imp_ = *IControllerUPtr_;

	auto itor = std::remove(imp_.ChildList_.begin(), imp_.ChildList_.end(), child);
	imp_.ChildList_.erase(itor, imp_.ChildList_.end());
}

void IController::FrameStart(const Ogre::FrameEvent &fevt)
{
	auto& imp_ = *IControllerUPtr_;

	if ( !imp_.NewChildList_.empty() )
	{
		std::copy(imp_.NewChildList_.begin(), imp_.NewChildList_.end(), std::back_inserter(imp_.ChildList_));
		imp_.NewChildList_.clear();
	}

	if ( !imp_.LazyFrameEventQueue_.empty() )
	{
		for ( auto& curFE : imp_.LazyFrameEventQueue_ )
		{
			HandleFrameEvent(curFE);
		}
		imp_.LazyFrameEventQueue_.clear();
	}

	_FrameStart(fevt);

	for (auto& curChild : imp_.ChildList_)
	{
		curChild->FrameStart(fevt);
	}

	_FrameStartPost(fevt);
}

void IController::FrameQueue(const Ogre::FrameEvent &fevt)
{
	auto& imp_ = *IControllerUPtr_;

	_FrameQueue(fevt);

	for (auto& curChild : imp_.ChildList_)
	{
		curChild->FrameQueue(fevt);
	}

	_FrameQueuePost(fevt);
}

void IController::FrameEnd(const Ogre::FrameEvent &fevt)
{
	auto& imp_ = *IControllerUPtr_;

	_FrameEnd(fevt);

	for (auto& curChild : imp_.ChildList_)
	{
		curChild->FrameEnd(fevt);
	}

	_FrameEndPost(fevt);

	for ( auto& curChild : imp_.LazyRemoveChildList_ )
	{
		auto itor = std::remove(imp_.ChildList_.begin(), imp_.ChildList_.end(), curChild);
		imp_.ChildList_.erase(itor, imp_.ChildList_.end());
	}

	imp_.LazyRemoveChildList_.clear();

	imp_.EventRecorder_.Reset();
	imp_.FrameEventQueue_.clear();
}

void IController::HandleSysEvent(const SSysEvent &evt)
{
	auto& imp_ = *IControllerUPtr_;

	imp_.EventRecorder_.TransferEvent(evt);

	for ( auto& curChild : imp_.ChildList_ )
	{
		curChild->HandleSysEvent(evt);
	}
}

const SysEventRecorder& IController::GetSysEventRecorder() const
{
	auto& imp_ = *IControllerUPtr_;

	return imp_.EventRecorder_;
}

void IController::HandleFrameEvent(const FrameEvent& frameEvent)
{
	auto& imp_ = *IControllerUPtr_;

	imp_.FrameEventQueue_.emplace(frameEvent.GetEventName(), frameEvent);

	for (auto& curChild : imp_.ChildList_)
	{
		curChild->HandleFrameEvent(frameEvent);
	}
}

void IController::HandleFrameEventImmediately(const FrameEvent& frameEvent)
{
	_HandleFrameEventImmediately(frameEvent);
}

void IController::HandleFrameEventLazy(const FrameEvent& frameEvent)
{
	auto& imp_ = *IControllerUPtr_;

	imp_.LazyFrameEventQueue_.push_back(frameEvent);
}

void IController::PostFrameEventToUI(const FrameEvent& frameEvent)
{
	OgreEnv::GetInstance().PostFrameEventToUI(frameEvent);
}

IControllerSPtr IController::GetParent()
{
	auto& imp_ = *IControllerUPtr_;

	return imp_.Parent_.lock();
}

void IController::RemoveLazy()
{
	auto& imp_ = *IControllerUPtr_;

	auto parent = imp_.Parent_.lock();
	if ( parent )
	{
		parent->_RemoveChildLazy(shared_from_this());
	}
}

void IController::RemoveChildrenLazy()
{
	auto& imp_ = *IControllerUPtr_;

	std::copy(imp_.ChildList_.begin(), imp_.ChildList_.end(), std::back_inserter(imp_.LazyRemoveChildList_));
}

void IController::Unload()
{
	auto& imp_ = *IControllerUPtr_;

	imp_.ChildList_.clear();
	imp_.LazyRemoveChildList_.clear();
	imp_.NewChildList_.clear();
}

boost::optional<FrameEvent> IController::_PopFrameEvent(const std::string& frameName)
{
	auto& imp_ = *IControllerUPtr_;

	FrameEvent ret;

	auto itor = imp_.FrameEventQueue_.find(frameName);
	if ( itor != imp_.FrameEventQueue_.end() )
	{
		ret = itor->second;
		imp_.FrameEventQueue_.erase(itor);

		return ret;
	}

	return boost::none;
}

void IController::_SetParent(const IControllerSPtr& parent)
{
	auto& imp_ = *IControllerUPtr_;

	imp_.Parent_ = parent;
}

void IController::_RemoveChildLazy(const IControllerSPtr& child)
{
	auto& imp_ = *IControllerUPtr_;

	imp_.LazyRemoveChildList_.push_back(child);
}
