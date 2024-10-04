// Fill out your copyright notice in the Description page of Project Settings.


#include "Generator.h"

#include "Item.h"

AGenerator::AGenerator()
{
	PrimaryActorTick.bCanEverTick = false;
	
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>("DefaultSceneRoot");
	RootComponent = DefaultSceneRoot;

	Box = CreateDefaultSubobject<UStaticMeshComponent>("Box");
	Box->SetupAttachment(RootComponent);
	
	Panel = CreateDefaultSubobject<USceneComponent>("Panel");
	Panel->SetupAttachment(RootComponent);
	
	Cover = CreateDefaultSubobject<UStaticMeshComponent>("Cover");
	Cover->SetupAttachment(Panel);

	Screw1 = CreateDefaultSubobject<UStaticMeshComponent>("Screw1");
	Screw1->SetupAttachment(Panel);
	Screw1->ComponentTags.Add(FName("Screw"));
	
	Screw2 = CreateDefaultSubobject<UStaticMeshComponent>("Screw2");
	Screw2->SetupAttachment(Panel);
	Screw2->ComponentTags.Add(FName("Screw"));
	
	Screw3 = CreateDefaultSubobject<UStaticMeshComponent>("Screw3");
	Screw3->SetupAttachment(Panel);
	Screw3->ComponentTags.Add(FName("Screw"));
	
	Screw4 = CreateDefaultSubobject<UStaticMeshComponent>("Screw4");
	Screw4->SetupAttachment(Panel);
	Screw4->ComponentTags.Add(FName("Screw"));
}

void AGenerator::BeginPlay()
{
	ScrewCounter = 0;
	bIsActive = false;
}
void AGenerator::Interact(UPrimitiveComponent* HitComponent, ATP2Character* Player)
{
	AItem* PlayerItem = Player->HeldItem;
	if (HitComponent->ComponentHasTag("Screw") && PlayerItem)
	{
		if (PlayerItem->ActorHasTag("Screwdriver"))
		{
			FDetachmentTransformRules DetachRules(EDetachmentRule::KeepRelative, EDetachmentRule::KeepRelative, EDetachmentRule::KeepWorld, true);
			HitComponent->DetachFromComponent(DetachRules);
			HitComponent->SetSimulatePhysics(true);
			HitComponent->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
		
			ScrewCounter++;
			if (ScrewCounter == 4)
			{
				Cover->DetachFromComponent(DetachRules);
				Cover->SetSimulatePhysics(true);
				Cover->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
			}
		}
	}
	if (PlayerItem)
	{
		if (ScrewCounter == 4 && PlayerItem->ActorHasTag("Battery"))
		{
			//Remove the battery from inventory
			PlayerItem->OriginalLocation = this->GetTransform();
			PlayerItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			Player->DropItem();
			bIsActive = true;
		}
	}
}

