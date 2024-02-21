// Fill out your copyright notice in the Description page of Project Settings.
#include "Tutorial/MT_MovingPlatform.h"
#include "Kismet/KismetMathLibrary.h"


AMT_MovingPlatform::AMT_MovingPlatform() :speed(100.f), moveStyle(EMoveStyle::EMS_Single), bCanMove(true)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMT_MovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	mainMeshComp = GetStaticMeshComponent();

	startLocation = GetActorLocation();
	globalTargetLocation = GetTransform().TransformPosition(targetLocation);

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}
}



void AMT_MovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (HasAuthority())
	{
		if (bCanMove)
		{
			MovePlatform();
		}
		
	}

}


void AMT_MovingPlatform::MovePlatform()
{
	float startActorDist = (GetActorLocation() - startLocation).Size();
	float startTargetDist = (globalTargetLocation - startLocation).Size();

	FVector direction = (globalTargetLocation - startLocation).GetSafeNormal();
	FVector offset = direction * speed * GetWorld()->GetDeltaSeconds();

	switch (moveStyle)
	{	
	case EMoveStyle::EMS_Single:
	{
		if (startActorDist >= startTargetDist)
		{
			return;
		}
	}
	break;
	case EMoveStyle::EMS_Pingpong:
	{		
		if (startActorDist >= startTargetDist)
		{
			FVector temp = startLocation;
			startLocation = globalTargetLocation;
			globalTargetLocation = temp;
		}
	}
	break;
	default:
		break;
	}

	AddActorWorldOffset(offset, true);
}