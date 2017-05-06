#include "TextAreaExt.h"

#include "ExtensionUtil.h"

#include "Ogre.h"
#include "OgreFont.h"



class	CharInfo
{
public:

	wchar_t				Ch{};
	float				AspectRadio{};
	Ogre::Font::UVRect	UV{};
};

class	TextAreaExt::Imp
{
public:

	Ogre::RenderOperation	RO_;
	Ogre::Real				BoundRadius_{};
	Ogre::AxisAlignedBox	AABB_;
	Ogre::MaterialPtr		Material_;
	Ogre::SceneManager*		Smgr_{};
	Ogre::Font*				Font_{};

	std::wstring			Content_;

	float					CharHeight_{ 1.f };
	float					AeraWidth_{ 10.f };
	float					BorderWidth_{ .2f };
	float					BorderHeight_{ .2f };
	float					LineSpaceing_{ .5f };
	float					CharSpaceing_{ .1f };
	float					SpaceWidth_{ .5f };

public:

	void	UpdateContent()
	{
		if ( !Font_->isLoaded() )
		{
			Font_->load();
		}

		std::vector<std::wstring> lineList;
		lineList.emplace_back();
		auto curLineWidth = 0.f;
		for ( auto& curChar : Content_ )
		{
			auto curCharWidth = 0.f;
			{
				if ( curChar == ' ' )
				{
					curCharWidth = SpaceWidth_;
				}
				else if ( curChar == '\n' )
				{

				}
			}
			
		}

	}
};


TextAreaExt::TextAreaExt(const Ogre::IdType& id, Ogre::ObjectMemoryManager *objectMemoryManager)
	:MovableObject(id, objectMemoryManager, Ogre::RENDER_QUEUE_MAIN), ImpUPtr_(std::make_unique<Imp>())
{
	auto& imp_ = *ImpUPtr_;

	imp_.RO_.vertexData = new Ogre::VertexData();
	imp_.RO_.indexData = 0;
	imp_.RO_.operationType = Ogre::RenderOperation::OT_TRIANGLE_FAN;
	imp_.RO_.useIndexes = false;
	imp_.RO_.useGlobalInstancingVertexBufferIsAvailable = false;

	std::vector<Ogre::Vector3> vList;
	{
		auto halfSize = .5f;
		vList.emplace_back(-halfSize, halfSize, 0.f);
		vList.emplace_back(-halfSize, -halfSize, 0.f);
		vList.emplace_back(halfSize, -halfSize, 0.f);
		vList.emplace_back(halfSize, halfSize, 0.f);
	}

	std::vector<Ogre::Vector2> uvList;
	{
		uvList.emplace_back(0.f, 0.f);
		uvList.emplace_back(0.f, 1.f);
		uvList.emplace_back(1.f, 1.f);
		uvList.emplace_back(1.f, 0.f);
	}

	imp_.RO_.vertexData->vertexCount = vList.size();
	imp_.RO_.vertexData->vertexStart = 0;

	auto decl = imp_.RO_.vertexData->vertexDeclaration;

	auto posEle = decl->addElement(0, 0, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
	auto uvEle = decl->addElement(0, Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3), Ogre::VET_FLOAT2, Ogre::VES_TEXTURE_COORDINATES);

	auto vbuf = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(decl->getVertexSize(0), imp_.RO_.vertexData->vertexCount, Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);
	{
		auto* pBuf = static_cast<uint8_t *>( vbuf->lock(Ogre::HardwareBuffer::HBL_DISCARD) );
		float* pVal{};
		for ( auto curIndex=0U; curIndex<vList.size(); ++curIndex )
		{
			posEle.baseVertexPointerToElement(pBuf, &pVal);
			*reinterpret_cast<Ogre::Vector3*>(pVal) = vList[curIndex];

			uvEle.baseVertexPointerToElement(pBuf, &pVal);
			*reinterpret_cast<Ogre::Vector2*>(pVal) = uvList[curIndex];

			pBuf += vbuf->getVertexSize();
		}

		vbuf->unlock();
	}

	imp_.RO_.vertexData->vertexBufferBinding->setBinding(0, vbuf);
	imp_.Material_ = Ogre::MaterialManager::getSingleton().getByName("Head");
}

TextAreaExt::~TextAreaExt()
{
	auto& imp_ = *ImpUPtr_;

	delete imp_.RO_.vertexData;
}

const Ogre::String& TextAreaExt::getMovableType(void) const
{
	return TextAreaExtFactory::GetFactoryName();
}

const Ogre::LightList& TextAreaExt::getLights(void) const
{
	return queryLights();
}

void TextAreaExt::getRenderOperation(Ogre::RenderOperation& op)
{
	auto& imp_ = *ImpUPtr_;
	op = imp_.RO_;
}

void TextAreaExt::getWorldTransforms(Ogre::Matrix4* xform) const
{
	*xform = getParentNode()->_getFullTransform();
}

void TextAreaExt::_updateRenderQueue(Ogre::RenderQueue* queue, Ogre::Camera *camera, const Ogre::Camera *lodCamera)
{
	queue->addRenderable(this, mRenderQueueID, mRenderQueuePriority);
}

void TextAreaExt::visitRenderables(Ogre::Renderable::Visitor* visitor, bool debugRenderables /*= false*/)
{
	visitor->visit(this, 0, false);
}

const Ogre::MaterialPtr& TextAreaExt::getMaterial(void) const
{
	auto& imp_ = *ImpUPtr_;

	return imp_.Material_;
}

Ogre::Real TextAreaExt::getSquaredViewDepth(const Ogre::Camera* cam) const
{
	auto diff = ( getParentNode()->_getFullTransform() ).getTrans() - cam->getDerivedPosition();
	return diff.squaredLength();
}

void TextAreaExt::SetSmgr(Ogre::SceneManager* smgr)
{
	auto& imp_ = *ImpUPtr_;

	imp_.Smgr_ = smgr;
}

Ogre::SceneManager* TextAreaExt::GetSmgr() const
{
	auto& imp_ = *ImpUPtr_;

	return imp_.Smgr_;
}

void TextAreaExt::SetMaterial(const std::string &name)
{
	auto& imp_ = *ImpUPtr_;

	imp_.Material_ = Ogre::MaterialManager::getSingleton().getByName(name, "General");
}

void TextAreaExt::Destory()
{
	auto& imp_ = *ImpUPtr_;

	detachFromParent();

	imp_.Smgr_->destroyMovableObject(this);
}