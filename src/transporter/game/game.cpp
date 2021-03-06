#include "transporter.h"

void Game::run()
{
	isRunning = true;
			
	visualSystem.addScene(&gameScene.visualWorld);		
	physicsSystem.run(&gameScene.physicsWorld);	

	inputSystem.start();
	bootScene.showLog(false);
	bootScene.showLoadingScreen(false);
	visualSystem.waitUntilEnd();
}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

bit Game::init(HINSTANCE instance)
{
	this->appInstance = instance;
	bit result = visualSystem.init(this);	
	if(result)
	{
		bootScene.init(this);
		visualSystem.addScene(&bootScene);
		visualSystem.run();	
		
		result &= inputSystem.init(this);
		result &= physicsSystem.init(this);		
		result &= gameScene.init(this);	
		result &= gameScene.physicsWorld.init(this);
		result &= gameScene.visualWorld.init(this);
		gameScene.createEntities();
	}
	return result;
}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

Game::Game()
{
	isRunning = false;
}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

Game::~Game()
{	
	stop();
}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

HINSTANCE Game::getAppInstance()
{
	return appInstance;
}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

void Game::stop()
{
	if(isRunning)
	{
		inputSystem.stop();
		physicsSystem.stop();
		visualSystem.stop();

		gameScene.cleanUp();
		isRunning = false;
	}
}
