// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionInterface.h"
#include "TP2Character.h"
#include "GameFramework/Actor.h"
#include "Generator.generated.h"

UCLASS()
class TP2_API AGenerator : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGenerator();
	UPROPERTY(VisibleAnywhere, Category="Component")
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere, Category="Component")
	UStaticMeshComponent* Box;
	
	UPROPERTY(VisibleAnywhere, Category="Component")
	USceneComponent* Panel;
	
	UPROPERTY(VisibleAnywhere, Category="Component")
	UStaticMeshComponent* Screw1;
	
	UPROPERTY(VisibleAnywhere, Category="Component")
	UStaticMeshComponent* Screw2;
	
	UPROPERTY(VisibleAnywhere, Category="Component")
	UStaticMeshComponent* Screw3;
	
	UPROPERTY(VisibleAnywhere, Category="Component")
	UStaticMeshComponent* Screw4;
	
	UPROPERTY(VisibleAnywhere, Category="Component")
	UStaticMeshComponent* Cover;
	
	UPROPERTY(VisibleAnywhere, Category="Generator | Screws")
	int ScrewCounter;

	UPROPERTY(VisibleAnywhere, Category="Generator | State")
	bool bIsActive;
	
	virtual void Interact(UPrimitiveComponent* HitComponent, ATP2Character* Player) override;

	virtual void BeginPlay() override;
};
