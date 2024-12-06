// Fill out your copyright notice in the Description page of Project Settings.


#include "VRProjectA4/Public/Glowstick.h"
#include "Components/PointLightComponent.h"

#pragma optimize("", off)
// Sets default values
AGlowstick::AGlowstick()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AGlowstick::BeginPlay()
{
	Super::BeginPlay();
	GrabComponents = K2_GetComponentsByClass(USceneComponent::StaticClass());
	for (int i = GrabComponents.Num() - 1; i >= 0; i--) {
		if (Cast<UPointLightComponent>(GrabComponents[i])) {
			LightComponent = Cast<UPointLightComponent>(GrabComponents[i]);
			LightComponent->SetIntensity(0.f);
		}
		if (GrabComponents[i]->GetName().Contains("MainMesh")) {
			MainMeshComponent = Cast<UStaticMeshComponent>(GrabComponents[i]);
			GlowstickMaterial = MainMeshComponent->GetMaterial(0);
			Cast<UMaterialInstanceDynamic>(GlowstickMaterial.Get())->SetScalarParameterValue("Glow Intensity", 0.f);
		}
		if (!GrabComponents[i]->GetName().Contains("GrabComponent")) {
			GrabComponents.RemoveAt(i);
		}
	}
	for (int i = 0; i + 1 < GrabComponents.Num(); i++) {
		const USceneComponent* GrabComponentLower = Cast<USceneComponent>(GrabComponents[i]);
		const USceneComponent* GrabComponentUpper = Cast<USceneComponent>(GrabComponents[i + 1]);
		
		InitialDistance = (GrabComponentUpper->GetComponentLocation() - GrabComponentLower->GetComponentLocation()).Size();
	}
}

// Called every frame
void AGlowstick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CheckIsCracked()) {
		Cracked();
	}
}

void AGlowstick::Grabbed()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Grabbed"));
	PrimaryActorTick.bCanEverTick = true;
	IsGrabbed = true;
}

bool AGlowstick::CheckIsCracked() const
{
	for (int i = 0; i + 1 < GrabComponents.Num(); i++) {
		const USceneComponent* GrabComponentLower = Cast<USceneComponent>(GrabComponents[i]);
		const USceneComponent* GrabComponentUpper = Cast<USceneComponent>(GrabComponents[i + 1]);
		const float Distance = (GrabComponentUpper->GetComponentLocation() - GrabComponentLower->GetComponentLocation()).Size();
		
		if (Distance < InitialDistance) {
			return true;
		}
	}
	return false;
}

void AGlowstick::Cracked()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, TEXT("Cracked"));
	IsCracked = true;
	PrimaryActorTick.bCanEverTick = false;
	Cast<UMaterialInstanceDynamic>(GlowstickMaterial.Get())->SetScalarParameterValue("Glow Intensity", 3.f);
	LightComponent->SetIntensity(MaxIntensity);
}

void AGlowstick::CustomGrab_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("CustomGrab_Implementation"));
	Grabbed();
}
#pragma optimize("", on)