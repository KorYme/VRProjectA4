// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RopeTest.generated.h"

UCLASS()
class VRPROJECTA4_API ARopeTest : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARopeTest();

protected:
	UPROPERTY(EditAnywhere)
	float Height;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
