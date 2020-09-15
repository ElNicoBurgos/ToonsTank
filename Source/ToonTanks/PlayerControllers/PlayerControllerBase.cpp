// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"

APlayerControllerBase::APlayerControllerBase() {
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void APlayerControllerBase::SetPlayerEnabledState(bool SetPlayerEnabled) 
{
	if (SetPlayerEnabled) 
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}

	bShowMouseCursor = SetPlayerEnabled;
}