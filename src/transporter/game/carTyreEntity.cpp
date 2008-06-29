#include "transporter.h"

CarTyreEntity::CarTyreEntity( VisualSystem* visual )
:GameEntity(visual)
{

}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

CarTyreEntity::~CarTyreEntity()
{

}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

bit CarTyreEntity::init(str name)
{
	visualEntity = visualSystem->getSceneMgr()->createEntity(name,"tyre.mesh");
	visualEntity->setMaterialName("tyreMaterial");
	return true;
}