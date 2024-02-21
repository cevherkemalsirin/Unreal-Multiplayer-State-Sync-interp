// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MT_MovingPlatform.generated.h"

UENUM(BlueprintType)
enum class EMoveStyle : uint8
{
	EMS_Pingpong,
	EMS_Single,
	EMS_Infinite
};

UCLASS()
class MULTIHUB_API AMT_MovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
	UStaticMeshComponent* mainMeshComp;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"),meta=(MakeEditWidget = "true"))
	FVector targetLocation;
	

	FVector startLocation;
	FVector globalTargetLocation;

	void MovePlatform();
public:
	AMT_MovingPlatform();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	EMoveStyle moveStyle;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	FORCEINLINE void SetCanMove(bool move) { this->bCanMove = move; };

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere ,BlueprintReadWrite, Category = "Movement")
	bool bCanMove;
};
