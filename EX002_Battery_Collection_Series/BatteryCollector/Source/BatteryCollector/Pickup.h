// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class BATTERYCOLLECTOR_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;	

	/** Getter de la StaticMesh */
	FORCEINLINE class UStaticMeshComponent* GetMesh() const { return PickupMesh; }

protected:
	/** True cuando el popup puede usarse*/
	bool bIsActive;

private:
	/** Static mesh para representar el pickup en el nivel */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Pickup", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* PickupMesh;
};
