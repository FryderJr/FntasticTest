// Fill out your copyright notice in the Description page of Project Settings.


#include "Path.h"
#include "Kismet/BlueprintFunctionLibrary.h"

// Sets default values
APath::APath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Spline = CreateDefaultSubobject<USplineComponent>(FName("Spline"));
	Spline->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APath::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float APath::GetPathLength() const
{
	
	return Spline->GetSplineLength();
}

FVector APath::GetLocationAtDistance(float Distance)
{
	return Spline->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
}

