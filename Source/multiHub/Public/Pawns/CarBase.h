// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CarBase.generated.h"

UCLASS()
class MULTIHUB_API ACarBase : public APawn
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, Category = "Camera", meta = (AllowPrivateAcess = "true"))
	class USpringArmComponent* springArm;
	UPROPERTY(VisibleAnywhere, Category = "Camera", meta=(AllowPrivateAcess = "true"))
	class UCameraComponent* camera;
	UPROPERTY(VisibleAnywhere, Category = "Mesh", meta = (AllowPrivateAcess = "true"))
	USkeletalMeshComponent* mainMesh;


	FVector velocity;

	void MoveForward(float value);
protected:
	virtual void BeginPlay() override;


public:	
	ACarBase();
	virtual void Tick(float DeltaTime) override;



	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
