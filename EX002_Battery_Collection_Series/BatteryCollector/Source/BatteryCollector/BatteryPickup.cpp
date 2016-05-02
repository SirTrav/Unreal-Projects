// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryCollector.h"
#include "BatteryPickup.h"
#include "ParticleDefinitions.h"
#include "Engine/SkeletalMeshSocket.h"

// Sets default values
ABatteryPickup::ABatteryPickup()
{
	// Activamos las físicas
	GetMesh()->SetSimulatePhysics(true);

	BatteryPower = 150.0f;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> Template
	(TEXT("ParticleSystem'/Game/ExampleContent/Effects/ParticleSystems/P_electricity_arc.P_electricity_arc'"));

	if (Template.Succeeded())
	{
		ParticleSystemTemplate = Template.Object;
	} else 
	{
		UE_LOG(LogTemp, Warning, TEXT("'P_electricity_arc' not found"));
	}
	
}

void ABatteryPickup::WasCollected_Implementation()
{
	Super::WasCollected_Implementation();
	
	ParticleSystem = UGameplayStatics::SpawnEmitterAttached(ParticleSystemTemplate, GetMesh(), NAME_None);
	UpdateBeamTargetPoint();

	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(
		UnusedHandle, this, &ABatteryPickup::DestroyAfterDelay, 1, false);

}

void ABatteryPickup::DestroyAfterDelay() {
	// Destruimos el objeto
	Destroy();
}

float ABatteryPickup::GetPower()
{
	return BatteryPower;
}

// Called every frame
void ABatteryPickup::Tick(float DeltaTime)
{
	if (ParticleSystem)
	{
		UpdateBeamTargetPoint();
	}
}

void ABatteryPickup::UpdateBeamTargetPoint()
{
	ACharacter* Character = GetWorld()->GetFirstPlayerController()->GetCharacter();
	FVector SocketLocation = Character->GetMesh()->GetSocketLocation("spine_02");
	ParticleSystem->SetBeamTargetPoint(0, SocketLocation, 0);
}