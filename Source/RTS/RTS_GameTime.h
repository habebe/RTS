// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RTS_GameTime.generated.h"

/**
 * 
 */

UCLASS(Blueprintable, Category = "RTS|GameTime")
class RTS_API URTS_GameTime : public UObject
{
	GENERATED_BODY()
	
public:
    URTS_GameTime();

    UFUNCTION(BlueprintCallable, Category = "RTS|GameTime")
    void Initialize(float timeScale,const FDateTime& dateTime);
    
    UFUNCTION(BlueprintCallable, Category = "RTS|GameTime")
    void SetInitialDateTime(const FDateTime& dateTime);

    UFUNCTION(BlueprintCallable, Category = "RTS|GameTime")
    void SetCurrentDateTime(const FDateTime& dateTime);

    UFUNCTION(BlueprintCallable, Category = "RTS|GameTime")
    void SetTimescale(float timeScale);

    UFUNCTION(BlueprintCallable, Category = "RTS|GameTime")
    void UpdateTime(float seconds);

    UFUNCTION(BlueprintCallable, Category = "RTS|GameTime")
    FString ToString() const;
  
    UFUNCTION(BlueprintCallable, Category = "RTS|GameTime")
    float GetTimeScale() const { return this->TimeScale; }

    UFUNCTION(BlueprintCallable, Category = "RTS|GameTime")
    const FDateTime& GetInitial() const { return this->Initial; }

    UFUNCTION(BlueprintCallable, Category = "RTS|GameTime")
    const FDateTime& GetCurrent() const { return this->Current; }

    UFUNCTION(BlueprintCallable, Category = "RTS|GameTime")
    FTimespan TimespanSinceStart() const;

    UFUNCTION(BlueprintCallable, Category = "RTS|GameTime")
    float GetHourOfDay() const;

private:
    float TimeScale;
    FDateTime Initial;
    FDateTime Current;
};
