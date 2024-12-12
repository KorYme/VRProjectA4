// Fill out your copyright notice in the Description page of Project Settings.


#include "VRProjectA4/Public/Glowstick.h"
#include "Components/PointLightComponent.h"

#pragma optimize("", off)
// Sets default values
AGlowstick::AGlowstick()
{
	
}

// Called when the game starts or when spawned
void AGlowstick::BeginPlay()
{
	Super::BeginPlay();
	CurrentTime = 0.f;
	GrabComponents = K2_GetComponentsByClass(USceneComponent::StaticClass());
	for (int i = GrabComponents.Num() - 1; i >= 0; i--) {
		if (GrabComponents[i]->GetName().Contains("MainMesh")) {
			MainMeshComponent = Cast<USkeletalMeshComponent>(GrabComponents[i]);
			GlowstickMaterial = MainMeshComponent->GetMaterial(1);
			//Cast<UMaterialInstanceDynamic>(GlowstickMaterial.Get())->SetScalarParameterValue("Glow Intensity", 0.f);
		}
		if (GrabComponents[i]->GetName().Contains("Upper")) {
			InitialGrabLocation = Cast<USceneComponent>(GrabComponents[i])->GetComponentLocation();
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
	TArray<FName> Bones = MainMeshComponent->GetAllSocketNames();
	for (int i = Bones.Num() - 1; i >= 0; i--) {
		if (Bones[i].ToString().Contains("bout_haut")) {
			UpperBones = Bones[i];
		}
	}
}

// Called every frame
void AGlowstick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsCracked && CurrentTime < TimeToMaxIntensity) {
		UpdateLightIntensity(DeltaTime);
	}
	if (IsCracked || !IsGrabbed) {
		return;
	}
	MoveBones();
	if (CheckIsCracked()) {
		Cracked();
	}
}

void AGlowstick::Grabbed()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, TEXT("Grabbed"));
	IsGrabbed = true;
}

void AGlowstick::OnRelease()
{
	Cast<USceneComponent>(GetGrabComponent("Upper"))->SetWorldLocation(InitialGrabLocation);
}

void AGlowstick::MoveBones()
{
	const USceneComponent* GrabComponentUpper = Cast<USceneComponent>(GetGrabComponent("Upper"));
	FVector OutVector;
	FRotator OutRotator;
	
	MainMeshComponent->TransformFromBoneSpace(UpperBones, GrabComponentUpper->K2_GetComponentLocation(), FRotator(0,0,0), OutVector, OutRotator);
}

UActorComponent* AGlowstick::GetGrabComponent(FString const &Name)
{
	for (int i = 0; i < GrabComponents.Num(); i++) {
		if (GrabComponents[i]->GetName().Contains(Name)) {
			return GrabComponents[i];
		}
	}
	return nullptr;
}

bool AGlowstick::CheckIsCracked() const
{
	for (int i = 0; i + 1 < GrabComponents.Num(); i++) {
		const USceneComponent* GrabComponentLower = Cast<USceneComponent>(GrabComponents[i]);
		const USceneComponent* GrabComponentUpper = Cast<USceneComponent>(GrabComponents[i + 1]);
		const float Distance = (GrabComponentUpper->GetComponentLocation() - GrabComponentLower->GetComponentLocation()).Size();
		
		if (Distance != InitialDistance) {
			return true;
		}
	}
	return false;
}

void AGlowstick::UpdateLightIntensity(const float DeltaTime)
{
	if (CurrentTime >= TimeToMaxIntensity) {
		return;
	}
	CurrentTime += DeltaTime;
	LightComponent->SetIntensity(FMath::Lerp(0.f, MaxIntensity, CurrentTime / TimeToMaxIntensity));
}

void AGlowstick::Cracked()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, TEXT("Cracked"));
	IsCracked = true;
	PrimaryActorTick.bCanEverTick = false;
	//Cast<UMaterialInstanceDynamic>(GlowstickMaterial.Get())->SetScalarParameterValue("Glow Intensity", 3.f);
	//LightComponent->SetIntensity(MaxIntensity);
}

void AGlowstick::Shake()
{
	CurrentTime += ShakeValue;
}

void AGlowstick::CustomGrab_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("CustomGrab_Implementation"));
	Grabbed();
}
#pragma optimize("", on)