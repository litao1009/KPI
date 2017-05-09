#include "RectExt.h"

#include "ExtensionUtil.h"

#include "Ogre.h"


RectExt::RectExt(const Ogre::IdType& id, Ogre::ObjectMemoryManager *objectMemoryManager)
	:MovableObject(id, objectMemoryManager, Ogre::RENDER_QUEUE_MAIN)
{
	RO_.vertexData = new Ogre::VertexData();
	RO_.indexData = 0;
	RO_.operationType = Ogre::RenderOperation::OT_TRIANGLE_FAN;
	RO_.useIndexes = false;
	RO_.useGlobalInstancingVertexBufferIsAvailable = false;

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

	RO_.vertexData->vertexCount = vList.size();
	RO_.vertexData->vertexStart = 0;

	auto decl = RO_.vertexData->vertexDeclaration;

	auto posEle = decl->addElement(0, 0, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
	auto uvEle = decl->addElement(0, Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3), Ogre::VET_FLOAT2, Ogre::VES_TEXTURE_COORDINATES);

	auto vbuf = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(decl->getVertexSize(0), RO_.vertexData->vertexCount, Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);
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

	RO_.vertexData->vertexBufferBinding->setBinding(0, vbuf);
	Material_ = Ogre::MaterialManager::getSingleton().getByName("Head");
}

RectExt::~RectExt()
{
	delete RO_.vertexData;
}

const Ogre::String& RectExt::getMovableType(void) const
{
	return RectExtFactory::GetFactoryName();
}

const Ogre::LightList& RectExt::getLights(void) const
{
	return queryLights();
}

void RectExt::getRenderOperation(Ogre::RenderOperation& op)
{
	op = RO_;
}

void RectExt::getWorldTransforms(Ogre::Matrix4* xform) const
{
	*xform = getParentNode()->_getFullTransform();
}

void RectExt::_updateRenderQueue(Ogre::RenderQueue* queue, Ogre::Camera *camera, const Ogre::Camera *lodCamera)
{
	queue->addRenderable(this, mRenderQueueID, mRenderQueuePriority);
}

void RectExt::visitRenderables(Ogre::Renderable::Visitor* visitor, bool debugRenderables /*= false*/)
{
	visitor->visit(this, 0, false);
}

const Ogre::MaterialPtr& RectExt::getMaterial(void) const
{
	return Material_;
}

Ogre::Real RectExt::getSquaredViewDepth(const Ogre::Camera* cam) const
{
	auto diff = ( getParentNode()->_getFullTransform() ).getTrans() - cam->getDerivedPosition();
	return diff.squaredLength();
}

void RectExt::SetSmgr(Ogre::SceneManager* smgr)
{
	Smgr_ = smgr;
}

Ogre::SceneManager* RectExt::GetSmgr() const
{
	return Smgr_;
}

void RectExt::SetMaterial( const std::string &name )
{
	Material_ = Ogre::MaterialManager::getSingleton().getByName(name, "General");
}

void RectExt::Destory()
{
	detachFromParent();

	Smgr_->destroyMovableObject(this);
}

void RectExt::SetUV(float uBeg, float uEnd, float vBeg, float vEnd)
{
	auto uvEle = RO_.vertexData->vertexDeclaration->findElementBySemantic(Ogre::VES_TEXTURE_COORDINATES);

	auto vbuf = RO_.vertexData->vertexBufferBinding->getBuffer(0);

	auto pBuf = reinterpret_cast<uint8_t*>( vbuf->lock(Ogre::HardwareBuffer::HBL_WRITE_ONLY) );

	float* pVal{};
	uvEle->baseVertexPointerToElement(pBuf, &pVal);
	reinterpret_cast<Ogre::Vector2*>( pVal )->x = uBeg;
	reinterpret_cast<Ogre::Vector2*>( pVal )->y = vBeg;

	pBuf += vbuf->getVertexSize();
	uvEle->baseVertexPointerToElement(pBuf, &pVal);
	reinterpret_cast<Ogre::Vector2*>( pVal )->x = uBeg;
	reinterpret_cast<Ogre::Vector2*>( pVal )->y = vEnd;

	pBuf += vbuf->getVertexSize();
	uvEle->baseVertexPointerToElement(pBuf, &pVal);
	reinterpret_cast<Ogre::Vector2*>( pVal )->x = uEnd;
	reinterpret_cast<Ogre::Vector2*>( pVal )->y = vEnd;

	pBuf += vbuf->getVertexSize();
	uvEle->baseVertexPointerToElement(pBuf, &pVal);
	reinterpret_cast<Ogre::Vector2*>( pVal )->x = uEnd;
	reinterpret_cast<Ogre::Vector2*>( pVal )->y = vBeg;

	vbuf->unlock();
}
