// Fill out your copyright notice in the Description page of Project Settings.


#include "RTS_GameTime.h"

URTS_GameTime::URTS_GameTime():TimeScale(0)
{
}

void URTS_GameTime::Initialize(float timeScale,const FDateTime& dateTime)
{
	this->TimeScale = timeScale;
	this->Initial = dateTime;
	this->Current = dateTime;
}

void URTS_GameTime::UpdateTimescale(float timeScale)
{
	this->TimeScale = timeScale;
}

void URTS_GameTime::UpdateTime(float seconds)
{
	float scaledTime = seconds * this->TimeScale;
	this->Current += FTimespan::FromSeconds(scaledTime);
}

FString URTS_GameTime::ToString() const
{
	return this->Current.ToString();
}

FTimespan URTS_GameTime::TimespanSinceStart() const
{
	FTimespan result = this->Current - this->Initial;
	return result;
}

float URTS_GameTime::GetHourOfDay() const
{
	float result = Current.GetMillisecond() / 1000;
	result = (result + Current.GetSecond()) / 60;
	result = (result + Current.GetMinute()) / 60;
	result = (result + Current.GetHour());
	return result;
}