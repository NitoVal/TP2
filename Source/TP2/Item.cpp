// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

#include "TP2Character.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AItem::BeginPlay()
{
	OriginalLocation = GetActorTransform();
}

void AItem::Interact(UPrimitiveComponent* HitComponent, ATP2Character* Player)
{
	Player->PickupItem(this);
}

void AItem::OnDrop()
{
	SetActorTransform(OriginalLocation);
}


