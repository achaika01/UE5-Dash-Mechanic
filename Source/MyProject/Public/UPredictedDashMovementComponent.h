// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UPredictedDashMovementComponent.generated.h"

class FSavedMove_Dash : public FSavedMove_Character 
{
public:
	uint8 bWantsToDash;
	virtual void Clear() override;
	virtual void SetMoveFor(ACharacter* Character, float InDeltaTime, FVector const& NewAccel, class FNetworkPredictionData_Client_Character& ClientData) override;
	virtual uint8 GetCompressedFlags() const override;
	virtual bool CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* Character, float MaxDelta) const override;
};

class FNetworkPredictionData_Client_Dash : public FNetworkPredictionData_Client_Character {
public:
	FNetworkPredictionData_Client_Dash(const UCharacterMovementComponent& ClientMovement);
	virtual FSavedMovePtr AllocateNewMove() override;
};

/**
 * 
 */
UCLASS()
class MYPROJECT_API UPredictedDashMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
public:
	uint8 bWantsToDash;
	virtual FNetworkPredictionData_Client* GetPredictionData_Client() const override;
	virtual void UpdateFromCompressedFlags(uint8 Flags) override;
	virtual void OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity) override;
};
