// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "ToonTanks/Pawn/PawnTank.h"
#include "ToonTanks/Pawn/PawnTurret.h"
#include "Kismet/GameplayStatics.h"


void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();
}

void ATankGameModeBase::HandleGameStart() 
{

	TargetTurrets = GetTargetTurretCount();
	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	GameStart();
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
	GameOver(PlayerWon);
}

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
	if (DeadActor == PlayerTank) 
	{
		PlayerTank->HandleDestruction();
		HandleGameOver(false);
	}
	else if (APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor)) 
	{
		DestroyedTurret->HandleDestruction();
		TargetTurrets--;
		if (TargetTurrets == 0) 
		{
			HandleGameOver(true);
		}
	}
}

int32 ATankGameModeBase::GetTargetTurretCount()
{
	TArray<AActor*> TurretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);
	return TurretActors.Num();
}
