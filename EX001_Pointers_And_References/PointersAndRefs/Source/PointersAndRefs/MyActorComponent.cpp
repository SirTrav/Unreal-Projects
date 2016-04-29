// Fill out your copyright notice in the Description page of Project Settings.

#include "PointersAndRefs.h"
#include "MyActorComponent.h"


// Sets default values for this component's properties
UMyActorComponent::UMyActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMyActorComponent::BeginPlay()
{
	Super::BeginPlay();
	InputComponent = GetOwner()->InputComponent;

	if (InputComponent) {
		InputComponent->BindAction(
			"DoSomething", 
			IE_Pressed, 
			this, 
			&UMyActorComponent::DoSomething);
	}
	// ...
	
}

void UMyActorComponent::DoSomething() 
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	// Puntero
	FVector* LocationPtr;
	// Objeto
	FVector Location;

	Location.X = 5;
	// Hacemos que el puntero apunte a la dirección del objeto
	LocationPtr = &Location;

	PlayerController->ClientMessage(FString(TEXT("Acceso directo: ")));
	PlayerController->ClientMessage(FString::SanitizeFloat(Location.X));

	// Podemos modificar el valor de la variable indirectamente
	LocationPtr->X = 10;

	PlayerController->ClientMessage(FString(TEXT("Acceso indirecto: ")));
	PlayerController->ClientMessage(FString::SanitizeFloat(LocationPtr->X));

	// Alternativamente, podemos acceder al contenido del puntero así
	(*LocationPtr).X = 5;

	// Desasignamos el puntero
	LocationPtr = nullptr;
	if (!LocationPtr) {
		PlayerController->ClientMessage(FString(TEXT("Null pointer en LocationPtr")));
	}
	
}

// Called every frame
void UMyActorComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

