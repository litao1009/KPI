#include "Line2D.h"

#include "ExtensionUtil.h"

#include "Ogre.h"

static const auto sDefaultWidth = 20.f;

Line2D::Line2D(const Ogre::IdType& id, Ogre::ObjectMemoryManager *objectMemoryManager)
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

	RO_.vertexData->vertexCount = vList.size();
	RO_.vertexData->vertexStart = 0;

	auto decl = RO_.vertexData->vertexDeclaration;

	auto posEle = decl->addElement(0, 0, Ogre::VET_FLOAT3, Ogre::VES_POSITION);

	auto vbuf = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(decl->getVertexSize(0), RO_.vertexData->vertexCount, Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);
	{
		auto* pBuf = static_cast<uint8_t *>( vbuf->lock(Ogre::HardwareBuffer::HBL_DISCARD) );
		float* pVal{};
		for ( auto curIndex = 0U; curIndex < vList.size(); ++curIndex )
		{
			posEle.baseVertexPointerToElement(pBuf, &pVal);
			*reinterpret_cast<Ogre::Vector3*>( pVal ) = vList[curIndex];

			pBuf += vbuf->getVertexSize();

			AABB_.merge(vList[curIndex]);
		}

		vbuf->unlock();
	}

	RO_.vertexData->vertexBufferBinding->setBinding(0, vbuf);

	Material_ = Ogre::MaterialManager::getSingleton().getByName("Chart/Line2D");

	setCustomParameter(0, Ogre::Vector4(Ogre::Vector3::UNIT_SCALE));

	LocalMat_ = Ogre::Matrix4::IDENTITY;

	StartPnt_ = Ogre::Vector3(-.5f, 0.f, 0.f);
	EndPnt_ = Ogre::Vector3(.5f, 0.f, 0.f);

	SetColor(Ogre::ColourValue::White);
	SetLineWidth(sDefaultWidth);
}

Line2D::~Line2D()
{
	delete RO_.vertexData;
}

const Ogre::String& Line2D::getMovableType(void) const
{
	return Line2DFactory::GetFactoryName();
}

const Ogre::LightList& Line2D::getLights(void) const
{
	return queryLights();
}

void Line2D::getRenderOperation(Ogre::RenderOperation& op)
{
	op = RO_;
}

void Line2D::getWorldTransforms(Ogre::Matrix4* xform) const
{	
	*xform = getParentNode()->_getFullTransform() * LocalMat_;
}

void Line2D::_updateRenderQueue(Ogre::RenderQueue* queue, Ogre::Camera *camera, const Ogre::Camera *lodCamera)
{
	queue->addRenderable(this, mRenderQueueID, mRenderQueuePriority);
}

void Line2D::visitRenderables(Renderable::Visitor* visitor, bool debugRenderables /*= false*/)
{
	visitor->visit(this, 0, false);
}

const Ogre::MaterialPtr& Line2D::getMaterial(void) const
{
	return Material_;
}

Ogre::Real Line2D::getSquaredViewDepth(const Ogre::Camera* cam) const
{
	auto diff = (getParentNode()->_getFullTransform() * LocalMat_).getTrans() - cam->getDerivedPosition();
	return diff.squaredLength();
}

const Ogre::UserObjectBindings& Line2D::GetUserObjectBindings() const
{
	return Ogre::MovableObject::getUserObjectBindings();
}

Ogre::UserObjectBindings& Line2D::GetUserObjectBindings()
{
	return Ogre::MovableObject::getUserObjectBindings();
}

void Line2D::SetSmgr(Ogre::SceneManager* smgr)
{
	Smgr_ = smgr;
}

Ogre::SceneManager* Line2D::GetSmgr() const
{
	return Smgr_;
}

void Line2D::Destory()
{
	detachFromParent();

	Smgr_->destroyMovableObject(this);
}

void Line2D::SetColor(const Ogre::ColourValue& val)
{
	Ogre::Vector4 clr;
	clr.x = val.r;
	clr.y = val.g;
	clr.z = val.b;
	clr.w = val.a;
	setCustomParameter(0, clr);
}

Ogre::ColourValue Line2D::GetColor() const
{
	auto val = getCustomParameter(0);
	return Ogre::ColourValue(val.x, val.y, val.z, val.w);
}

void Line2D::SetLineWidth(float val)
{
	Width_ = val;

	SetPoint(StartPnt_, EndPnt_);
}

float Line2D::GetLineWidth() const
{
	return Width_;
}

void Line2D::SetStartPoint(const Ogre::Vector3& pos)
{
	SetPoint(pos, EndPnt_);
}

const Ogre::Vector3& Line2D::GetStartPoint() const
{
	return StartPnt_;
}

void Line2D::SetEndPoint(const Ogre::Vector3& pos)
{
	SetPoint(StartPnt_, pos);
}

const Ogre::Vector3& Line2D::GetEndPoint() const
{
	return EndPnt_;
}

Ogre::Vector3 Line2D::GetCenter() const
{
	return (StartPnt_ + EndPnt_) / 2;
}

void Line2D::SetPoint(const Ogre::Vector3& start, const Ogre::Vector3& end)
{
	StartPnt_ = start;
	EndPnt_ = end;
	LineDir_ = (EndPnt_ - StartPnt_).normalisedCopy();

	auto vec = EndPnt_ - StartPnt_;
	auto norVec = vec;
	norVec.normalise();

	LocalMat_.makeTransform((EndPnt_ + StartPnt_) / 2,
							Ogre::Vector3(vec.length(), Width_, 1.f),
							Ogre::Vector3::UNIT_X.getRotationTo(norVec));

	
	Ogre::Aabb aabb(AABB_.getCenter(), AABB_.getHalfSize());
	aabb.transformAffine(LocalMat_);
	mObjectData.mLocalAabb->setFromAabb(aabb, mObjectData.mIndex);
	mObjectData.mLocalRadius[mObjectData.mIndex] = aabb.getRadius();
}

const Ogre::Vector3& Line2D::GetLineDir() const
{
	return LineDir_;
}

const Ogre::Real	Line2D::GetLength() const
{
	return (EndPnt_ - StartPnt_).length();
}