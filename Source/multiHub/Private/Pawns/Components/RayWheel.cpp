// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/Components/RayWheel.h"
#include "DrawDebugHelpers.h"

URayWheel::URayWheel():mass(50.0f)
{
	PrimaryComponentTick.bCanEverTick = true;

}



void URayWheel::BeginPlay()
{
	Super::BeginPlay();
	radius = GetStaticMesh()->GetBounds().SphereRadius;

	
}



void URayWheel::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

