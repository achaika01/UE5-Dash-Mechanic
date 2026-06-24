// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
	MaxHealth = 100.0f;
	CurrentHealth = 100.0f;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::OnRep_CurrentHealth() 
{
	FString TheFloatStr = FString::SanitizeFloat(CurrentHealth);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, *TheFloatStr);
}

bool UHealthComponent::ServerApplyDamage_Validate(float Amount)
{
	if (Amount > 0 && Amount <= MaxHealth)
	{
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SERVER REJECTED CHEAT DAMAGE: %f"), Amount);
		return false;
	}
}

void UHealthComponent::ServerApplyDamage_Implementation(float Amount)
{
	CurrentHealth = (CurrentHealth - Amount) < 0 ? 0 : CurrentHealth - Amount;
	OnRep_CurrentHealth();
	MulticastDamageFlash();
}

void UHealthComponent::MulticastDamageFlash_Implementation() 
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("* FLASH EFFECT *"));
}

void UHealthComponent::GetLifetimeReplicatedProps (TArray<FLifetimeProperty>& OutLifetimeProps) const{
	DOREPLIFETIME(UHealthComponent, CurrentHealth);
	DOREPLIFETIME(UHealthComponent, MaxHealth);
}

