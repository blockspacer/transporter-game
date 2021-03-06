#include "transporter.h"

static DebugRegistry* volatile debugRegistry;

DebugRegistryBaseItem::DebugRegistryBaseItem( str name )
{
	debugItemName = name;
}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

DebugRegistryBaseItem::~DebugRegistryBaseItem()
{
	DebugRegistry::getInstance()->removeItem(this->debugItemName);
}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

str DebugRegistryBaseItem::getDebugItemName()
{
	return debugItemName;
}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

DebugRegistry::DebugRegistry()
{
	InitializeCriticalSection(&lock);
}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

DebugRegistry::~DebugRegistry()
{
	EnterCriticalSection(&lock);
	items.clear();
	LeaveCriticalSection(&lock);
	DeleteCriticalSection(&lock);
}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

void DebugRegistry::destroyDebugRegistry()
{
	if(debugRegistry)
	{
		delete debugRegistry;
		debugRegistry = NULL;
	}
}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

DebugRegistry* DebugRegistry::getInstance()
{
	static DebugRegistry* volatile selfPtr;
	if( selfPtr == NULL)
	{
		DebugRegistry* newDebugRegistry = new DebugRegistry;
		LONG value = InterlockedCompareExchange((LONG*)&selfPtr,(LONG)newDebugRegistry,NULL);
		if( value != NULL )
		{
			delete newDebugRegistry;
		}
		else
		{
			debugRegistry = selfPtr;
			atexit(destroyDebugRegistry);
		}
	}	
	return selfPtr;
}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

DebugRegistryBaseItem* DebugRegistry::getItem( str name )
{
	EnterCriticalSection(&lock);
	std::map<str,DebugRegistryBaseItem*>::iterator it = items.find(name);
	if(it != items.end())
	{
		DebugRegistryBaseItem* item = it->second;
		LeaveCriticalSection(&lock);
		return item;
	}
	LeaveCriticalSection(&lock);
	return NULL;
}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

bit DebugRegistry::addItem( DebugRegistryBaseItem* item )
{
	EnterCriticalSection(&lock);
	std::map<str,DebugRegistryBaseItem*>::iterator it = items.find(item->getDebugItemName());
	if(it == items.end())
	{
		items[item->getDebugItemName()] = item;
		LeaveCriticalSection(&lock);
		return true;
	}
	LeaveCriticalSection(&lock);
	return false;
}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

void DebugRegistry::removeItem( str name )
{
	EnterCriticalSection(&lock);
	items.erase(name);
	LeaveCriticalSection(&lock);
}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

str DebugRegistry::print()
{
	EnterCriticalSection(&lock);
	str result;
	std::map<str,DebugRegistryBaseItem*>::iterator it = items.begin();
	for(it ; it!=items.end() ; it++)
	{
		DebugRegistryBaseItem* item = it->second;
		result += item->print()+"\n";
	}
	LeaveCriticalSection(&lock);
	return result;
}