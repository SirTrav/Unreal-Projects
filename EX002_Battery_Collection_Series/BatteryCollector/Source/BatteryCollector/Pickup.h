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

	FORCEINLINE UStaticMeshComponent* GetMesh() const { return PickupMesh; }

	// BlueprintPure se utiliza con métodos que no modifican el estado del juego (ej. Getters)
	// En el editor de blueprints no tienen input
	UFUNCTION(BlueprintPure, Category = "Pickup")
	bool IsActive() const;

	// BlueprintCallable se utiliza con métodos que sí pueden modificar el estado del juego
	// En el editor de blueprints tienen input
	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void SetActive(bool NewPickupState);

protected:
	/** True cuando el popup puede usarse*/
	bool bIsActive;

private:
	/** Static mesh para representar el pickup en el nivel */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Pickup", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* PickupMesh;
};
