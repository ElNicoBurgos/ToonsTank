// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"


APawnTurret::APawnTurret()
{

}

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);
	
}

void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APawnTurret::CheckFireCondition() 
{
	// If Player == null || is Dead THEN BAIL!!

	// IF Player IS in range THEN FIRE!! 

	UE_LOG(LogTemp, Warning, TEXT("Fire Condition checked"));
}
