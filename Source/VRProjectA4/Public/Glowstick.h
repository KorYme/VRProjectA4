// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Glowstick.generated.h"

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
	UPROPERTY()
	bool IsGrabbed = false;

	UPROPERTY()
	bool IsCracked = false;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Glowstick")
	float MaxIntensity = 100.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Glowstick")
	float TimeToMaxIntensity = 5.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Glowstick")
	UMaterial *GlowstickMaterial;	

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<TObjectPtr<USceneComponent>> GrabComponents;

	UFUNCTION(BlueprintCallable, Category = "Glowstick")
	void Grabbed();

	UFUNCTION(BlueprintCallable, Category = "Glowstick")
	bool CheckIsCracked();
	
	UFUNCTION(BlueprintCallable, Category = "Glowstick")
	void Cracked();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Glowstick")
	void CustomGrab();
};
