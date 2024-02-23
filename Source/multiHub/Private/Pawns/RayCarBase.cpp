// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/RayCarBase.h"
#include "Pawns/Components/RayWheel.h"

ARayCarBase::ARayCarBase():wheelNumber(4)
{
 
	PrimaryActorTick.bCanEverTick = true;

	bodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChasisMesh"));
	this->SetRootComponent(bodyMesh);
	
	topLink_RF = CreateDefaultSubobject<USceneComponent>(TEXT("topLinkRF"));
	topLink_LF = CreateDefaultSubobject<USceneComponent>(TEXT("ToplinkLF"));
	topLink_RB = CreateDefaultSubobject<USceneComponent>(TEXT("ToplinkRB"));
	topLink_LB = CreateDefaultSubobject<USceneComponent>(TEXT("ToplinkLB"));

	suspensions.Add(topLink_RF);
	suspensions.Add(topLink_LF);
	suspensions.Add(topLink_RB);
	suspensions.Add(topLink_LB);

	wheel_RF = CreateDefaultSubobject <URayWheel>(TEXT("Wheel_RF"));
	wheel_RF->SetupAttachment(RootComponent);
	topLink_RF->SetupAttachment(RootComponent);
	topLink_LF->SetupAttachment(RootComponent);
	topLink_RB->SetupAttachment(RootComponent);
	topLink_LB->SetupAttachment(RootComponent);




}


void ARayCarBase::BeginPlay()
{
	Super::BeginPlay();
	
	for (int i = 0; i < wheelNumber; i++)
	{
		rayLengths.Add(suspensionProperties[i].restLength  + suspensionProperties[i].travel + wheel_RF->GetRadius());
		
	}

}


void ARayCarBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	deltaTime = DeltaTime;
	
	for (int i = 0; i < wheelNumber; i++)
	{
		if (GetWorld())
		{
			FHitResult hitResult;
			FVector startLoc = suspensions[i]->GetComponentLocation();
			FVector endLoc = startLoc + (-suspensions[i]->GetUpVector() * rayLengths[i]);
			FCollisionQueryParams CollisionParameters;
			CollisionParameters.AddIgnoredActor(this);
			if (GetWorld()->LineTraceSingleByChannel(hitResult, startLoc, endLoc, ECollisionChannel::ECC_Visibility, CollisionParameters))
			{
				DrawDebugLine(GetWorld(), startLoc, hitResult.Location, FColor::Red, false, -1.0f, 0, 2.0f);
				DrawDebugSphere(GetWorld(), hitResult.Location, 1.f, 1, FColor::Green,false,-1.0f,0,2.f);
				
			}
			else
			{
				DrawDebugLine(GetWorld(), startLoc, endLoc, FColor::Red, false, -1.0f, 0, 2.0f);
			}
		}
	}
	
}


void ARayCarBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

