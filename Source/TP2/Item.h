// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class TP2_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	bool bIsScrewdriver;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item")
	FTransform OriginalLocation;

	UFUNCTION()
	void OnDrop();

	virtual void BeginPlay() override;
};
