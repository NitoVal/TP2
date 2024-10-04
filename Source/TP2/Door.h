// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

class AGenerator;

UCLASS()
class TP2_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:
	ADoor();

	UPROPERTY(EditAnywhere, Category="Requirements")
	TArray<AGenerator*> Gens;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
};
