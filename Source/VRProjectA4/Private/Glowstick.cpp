// Fill out your copyright notice in the Description page of Project Settings.


#include "VRProjectA4/Public/Glowstick.h"


// Sets default values
AGlowstick::AGlowstick()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AGlowstick::BeginPlay()
{
	Super::BeginPlay();
	GetComponents(GrabComponents);
}

// Called every frame
void AGlowstick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGlowstick::Grabbed()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Grabbed"));
	PrimaryActorTick.bCanEverTick = true;
	IsGrabbed = true;
}

bool AGlowstick::CheckIsCracked()
{
	return true;
}

void AGlowstick::Cracked()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, TEXT("Cracked"));
	IsCracked = true;
}

void AGlowstick::CustomGrab_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("CustomGrab_Implementation"));
	Grabbed();
}

