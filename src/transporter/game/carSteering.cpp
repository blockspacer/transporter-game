#include "transporter.h"

CarSteering::CarSteering( InputSystem* inputSystem )
: DebugRegistryBaseItem("steering")
{
	this->inputSystem = inputSystem;
	steering = 0.0f;
	throttle = 0.0f;
	braking  = 0.0f;
	handBrake= false;
	gearShift= 0;

	steeringSaturation = 0.0010f;
	brakingSaturation  = 0.0025f;
	throttleSaturation = 0.0012f;

	throttleKey			= DIK_UPARROW;
	brakingKey			= DIK_DOWNARROW;
	leftSteeringKey		= DIK_LEFTARROW;
	rightSteeringKey	= DIK_RIGHTARROW;
	handBrakeKey		= DIK_LSHIFT;
	gearUpshiftKey		= DIK_A;
	gearDownshiftKey	= DIK_Z;

	isThrottleKeyPressed    = false;
	isBrakingKeyPressed		= false;
	isSteeringKey			= false;

	inputSystem->keyboard.onKeyDown.connect(onKeyDown,this);
	inputSystem->keyboard.onKeyUp.connect(onKeyUp,this);
	inputSystem->keyboard.onKeyPress.connect(onKeyPressed,this);

	DebugRegistry::getInstance()->addItem(this);
}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

CarSteering::~CarSteering()
{
	inputSystem->keyboard.onKeyDown.disconnect(onKeyDown);
	inputSystem->keyboard.onKeyUp.disconnect(onKeyUp);
	inputSystem->keyboard.onKeyPress.disconnect(onKeyPressed);
	DebugRegistry::getInstance()->removeItem(this->debugItemName);
}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

f32 CarSteering::getSteering()
{
	return steering;
}

f32 CarSteering::getThrottle()
{
	return throttle;
}

f32 CarSteering::getBraking()
{
	return braking;
}

bit CarSteering::getHandBrake()
{
	return handBrake;
}

i32 CarSteering::getGearShift()
{
	return gearShift;
}

f32 CarSteering::getSteeringSaturation()
{
	return steeringSaturation;
}

f32 CarSteering::getThrottleSaturation()
{
	return throttleSaturation;
}

f32 CarSteering::getBrakingSaturation()
{
	return brakingSaturation;
}

void CarSteering::setSteeringSaturation( f32 value )
{
	steeringSaturation = value;
}

void CarSteering::setThrottleSaturation( f32 value )
{
	throttleSaturation = value;
}

void CarSteering::setBrakingSaturation( f32 value )
{
	brakingSaturation = value;
}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

void CarSteering::onKeyDown( void* userptr,u32 btn )
{	
	CarSteering* This = (CarSteering*)userptr;

	if(btn == This->throttleKey)
		This->isThrottleKeyPressed = true;
	if(btn == This->brakingKey)
		This->isBrakingKeyPressed  = true;
	if(btn == This->leftSteeringKey)
		if(This->isSteeringKey ==  1 || This->isSteeringKey ==  0)
			This->isSteeringKey = -1;
	if(btn == This->rightSteeringKey)
		if(This->isSteeringKey == -1 || This->isSteeringKey ==  0)
			This->isSteeringKey =  1;
	if(btn == This->handBrakeKey)
		This->handBrake = true;
}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

void CarSteering::onKeyUp( void* userptr,u32 btn )
{
	CarSteering* This = (CarSteering*)userptr;

	if(btn == This->throttleKey)
		This->isThrottleKeyPressed = false;
	if(btn == This->brakingKey)
		This->isBrakingKeyPressed  = false;
	if(btn == This->leftSteeringKey)
		if(This->isSteeringKey == -1)
			This->isSteeringKey = 0;
	if(btn == This->rightSteeringKey)
		if(This->isSteeringKey ==  1)
			This->isSteeringKey = 0;
	if(btn == This->handBrakeKey)
		This->handBrake = false;
}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

void CarSteering::onKeyPressed( void* userptr,u32 btn )
{
	CarSteering* This = (CarSteering*)userptr;

	if(btn == This->gearUpshiftKey) 
		 This->gearShift = (This->gearShift==7)?7:This->gearShift+1;
	if(btn == This->gearDownshiftKey ) 
		 This->gearShift = (This->gearShift==-1)?-1:This->gearShift-1;
}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

void CarSteering::updateThrottleKey(u32 timeElapse)
{
	if(isThrottleKeyPressed && throttle<=1.0f)
	{
		throttle = clampValue(throttle + throttleSaturation*(f32)timeElapse,0.0f,1.0f);
	}
	else if(!isThrottleKeyPressed && throttle>0.0f)
	{
		throttle = clampValue(throttle - throttleSaturation*(f32)timeElapse,0.0f,1.0f);
	}
}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

void CarSteering::updateBrakingKey( u32 timeElapse )
{
	if(isBrakingKeyPressed && braking<=1.0f)
	{
		braking = clampValue(braking + brakingSaturation*(f32)timeElapse,0.0f,1.0f);
	}
	else if(!isBrakingKeyPressed && braking>0.0f)
	{
		braking = clampValue(braking - brakingSaturation*(f32)timeElapse,0.0f,1.0f);
	}
}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

void CarSteering::updateSteeringKey( u32 timeElapse )
{
	f32 reverseFactor = 1.0f;
	f32 normalizationFactor = 1.25f;
	if(isSteeringKey == 0)
	{
		f32 changes = steeringSaturation*normalizationFactor*(f32)timeElapse;
		if(steering < 0.0f)
		{
			steering = clampValue(steering + changes,-1.0f,0.0f);
		}
		else
		{
			steering = clampValue(steering - changes,0.0f,1.0f);
		}
	}
	else if(isSteeringKey==-1 && steering>=-1.0f)
	{		
		if(steering > 0.0f)
		{
			reverseFactor = 4.0f;
		}
		steering = clampValue(steering - steeringSaturation*reverseFactor*(f32)timeElapse,-1.0f,1.0f);
	}
	else if(isSteeringKey==1 && steering<=1.0f)
	{
		if(steering < 0.0f)
		{
			reverseFactor = 4.0f;
		}
		steering = clampValue(steering + steeringSaturation*reverseFactor*(f32)timeElapse,-1.0f,1.0f);
	}	
}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

void CarSteering::update( u32 timeElapse )
{
	updateBrakingKey(timeElapse);
	updateSteeringKey(timeElapse);
	updateThrottleKey(timeElapse);
}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

str CarSteering::print()
{
	return StrPrintf("carSteering [steering : %.2f, throttle : %.2f, brake : %.2f, manual gear : %d]",
		             steering,throttle,braking,gearShift);
}
//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧