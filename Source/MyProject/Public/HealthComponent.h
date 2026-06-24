// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerApplyDamage(float Amount);
	bool ServerApplyDamage_Validate(float Amount);
	void ServerApplyDamage_Implementation(float Amount);
	UFUNCTION(NetMulticast, Unreliable) 
	void MulticastDamageFlash();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_CurrentHealth)
	float CurrentHealth;
	UPROPERTY(VisibleAnywhere, Replicated)
	float MaxHealth;
	UFUNCTION()
	void OnRep_CurrentHealth();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
