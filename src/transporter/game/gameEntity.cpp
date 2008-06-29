#include "transporter.h"

GameEntity::GameEntity( VisualSystem* visual )
{
	this->visualEntity = NULL;
	this->visualSystem = visual;
}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

Ogre::Entity* GameEntity::getVisualEntity()
{
	return this->visualEntity; 
}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

VisualSystem* GameEntity::getVisualSystem()
{
	return this->visualSystem;
}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

bit GameEntity::init(str name)
{
	return true;
}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

GameEntity::~GameEntity()
{
	if(visualEntity)
	{		
		if(visualEntity->getParentSceneNode())
		{
			visualEntity->getParentSceneNode()->detachObject(visualEntity);
		}
		delete visualEntity;
		visualEntity = NULL;
	}
}