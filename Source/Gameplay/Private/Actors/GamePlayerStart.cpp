// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/GamePlayerStart.h"

AGamePlayerStart::AGamePlayerStart(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PlayerStartStatus = GamePlayerStartStatus::None;
}

GamePlayerStartStatus AGamePlayerStart::GetPlayerStartStatus() const
{
	return PlayerStartStatus;
}

void AGamePlayerStart::SetPlayerStartStatus(GamePlayerStartStatus InPlayerStartStatus)
{
	PlayerStartStatus = InPlayerStartStatus;
}