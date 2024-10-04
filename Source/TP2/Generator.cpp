// Fill out your copyright notice in the Description page of Project Settings.


#include "Generator.h"

AGenerator::AGenerator()
{
	PrimaryActorTick.bCanEverTick = false;
	bIsActive = false;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>("DefaultSceneRoot");
	RootComponent = DefaultSceneRoot;
	
	Screw1 = CreateDefaultSubobject<UStaticMeshComponent>("Screw1");
	Screw1->SetupAttachment(RootComponent);
	
	Screw2 = CreateDefaultSubobject<UStaticMeshComponent>("Screw2");
	Screw2->SetupAttachment(RootComponent);
	
	Screw3 = CreateDefaultSubobject<UStaticMeshComponent>("Screw3");
	Screw3->SetupAttachment(RootComponent);
	
	Screw4 = CreateDefaultSubobject<UStaticMeshComponent>("Screw4");
	Screw4->SetupAttachment(RootComponent);
}

void AGenerator::ActivateGenerator()
{
	bIsActive = true;
	Screw1->SetSimulatePhysics(true);
	Screw2->SetSimulatePhysics(true);
	Screw3->SetSimulatePhysics(true);
	Screw4->SetSimulatePhysics(true);
}

void AGenerator::Interact()
{
	ActivateGenerator();
}
