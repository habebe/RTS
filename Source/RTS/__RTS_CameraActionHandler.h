// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "__RTS_CameraActionHandler.generated.h"

UENUM(BlueprintType)
enum class ECameraActionType : uint8 {
    None = 0 UMETA(DisplayName = "None"),
    Move = 1 UMETA(DisplayName = "Move"),
    Pan = 2 UMETA(DisplayName = "Pan"),
    Zoom = 3 UMETA(DisplayName = "Zoom")
};
