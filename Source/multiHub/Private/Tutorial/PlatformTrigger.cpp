// Fill out your copyright notice in the Description page of Project Settings.


#include "Tutorial/PlatformTrigger.h"
#include "Tutorial/MT_MovingPlatform.h"
#include "Components/BoxComponent.h"

APlatformTrigger::APlatformTrigger()
{

	PrimaryActorTick.bCanEverTick = true;
	boxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	SetRootComponent(boxTrigger);

}


void APlatformTrigger::BeginPlay()
{
	Super::BeginPlay();

	if (boxTrigger)
	{
		boxTrigger->OnComponentBeginOverlap.AddUniqueDynamic(this, &APlatformTrigger::OnBeginOverlap);
		boxTrigger->OnComponentEndOverlap.AddUniqueDynamic(this, &APlatformTrigger::OnEndOverlap);
	}
}


void APlatformTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlatformTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Hey"));

	for (auto platform : platforms)
	{
		if (platform)
		{
			platform->SetCanMove(true);
		}
		
	}
}

void APlatformTrigger::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("BYE"));
	for (auto platform : platforms)
	{
		if (platform)
		{
			platform->SetCanMove(false);
		}
	}
}

