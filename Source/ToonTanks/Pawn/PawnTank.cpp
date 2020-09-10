// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"
#include "Engine/World.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

APawnTank::APawnTank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Player"));
	CameraComp->SetupAttachment(SpringArm);

	SpringArm->TargetArmLength = 600.f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraLagSpeed = 5.f;
	SpringArm->CameraRotationLagSpeed = 5.f;
}

// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();
	PlayerControllerRef = Cast<APlayerController>(GetController());
}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
	Rotate();
	
	if(PlayerControllerRef)
	{
		FHitResult TraceHitResult;
		PlayerControllerRef->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, TraceHitResult);
		FVector HitLocation = TraceHitResult.ImpactPoint;
		RotateTurretFunction(HitLocation);
	}

}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMoveInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotateInput);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APawnTank::Fire);

}

void APawnTank::Move()
{
	AddActorLocalRotation(RotationDirection);
}
void APawnTank::Rotate()
{
	AddActorLocalOffset(MoveDirection, true);
}
void APawnTank::CalculateMoveInput(float Value)
{
	MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0.f, 0.f);
}
void APawnTank::CalculateRotateInput(float Value)
{
	float RotateAmount = Value * RotationSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator Rotation = FRotator(0.f, RotateAmount, 0.f);
	RotationDirection = FQuat(Rotation);
}

void APawnTank::HandleDestruction()
{
	Super::HandleDestruction();
	// Hide Player. TODO - Create new function to handle this. 
}
