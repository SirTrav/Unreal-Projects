// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo01.h"
#include "SpawnController.h"
#define OUT
#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,text)

// Sets default values for this component's properties
USpawnController::USpawnController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	FString BlueprintPath = "Blueprint'/Game/Blueprints/BP_Dynamic_Box.BP_Dynamic_Box'";
	static ConstructorHelpers::FObjectFinder<UBlueprint> ItemBlueprint(TEXT("Blueprint'/Game/Blueprints/BP_Dynamic_Box.BP_Dynamic_Box'"));
	if (ItemBlueprint.Object) {
		SpawnableItemClass = (UClass*)ItemBlueprint.Object->GeneratedClass;
	}
	else {
		print("Blueprint'/Game/Blueprints/BP_Dynamic_Box.BP_Dynamic_Box' not found");
	}
}




// Called when the game starts
void USpawnController::BeginPlay()
{
	Super::BeginPlay();
	InputComponent = GetOwner()->InputComponent;

	if (InputComponent) {
		InputComponent->BindAction("Spawn",
			IE_Pressed,
			this,
			&USpawnController::Spawn);

		InputComponent->BindAction("Destroy",
			IE_Pressed,
			this,
			&USpawnController::Destroy);
	
	}


}


// Called every frame
void USpawnController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FHitResult Hit;
	USpawnController::GetHitResult(Hit);

	if (Hit.GetComponent()) {
		FString HitLocationStr = FString(Hit.Location.ToString());
		DrawDebugPoint(GetWorld(), Hit.Location, 50, FColor::Red);
	}
}

void USpawnController::Spawn()
{
	if (SpawnableItemClass) {
		FHitResult Hit;
		USpawnController::GetHitResult(Hit);
		if (Hit.GetComponent()) {
			// Vector normal a la colisión
			FVector NormalVector = Hit.ImpactNormal;
			// TODO hardcoded value
			GetWorld()->SpawnActor<AActor>(SpawnableItemClass,
				Hit.ImpactPoint + NormalVector * 50,
				FRotator::ZeroRotator);
		}
	}
}

void USpawnController::Destroy() {
	FHitResult Hit;
	USpawnController::GetHitResult(Hit);
	if (Hit.GetComponent()) {
		GetWorld()->DestroyActor(Hit.GetActor());
	}
}

void USpawnController::GetHitResult(OUT FHitResult& Hit)
{
	FVector ViewPointLocation;
	FRotator ViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT ViewPointLocation,
		OUT ViewPointRotation);

	FVector TargetLocation = ViewPointLocation +
		Reach * ViewPointRotation.Vector();

	FCollisionQueryParams TraceParams(FName(TEXT("WeaponTrace")), false, GetOwner());
	GetWorld()->LineTraceSingle(OUT Hit, ViewPointLocation, TargetLocation, ECC_WorldStatic, TraceParams);
}

