// Fill out your copyright notice in the Description page of Project Settings.


#include "UPredictedDashMovementComponent.h"
#include "GameFramework/Character.h"

void FSavedMove_Dash::Clear() {
	FSavedMove_Character::Clear();
	bWantsToDash = false;
}

void FSavedMove_Dash::SetMoveFor(ACharacter* Character, float InDeltaTime, FVector const& NewAccel, class FNetworkPredictionData_Client_Character& ClientData) {
    FSavedMove_Character::SetMoveFor(Character, InDeltaTime, NewAccel, ClientData);
    UPredictedDashMovementComponent* DashMovement = Cast<UPredictedDashMovementComponent>(Character->GetCharacterMovement());
    if (DashMovement)
    {
        bWantsToDash = DashMovement->bWantsToDash;
    }
}

uint8 FSavedMove_Dash::GetCompressedFlags() const
{
    uint8 Result = FSavedMove_Character::GetCompressedFlags();

    if (bWantsToDash)
    {
        Result |= FLAG_Custom_0;
    }

    return Result;
}

bool FSavedMove_Dash::CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* Character, float MaxDelta) const {
    TSharedPtr<FSavedMove_Dash> NewDashMove = StaticCastSharedPtr<FSavedMove_Dash>(NewMove);
    if (bWantsToDash != NewDashMove->bWantsToDash) {
        return false;
    }
    return FSavedMove_Character::CanCombineWith(NewMove, Character, MaxDelta);
}

FSavedMovePtr FNetworkPredictionData_Client_Dash::AllocateNewMove() {
    return FSavedMovePtr(new FSavedMove_Dash());
}

FNetworkPredictionData_Client* UPredictedDashMovementComponent::GetPredictionData_Client() const {
    if (ClientPredictionData == nullptr) {
        UPredictedDashMovementComponent* MutableThis = const_cast<UPredictedDashMovementComponent*>(this);
        MutableThis->ClientPredictionData = new FNetworkPredictionData_Client_Dash(*this);
    }
    return ClientPredictionData;
}

void UPredictedDashMovementComponent::UpdateFromCompressedFlags(uint8 Flags) {
    Super::UpdateFromCompressedFlags(Flags);
    bWantsToDash = (Flags & FSavedMove_Character::FLAG_Custom_0) != 0;
}

void UPredictedDashMovementComponent::OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity) {
    Super::OnMovementUpdated(DeltaSeconds, OldLocation, OldVelocity);
    float DashSpeed = 10000.0f;
    if (bWantsToDash) {
        Velocity = GetOwner()->GetActorForwardVector() * DashSpeed;
    }
    bWantsToDash = false;
}

FNetworkPredictionData_Client_Dash::FNetworkPredictionData_Client_Dash(const UCharacterMovementComponent& ClientMovement)
    : FNetworkPredictionData_Client_Character(ClientMovement)
{
}

