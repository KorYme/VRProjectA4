// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Glowstick.generated.h"

class UPointLightComponent;

#pragma optimize("", off)
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
	
	UPROPERTY(BlueprintReadWrite, Category = "Glowstick")
	bool IsGrabbed = false;

	UPROPERTY(BlueprintReadOnly, Category = "Glowstick")
	bool IsCracked = false;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Glowstick")
	float MaxIntensity = 100.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Glowstick")
	float TimeToMaxIntensity = 5.f;

	UPROPERTY(BlueprintReadWrite)
	float CurrentTime = 0.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Glowstick")
	float ShakeValue = 0.01f;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Glowstick")
	FVector InitialGrabLocation;
	
	UPROPERTY(BlueprintReadOnly, Category = "Glowstick")
	FName UpperBones;
	
	UPROPERTY(BlueprintReadOnly, Category = "Glowstick")
	TObjectPtr<USkeletalMeshComponent> MainMeshComponent;
	
	UPROPERTY(BlueprintReadWrite)
	TSoftObjectPtr<UMaterial> GlowstickMaterial;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Glowstick")
	TObjectPtr<UPointLightComponent> LightComponent;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Glowstick")
	TArray<UActorComponent*> GrabComponents;
	
	UFUNCTION(BlueprintCallable, Category = "Glowstick")
	void Grabbed();

	UFUNCTION(BlueprintCallable, Category = "Glowstick")
	void OnRelease();
	
	UFUNCTION(BlueprintCallable, Category = "Glowstick")
	void MoveBones();
	
	UFUNCTION(BlueprintCallable, Category = "Glowstick")
	bool CheckIsCracked() const;
	
	UFUNCTION(BlueprintCallable, Category = "Glowstick")
	void Cracked();

	UFUNCTION(BlueprintCallable, Category = "Glowstick")
	void Shake();
	
	UFUNCTION(BlueprintCallable, Category = "Glowstick")
	void UpdateLightIntensity(const float DeltaTime);
	
	UFUNCTION(BlueprintCallable, Category = "Glowstick")
	UActorComponent* GetGrabComponent(FString const &Name);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Glowstick")
	void CustomGrab();
	
	UFUNCTION(BlueprintCallable, Category = "Glowstick")
	TSoftObjectPtr<UMaterial> GetGlowMaterial() const { return GlowstickMaterial; }

	UFUNCTION(BlueprintCallable, Category = "Glowstick")
	void SetGlowMaterial(TSoftObjectPtr<UMaterial> Material) { GlowstickMaterial = Material; }

	UFUNCTION(BlueprintCallable, Category = "Glowstick")
	void SetPointLight(UPointLightComponent* Target) { LightComponent = Target; }
};
#pragma optimize("", on)