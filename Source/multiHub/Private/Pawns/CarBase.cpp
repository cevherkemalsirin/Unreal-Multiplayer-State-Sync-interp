// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/CarBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
//#include "Components/SkeletalMeshComponent.h"


ACarBase::ACarBase()
{
	PrimaryActorTick.bCanEverTick = true;
	mainMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh Component"));

	// Create a camera boom (pulls in towards the player if there is a collision)
	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	springArm->SetupAttachment(mainMesh);
	springArm->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	springArm->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	camera->SetupAttachment(springArm, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	camera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

}


void ACarBase::BeginPlay()
{
	Super::BeginPlay();
	
}


void ACarBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector offset = velocity * DeltaTime;
	AddActorWorldOffset(offset, true);
}


void ACarBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACarBase::MoveForward);
}


void ACarBase::MoveForward(float value)
{
	//20 is cm, to make it meter multiply with 100 so below code means 20 meter per second
	velocity = GetActorForwardVector() * 2000.0f * value;

}