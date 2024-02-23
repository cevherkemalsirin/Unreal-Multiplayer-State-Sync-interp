// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RayCarUtils.h"
#include "RayCarBase.generated.h"

class URayWheel;

UCLASS()
class MULTIHUB_API ARayCarBase : public APawn
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Vehicle", meta=(AllowPrivateAcess = "true"))
	UStaticMeshComponent* bodyMesh;
	UPROPERTY(VisibleAnywhere, Category = "Vehicle | Suspension", meta = (AllowPrivateAcess = "true"))
	USceneComponent* topLink_RF;
	UPROPERTY(VisibleAnywhere, Category = "Vehicle | Suspension", meta = (AllowPrivateAcess = "true"))
	USceneComponent* topLink_LF;
	UPROPERTY(VisibleAnywhere, Category = "Vehicle | Suspension", meta = (AllowPrivateAcess = "true"))
	USceneComponent* topLink_RB;
	UPROPERTY(VisibleAnywhere, Category = "Vehicle | Suspension", meta = (AllowPrivateAcess = "true"))
	USceneComponent* topLink_LB;
	UPROPERTY(VisibleAnywhere, Category = "Vehicle | Wheel", meta = (AllowPrivateAcess = "true"))
	uint8 wheelNumber;

	//Wheels number
	UPROPERTY(VisibleAnywhere, Category = "Vehicle | Wheel", meta = (AllowPrivateAcess = "true"))
	URayWheel* wheel_RF;

	UPROPERTY(VisibleAnywhere, Category = "Vehicle | Wheel", meta = (AllowPrivateAcess = "true"))
	URayWheel* wheel_LF;

	UPROPERTY(VisibleAnywhere, Category = "Vehicle | Wheel", meta = (AllowPrivateAcess = "true"))
	URayWheel* wheel_RB;

	UPROPERTY(VisibleAnywhere, Category = "Vehicle | Wheel", meta = (AllowPrivateAcess = "true"))
	URayWheel* wheel_LB;


	//suspensions for each wheels
	TArray<USceneComponent*> suspensions;

	// length of ray trace from link top
	TArray<float> rayLengths;


	//Suspension struct for each suspension properties.
	UPROPERTY(EditDefaultsOnly, Category = "Vehicle | Suspension", meta = (AllowPrivateAcess = "true"))
	TArray<FSuspension> suspensionProperties;
	
protected:
	float deltaTime;
	virtual void BeginPlay() override;

public:	

	ARayCarBase();

	virtual void Tick(float DeltaTime) override;


	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
