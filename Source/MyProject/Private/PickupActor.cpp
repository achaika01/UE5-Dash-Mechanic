


#include "PickupActor.h"
#include "Engine/Engine.h"


// Sets default values
APickupActor::APickupActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	RootComponent = PickupMesh;
}


// Called when the game starts or when spawned
void APickupActor::BeginPlay()
{
	Super::BeginPlay();
	FString Message = FString("Spawned with role: ") + FString(HasAuthority() ? TEXT("Authority") : TEXT("Proxy"));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, Message);
	
}

void APickupActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (HasAuthority()) {
		Destroy();
	}
}

// Called every frame
void APickupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FString Message = FString::Printf(TEXT("Local Role: %s, Remote Role: %s"), *UEnum::GetValueAsString(GetLocalRole()), *UEnum::GetValueAsString(GetRemoteRole()));
	GEngine->AddOnScreenDebugMessage(1, 0.0f, FColor::Cyan, Message);

}


