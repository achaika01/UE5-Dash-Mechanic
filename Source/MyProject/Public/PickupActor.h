

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupActor.generated.h"

UCLASS()
class MYPROJECT_API APickupActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* PickupMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
