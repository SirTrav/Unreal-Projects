// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryCollector.h"
#include "BatteryPickup.h"

// Sets default values
ABatteryPickup::ABatteryPickup()
{
	// Activamos las f�sicas
	GetMesh()->SetSimulatePhysics(true);
}

void ABatteryPickup::WasCollected_Implementation()
{
	Super::WasCollected_Implementation();
	// Destruimos el objeto
	Destroy();
}

