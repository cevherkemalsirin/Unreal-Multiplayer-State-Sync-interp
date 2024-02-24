// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/RayCarBase.h"
#include "Pawns/Components/RayWheel.h"


ARayCarBase::ARayCarBase():wheelNumber(4), drawDebug(false)
{
 
	PrimaryActorTick.bCanEverTick = true;

	bodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChasisMesh"));
	this->SetRootComponent(bodyMesh);
	
	topLink_RF = CreateDefaultSubobject<USceneComponent>(TEXT("topLinkRF"));
	topLink_LF = CreateDefaultSubobject<USceneComponent>(TEXT("ToplinkLF"));
	topLink_RB = CreateDefaultSubobject<USceneComponent>(TEXT("ToplinkRB"));
	topLink_LB = CreateDefaultSubobject<USceneComponent>(TEXT("ToplinkLB"));
	topLink_RF->SetupAttachment(RootComponent);
	topLink_LF->SetupAttachment(RootComponent);
	topLink_RB->SetupAttachment(RootComponent);
	topLink_LB->SetupAttachment(RootComponent);

	suspensions.Add(topLink_RF);
	suspensions.Add(topLink_LF);
	suspensions.Add(topLink_RB);
	suspensions.Add(topLink_LB);

	wheel_RF = CreateDefaultSubobject <URayWheel>(TEXT("Wheel_RF"));
	wheel_RF->SetupAttachment(topLink_RF);
	wheel_LF = CreateDefaultSubobject <URayWheel>(TEXT("Wheel_LF"));
	wheel_LF->SetupAttachment(topLink_LF);
	wheel_RB = CreateDefaultSubobject <URayWheel>(TEXT("Wheel_RB"));
	wheel_RB->SetupAttachment(topLink_RB);
	wheel_LB = CreateDefaultSubobject <URayWheel>(TEXT("Wheel_LB"));
	wheel_LB->SetupAttachment(topLink_LB);

}


void ARayCarBase::BeginPlay()
{
	Super::BeginPlay();
	
	for (int i = 0; i < wheelNumber; i++)
	{
		rayLengths.Add(suspensionProperties[i].restLength  + suspensionProperties[i].travel + wheel_RF->GetRadius());
		//Init default values
		suspensionLengths.Add(suspensionProperties[i].restLength);
		PreSuspensionLengths.Add(suspensionProperties[i].restLength);
		b_wheelsContact.Add(false);
		hitResults.Add(FHitResult());
		suspensionFPower.Add(0.0f);
	}

}


void ARayCarBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	deltaTime = DeltaTime;
	
	StartSuspensions();

}


void ARayCarBase::StartSuspensions()
{
	for (int i = 0; i < wheelNumber && GetWorld(); i++)
	{
		FHitResult hitResult;
		FVector startLoc = suspensions[i]->GetComponentLocation();
		FVector endLoc = startLoc + (-suspensions[i]->GetUpVector() * rayLengths[i]);

		FCollisionQueryParams CollisionParameters;
		CollisionParameters.AddIgnoredActor(this);
		bool isHit = GetWorld()->LineTraceSingleByChannel(hitResult, startLoc, endLoc, ECollisionChannel::ECC_Visibility, CollisionParameters);
		b_wheelsContact[i] = hitResult.bBlockingHit;
		hitResults[i] = hitResult;

		if (drawDebug)
		{
			if (isHit)
			{
				DrawDebugLine(GetWorld(), startLoc, hitResult.Location, FColor::Red, false, -1.0f, 0, 2.0f);
				DrawDebugSphere(GetWorld(), hitResult.Location, 1.f, 1, FColor::Green, false, -1.0f, 0, 2.f);

			}
			else
			{
				DrawDebugLine(GetWorld(), startLoc, endLoc, FColor::Red, false, -1.0f, 0, 2.0f);

			}
		}

		GenerateSuspensionLength(i);
		ApplySuspensionForce(i);
	}

}


void ARayCarBase::GenerateSuspensionLength(uint32 i)
{
	FVector startLoc = suspensions[i]->GetComponentLocation();

	if (hitResults[i].bBlockingHit)
	{
		suspensionLengths[i] = (startLoc - (hitResults[i].Location + (suspensions[i]->GetUpVector() * wheel_RF->GetRadius()))).Length();
		suspensionLengths[i] = FMath::Clamp(suspensionLengths[i],
			suspensionProperties[i].restLength - suspensionProperties[i].travel,
			suspensionProperties[i].restLength + suspensionProperties[i].travel);
	}
	else
	{
		//if not hit then suspesion length will be the max length
		suspensionLengths[i] = suspensionProperties[i].restLength + suspensionProperties[i].travel;
	}
}


void ARayCarBase::ApplySuspensionForce(uint32 i)
{
	// Force = (restLength - currentLength) * stiffness, if wheel goes upwards the force is positive, else negative
	float forcePower = (suspensionProperties[i].restLength - suspensionLengths[i]) * suspensionProperties[i].stiffnes;

	//opposing force to stabilize the waveing movement.
	float suspensionSpeed = (PreSuspensionLengths[i] - suspensionLengths[i]) / deltaTime;
	float damperForce = suspensionSpeed * suspensionProperties[i].damper;
	forcePower += damperForce;

	suspensionFPower[i] = FMath::Clamp(forcePower, suspensionProperties[i].minForce, suspensionProperties[i].maxForce);
	FVector Force = suspensionFPower[i] * suspensions[i]->GetUpVector();

	bodyMesh->AddForceAtLocation(Force * 100.0f /*to convert to meters*/, suspensions[i]->GetComponentLocation());

	PreSuspensionLengths[i] = suspensionLengths[i];
}


void ARayCarBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

