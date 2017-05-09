#include "TexNumber.h"

#include "ExtensionUtil.h"

#include "Ogre.h"

class	TexNumber::Imp
{
public:

	Ogre::RenderOperation	RO_;
	Ogre::Real				BoundRadius_{};
	Ogre::AxisAlignedBox	AABB_;
	Ogre::MaterialPtr		Material_;
	Ogre::SceneManager*		Smgr_{};

public:

};


TexNumber::TexNumber(const Ogre::IdType& id, Ogre::ObjectMemoryManager *objectMemoryManager)
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
	imp_.Material_ = Ogre::MaterialManager::getSingleton().getByName("TexNumber");
}

TexNumber::~TexNumber()
{
	auto& imp_ = *ImpUPtr_;

	delete imp_.RO_.vertexData;
}

const Ogre::String& TexNumber::getMovableType(void) const
{
	return TexNumberFactory::GetFactoryName();
}

const Ogre::LightList& TexNumber::getLights(void) const
{
	return queryLights();
}

void TexNumber::getRenderOperation(Ogre::RenderOperation& op)
{
	auto& imp_ = *ImpUPtr_;
	op = imp_.RO_;
}

void TexNumber::getWorldTransforms(Ogre::Matrix4* xform) const
{
	*xform = getParentNode()->_getFullTransform();
}

void TexNumber::_updateRenderQueue(Ogre::RenderQueue* queue, Ogre::Camera *camera, const Ogre::Camera *lodCamera)
{
	queue->addRenderable(this, mRenderQueueID, mRenderQueuePriority);
}

void TexNumber::visitRenderables(Ogre::Renderable::Visitor* visitor, bool debugRenderables /*= false*/)
{
	visitor->visit(this, 0, false);
}

const Ogre::MaterialPtr& TexNumber::getMaterial(void) const
{
	auto& imp_ = *ImpUPtr_;

	return imp_.Material_;
}

Ogre::Real TexNumber::getSquaredViewDepth(const Ogre::Camera* cam) const
{
	auto diff = ( getParentNode()->_getFullTransform() ).getTrans() - cam->getDerivedPosition();
	return diff.squaredLength();
}

void TexNumber::SetSmgr(Ogre::SceneManager* smgr)
{
	auto& imp_ = *ImpUPtr_;

	imp_.Smgr_ = smgr;
}

Ogre::SceneManager* TexNumber::GetSmgr() const
{
	auto& imp_ = *ImpUPtr_;

	return imp_.Smgr_;
}

void TexNumber::Destory()
{
	auto& imp_ = *ImpUPtr_;

	detachFromParent();

	imp_.Smgr_->destroyMovableObject(this);
}

void TexNumber::SetIndex(int index)
{
	auto& imp_ = *ImpUPtr_;

	auto uvBeg = index / 11.f;
	auto uvEnd = ( index + 1 ) / 11.f;

	if ( index < 0 )
	{
		uvBeg = 0.f;
		uvEnd = 0.f;
	}

	auto uvEle = imp_.RO_.vertexData->vertexDeclaration->findElementBySemantic( Ogre::VES_TEXTURE_COORDINATES );

	auto vbuf = imp_.RO_.vertexData->vertexBufferBinding->getBuffer( 0 );

	auto pBuf = reinterpret_cast<uint8_t*>( vbuf->lock( Ogre::HardwareBuffer::HBL_WRITE_ONLY ) );
	
	float* pVal{};
	uvEle->baseVertexPointerToElement( pBuf, &pVal );
	reinterpret_cast<Ogre::Vector2*>( pVal )->x = uvBeg;

	pBuf += vbuf->getVertexSize();
	uvEle->baseVertexPointerToElement( pBuf, &pVal );
	reinterpret_cast<Ogre::Vector2*>( pVal )->x = uvBeg;

	pBuf += vbuf->getVertexSize();
	uvEle->baseVertexPointerToElement( pBuf, &pVal );
	reinterpret_cast<Ogre::Vector2*>( pVal )->x = uvEnd;

	pBuf += vbuf->getVertexSize();
	uvEle->baseVertexPointerToElement( pBuf, &pVal );
	reinterpret_cast<Ogre::Vector2*>( pVal )->x = uvEnd;

	vbuf->unlock();
}
