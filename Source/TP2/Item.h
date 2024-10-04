// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionInterface.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class TP2_API AItem : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	AItem();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item")
	FTransform OriginalLocation;

	UFUNCTION()
	void OnDrop();

	virtual void BeginPlay() override;

	virtual void Interact(UPrimitiveComponent* HitComponent, ATP2Character* Player) override;
};
