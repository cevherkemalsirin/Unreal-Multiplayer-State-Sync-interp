// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RayCarUtils.h"
#include "RayCarBase.generated.h"

class URayWheel;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class MULTIHUB_API ARayCarBase : public APawn
{
	GENERATED_BODY()
	//Hit results of each suspension line trace
	TArray<FHitResult> hitResults;

	//whether wheels are contacting to ground or not
	TArray<bool> b_wheelsContact;

	// length of ray trace from at the begining of suspension to the bottom of the wheel. For each wheels
	TArray<float> rayLengths;

	TArray<UCameraComponent*> cameras;
	TArray<USpringArmComponent*> cameraBooms;
	TArray<FRotator> camerasStartRots;

	uint8 currentCamIndex;
	
	

	//Casting ray from each suspensions to end of the wheel
	/*
		generate hitresults 
	*/
	void StartSuspensions();

	void GenerateSuspensionLength(uint32 targetIndex);

	void ApplySuspensionForce(uint32 targetIndex);

	void ResetCameras();

	//input related
	void Steer(float value);
	void LookUp(float value);
	void TurnRight(float value);

protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly ,Category = "Vehicle", meta=(AllowPrivateAcess = "true"))
	UStaticMeshComponent* bodyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle", meta = (AllowPrivateAcess = "true"))
	UStaticMeshComponent* steeringWheelMesh;
	//Suspension placements.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle | Suspension", meta = (AllowPrivateAcess = "true"))
	USceneComponent* topLink_RF;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle | Suspension", meta = (AllowPrivateAcess = "true"))
	USceneComponent* topLink_LF;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle | Suspension", meta = (AllowPrivateAcess = "true"))
	USceneComponent* topLink_RB;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle | Suspension", meta = (AllowPrivateAcess = "true"))
	USceneComponent* topLink_LB;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle | Suspension", meta = (AllowPrivateAcess = "true"))
	uint8 wheelNumber;

	//Wheels number
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle | Wheel", meta = (AllowPrivateAcess = "true"))
	URayWheel* wheel_RF;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle | Wheel", meta = (AllowPrivateAcess = "true"))
	URayWheel* wheel_LF;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle | Wheel", meta = (AllowPrivateAcess = "true"))
	URayWheel* wheel_RB;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle | Wheel", meta = (AllowPrivateAcess = "true"))
	URayWheel* wheel_LB;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle", meta = (AllowPrivateAcess = "true"))
	//the array of suspension placements for each wheels,
	TArray<USceneComponent*> suspensions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle | Debug", meta = (AllowPrivateAcess = "true"))
	bool drawDebug;

	//Lengths of the final suspensions. Depends on hit result.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle", meta = (AllowPrivateAcess = "true"))
	TArray<float> suspensionLengths;

	// Lengths of the  suspensions from previous frame.
	TArray<float> PreSuspensionLengths;

	//Suspension Force power applied depending on suspension Lengths, Either downwards or upwards
	TArray<float> suspensionFPower;

	//Suspension struct for each suspension properties.
	UPROPERTY(EditDefaultsOnly, Category = "Vehicle | Suspension", meta = (AllowPrivateAcess = "true"))
	TArray<FSuspension> suspensionProperties;
	
	//cameras
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle | Camera", meta = (AllowPrivateAcess = "true"))
	UCameraComponent* innerCam;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle | Camera", meta = (AllowPrivateAcess = "true"))
	UCameraComponent* outerCam;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle | Camera", meta = (AllowPrivateAcess = "true"))
	USpringArmComponent* innerCamBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle | Camera", meta = (AllowPrivateAcess = "true"))
	USpringArmComponent* outerCamBoom;
	

	//steering
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle | Steering", meta = (AllowPrivateAcess = "true"))
	float maxWheelAngle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle | Steering", meta = (AllowPrivateAcess = "true"))
	float currentWheelAngle;

	float deltaTime;
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable, Category = "Vehicle | Camera")
	void SwapCameras();

public:	

	ARayCarBase();

	virtual void Tick(float DeltaTime) override;


	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
