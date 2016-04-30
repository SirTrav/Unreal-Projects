// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pickup.h"
#include "BatteryPickup.generated.h"

/**
 * 
 */
UCLASS()
class BATTERYCOLLECTOR_API ABatteryPickup : public APickup
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ABatteryPickup();
	
	/** Override WasCollected_Implementation (WasCollected es BluePrint native, por lo que ejecutar� esta funci�n autom�ticamente) */
	void WasCollected_Implementation() override;

	float GetPower();
protected:
	/** Cuanta energ�a da la bater�a al jugador*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Power", Meta = (BlueprintProtected = "true"))
	float BatteryPower;
};
