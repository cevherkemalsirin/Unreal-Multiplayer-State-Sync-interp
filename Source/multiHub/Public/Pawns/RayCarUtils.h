// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RayCarUtils.generated.h"


USTRUCT(BlueprintType)
struct FSuspension {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float restLength = 50.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float travel = 20.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float stiffnes = 500.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float dumping = 10.0f;
};


class MULTIHUB_API RayCarUtils
{
public:
	RayCarUtils();
	~RayCarUtils();
};
