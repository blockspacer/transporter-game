#include "transporter.h"

static UpdateListenerMgr* volatile updateListenerMgr;

void UpdateListenerMgr::destroyUpdateListenerMgr()
{
	if(updateListenerMgr)
	{
		delete updateListenerMgr;
		updateListenerMgr = NULL;
	}
}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

UpdateListenerMgr::UpdateListenerMgr()
{
	InitializeCriticalSection(&lock);
}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

UpdateListenerMgr::~UpdateListenerMgr()
{
	EnterCriticalSection(&lock);
	listeners.clear();
	LeaveCriticalSection(&lock);
	DeleteCriticalSection(&lock);
}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

UpdateListenerMgr* UpdateListenerMgr::getInstance()
{
	static UpdateListenerMgr* volatile selfPtr;
	if( selfPtr == NULL)
	{
		UpdateListenerMgr* newUpdateListenerMgr = new UpdateListenerMgr;
		LONG value = InterlockedCompareExchange((LONG*)&selfPtr,(LONG)newUpdateListenerMgr,NULL);
		if( value != NULL )
		{
			delete newUpdateListenerMgr;
		}
		else
		{
			updateListenerMgr = selfPtr;
			atexit(destroyUpdateListenerMgr);
		}
	}	
	return selfPtr;
}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

void UpdateListenerMgr::addListener( UpdateListener* listener )
{
	EnterCriticalSection(&lock);
	std::vector<UpdateListener*>::iterator it = listeners.begin();
	for(it ; it!=listeners.end() ; it++)
	{
		if(*it == listener)
		{
			LeaveCriticalSection(&lock);
			return;
		}
	}
	listeners.push_back(listener);
	LeaveCriticalSection(&lock);
}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

void UpdateListenerMgr::removeListener( UpdateListener* listener )
{
	EnterCriticalSection(&lock);
	std::vector<UpdateListener*>::iterator it = listeners.begin();
	for(it ; it!=listeners.end() ; it++)
	{
		if(*it == listener)
		{
			listeners.erase(it);
			break;
		}
	}
	LeaveCriticalSection(&lock);
}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

void UpdateListenerMgr::update( u32 evId,u32 param )
{
	EnterCriticalSection(&lock);
	std::vector<UpdateListener*>::iterator it = listeners.begin();
	for(it ; it!=listeners.end() ; it++)
	{
		UpdateListener* listener = *it;
		listener->update(evId,param);
	}
	LeaveCriticalSection(&lock);
}