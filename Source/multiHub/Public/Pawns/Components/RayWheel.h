// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RayWheel.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MULTIHUB_API URayWheel : public UStaticMeshComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Wheel", meta = (AllowPrivateAcess = "true"))
	float mass;
	UPROPERTY(VisibleAnywhere, Category = "Wheel", meta = (AllowPrivateAcess = "true"))
	float radius;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	URayWheel();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FORCEINLINE float GetRadius()const { return GetStaticMesh()->GetBounds().SphereRadius; };
		
};
