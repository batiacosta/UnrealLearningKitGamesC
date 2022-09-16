// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	//	For debugging purposes, I can use these options to show info on console.
	UE_LOG(LogTemp, Display, TEXT("Holis! the distance for this bad boy is: %f"), MoveDistance);
	FString Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("Holis!, the name of this actor is: %s"), *Name);	//	Converts FString into string
	UE_LOG(LogTemp, Error, TEXT("Holis!"));

	
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//	Update the location of our platform forwards
		//	Get current location
	FVector CurrentLocation = GetActorLocation();
		//	Add vector to that location
	CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime);
		//	Set the location
	SetActorLocation(CurrentLocation);
	//	Set platform back if gone too far
		//	Check how far we've moved
	float DistanceMoved = FVector::Dist(StartLocation, CurrentLocation);
		//	Reverse direction of motion if gone too far
	if(DistanceMoved > MoveDistance)
	{
		float Overshoot = DistanceMoved - MoveDistance;
		FString NameActor = GetName();
		UE_LOG(LogTemp, Warning, TEXT("The actor: %s has an overshot value of: %f"), *NameActor, Overshoot)
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDirection * MoveDistance;
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
	}
} 

