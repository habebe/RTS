// Fill out your copyright notice in the Description page of Project Settings.


#include "RTS_CameraActionHandler.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"

bool URTS_CameraActionHandler::is(ERTS_CameraActionState type) const
{
	return (this->CurrentActionType == type);
}

bool URTS_CameraActionHandler::beginAction(ERTS_CameraActionState type)
{
	bool status = (CurrentActionType == ERTS_CameraActionState::None) || (CurrentActionType == type);
	if (status) {
		PreviousActionType = CurrentActionType;
		CurrentActionType = type;
	}
	return status;
}

bool URTS_CameraActionHandler::begin(ERTS_CameraActionState type, float axisValue)
{
	if (type == ERTS_CameraActionState::Move)
	{
		if (abs(axisValue) > 0)
			return true;
	}
	return this->beginAction(type);
}

bool URTS_CameraActionHandler::end(ERTS_CameraActionState type)
{
	bool status = (CurrentActionType == ERTS_CameraActionState::None) || (CurrentActionType == type);
	if(status)
		CurrentActionType = PreviousActionType;
	return status;
}

bool URTS_CameraActionHandler::moveForward(APawn* pawn, float value, float speed)
{
	if (this->begin(ERTS_CameraActionState::Move,value))
	{
		const FTransform& transform = pawn->GetActorTransform();
		const FVector& currentLocation = transform.GetLocation();
		FVector direction = UKismetMathLibrary::TransformDirection(transform, FVector(speed * value, 0, 0));
		FVector newLocation(
			direction.X + currentLocation.X,
			direction.Y + currentLocation.Y,
			currentLocation.Z
			);
		pawn->SetActorLocation(newLocation, true);
		this->end(ERTS_CameraActionState::Move);
	}
	return false;
}

bool URTS_CameraActionHandler::moveRight(APawn* pawn, float value, float speed)
{
	if (this->begin(ERTS_CameraActionState::Move, value))
	{
		const FTransform& transform = pawn->GetActorTransform();
		const FVector& currentLocation = transform.GetLocation();
		FVector direction = UKismetMathLibrary::TransformDirection(transform, FVector(0,speed * value,0));
		FVector newLocation(
			direction.X + currentLocation.X,
			direction.Y + currentLocation.Y,
			currentLocation.Z
			);
		pawn->SetActorLocation(newLocation, true);
		this->end(ERTS_CameraActionState::Move);
	}
	return false;
}

bool URTS_CameraActionHandler::zoom(USpringArmComponent* component, float speed, float minimumZoom, float maximumZoom)
{
	if (this->beginAction(ERTS_CameraActionState::Zoom))
	{
		float newDistance = component->TargetArmLength + speed;
		newDistance = UKismetMathLibrary::FClamp(newDistance, minimumZoom, maximumZoom);
		component->TargetArmLength = newDistance;
		this->end(ERTS_CameraActionState::Zoom);
	}
	return false;
}

bool URTS_CameraActionHandler::zoomReset(USpringArmComponent* component, float distance)
{
	if (this->beginAction(ERTS_CameraActionState::Zoom))
	{
		component->TargetArmLength = distance;
		this->end(ERTS_CameraActionState::Zoom);
	}
	return false;
}

bool URTS_CameraActionHandler::pan(float x, float y, AActor* target, float speed, float minimumPitch, float maximumPitch)
{
	const FRotator& rotation = target->GetActorRotation();

	float roll = rotation.Roll;
	float yaw = (x * speed) + rotation.Yaw;
	float pitch = (y * speed) + rotation.Pitch;
	pitch = UKismetMathLibrary::FClamp(pitch, minimumPitch, maximumPitch);

	FRotator newRotation(pitch, yaw, roll );


	target->SetActorRotation(newRotation);

	//UE_LOG(LogTemp, Warning, TEXT("Pan (%f,%f,%f) -> (%f,%f,%f)"), rotation.Roll, rotation.Pitch, rotation.Yaw, newRotation.Roll, newRotation.Pitch, newRotation.Yaw );
	return true;
}

bool URTS_CameraActionHandler::panReset(AActor* target, FRotator initialPosition)
{
	if (this->beginAction(ERTS_CameraActionState::Pan))
	{
		target->SetActorRotation(initialPosition);
		this->end(ERTS_CameraActionState::Pan);
	}
	return false;
}

