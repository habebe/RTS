// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RTS_CameraActionHandler.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ERTS_CameraActionState : uint8 {
    None = 0 UMETA(DisplayName = "None"),
    Move = 1 UMETA(DisplayName = "Move"),
    Pan = 2 UMETA(DisplayName = "Pan"),
    Zoom = 3 UMETA(DisplayName = "Zoom")
};

class USpringArmComponent;

UCLASS(Blueprintable, Category = "RTS|CameraActionHandler")
class RTS_API URTS_CameraActionHandler : public UObject
{
	GENERATED_BODY()
public:
    URTS_CameraActionHandler() :CurrentActionType(ERTS_CameraActionState::None), PreviousActionType(ERTS_CameraActionState::None) {}

    UFUNCTION(BlueprintCallable, Category = "RTS|CameraActionHandler")
    bool is(ERTS_CameraActionState type) const;

    UFUNCTION(BlueprintCallable, Category = "RTS|CameraActionHandler")
    bool beginAction(ERTS_CameraActionState type);

    UFUNCTION(BlueprintCallable, Category = "RTS|CameraActionHandler")
    bool begin(ERTS_CameraActionState type, float axisValue);

    UFUNCTION(BlueprintCallable, Category = "RTS|CameraActionHandler")
    bool end(ERTS_CameraActionState type);

    UFUNCTION(BlueprintCallable, Category = "RTS|CameraActionHandler")
    bool moveForward(APawn* pawn, float value, float speed);

    UFUNCTION(BlueprintCallable, Category = "RTS|CameraActionHandler")
    bool moveRight(APawn* pawn, float value, float speed);

    UFUNCTION(BlueprintCallable, Category = "RTS|CameraActionHandler")
    bool zoom(USpringArmComponent* component, float speed, float minimumZoom, float maximumZoom);

    UFUNCTION(BlueprintCallable, Category = "RTS|CameraActionHandler")
    bool zoomReset(USpringArmComponent* component, float distance);


    UFUNCTION(BlueprintCallable, Category = "RTS|CameraActionHandler")
    bool pan(float x, float y, AActor* target, float speed, float minimumPitch, float maximumPitch);

    UFUNCTION(BlueprintCallable, Category = "RTS|CameraActionHandler")
    bool panReset(AActor* target, FRotator initialPosition);

    UPROPERTY(BlueprintReadOnly, Category = "RTS|CameraActionHandler")
    ERTS_CameraActionState CurrentActionType;

    UPROPERTY(BlueprintReadOnly, Category = "RTS|CameraActionHandler")
    ERTS_CameraActionState PreviousActionType;
};
