// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

#include "Generator.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	int gActive = 0;
	for (auto g : Gens)
	{
		if (g->bIsActive)
			gActive++;
	}
	if (gActive == Gens.Num())
		Destroy();
}

