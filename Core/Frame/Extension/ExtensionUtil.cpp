#include "ExtensionUtil.h"
#include "TExtMovableObjFactory.h"

#include "RectExt.h"
#include "TexNumber.h"
#include "Line2D.h"

#include "Ogre.h"

#include <vector>

class	ExtensionUtil::Imp
{
public:

	using	IExtMovableObjFactoryUPtr = std::unique_ptr<IExtMovableObjFactory>;

public:

	std::vector<IExtMovableObjFactoryUPtr>	FactoryList_;
};

ExtensionUtil& ExtensionUtil::GetInstance()
{
	static ExtensionUtil sIns;
	return sIns;
}

ExtensionUtil::ExtensionUtil() :ImpUPtr_(std::make_unique<Imp>())
{

}

ExtensionUtil::~ExtensionUtil()
{

}

void ExtensionUtil::Init()
{
	auto& imp_ = *ImpUPtr_;

	auto& list = imp_.FactoryList_;
	if ( list.empty() )
	{
		list.emplace_back(std::make_unique<RectExtFactory>());
		list.emplace_back( std::make_unique<TexNumberFactory>() );
		list.emplace_back(std::make_unique<Line2DFactory>());
	}

	for ( auto& cur : list)
	{
		Ogre::Root::getSingletonPtr()->addMovableObjectFactory(cur.get());
		cur->Init();
	}
}

void ExtensionUtil::UnInit()
{
	auto& imp_ = *ImpUPtr_;

	auto& list = imp_.FactoryList_;

	for ( auto& cur : list )
	{
		cur->UnInit();
	}
}