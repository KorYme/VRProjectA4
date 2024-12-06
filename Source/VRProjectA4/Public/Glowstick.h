// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Glowstick.generated.h"

class UPointLightComponent;

UCLASS()
class VRPROJECTA4_API AGlowstick : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGlowstick();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Glowstick")
	float InitialDistance = 0.f;
	
	UPROPERTY(BlueprintReadOnly, Category = "Glowstick")
	bool IsGrabbed = false;

	UPROPERTY(BlueprintReadOnly, Category = "Glowstick")
	bool IsCracked = false;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Glowstick")
	float MaxIntensity = 100.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Glowstick")
	float TimeToMaxIntensity = 5.f;

	UPROPERTY(BlueprintReadOnly, Category = "Glowstick")
	TObjectPtr<USkeletalMeshComponent> MainMeshComponent;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Glowstick")
	TSoftObjectPtr<UMaterial> GlowstickMaterial;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Glowstick")
	TObjectPtr<UPointLightComponent> LightComponent;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Glowstick")
	TArray<UActorComponent*> GrabComponents;
	
	UFUNCTION(BlueprintCallable, Category = "Glowstick")
	void Grabbed();

	UFUNCTION(BlueprintCallable, Category = "Glowstick")
	bool CheckIsCracked() const;
	
	UFUNCTION(BlueprintCallable, Category = "Glowstick")
	void Cracked();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Glowstick")
	void CustomGrab();

	UFUNCTION(BlueprintCallable, Category = "Glowstick")
	TSoftObjectPtr<UMaterial> GetGlowMaterial() const { return GlowstickMaterial; }

	UFUNCTION(BlueprintCallable, Category = "Glowstick")
	void SetGlowMaterial(TSoftObjectPtr<UMaterial> Material) { GlowstickMaterial = Material; }
};
