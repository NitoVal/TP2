// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionInterface.h"
#include "GameFramework/Actor.h"
#include "Generator.generated.h"

UCLASS()
class TP2_API AGenerator : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGenerator();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Component")
	USceneComponent* DefaultSceneRoot;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Component")
	UStaticMeshComponent* Screw1;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Component")
	UStaticMeshComponent* Screw2;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Component")
	UStaticMeshComponent* Screw3;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Component")
	UStaticMeshComponent* Screw4;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Activation")
	bool bIsActive;

	void ActivateGenerator();

	void Interact() override;
};
