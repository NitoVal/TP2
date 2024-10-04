// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = false;
	bIsScrewdriver = false;
}

void AItem::BeginPlay()
{
	OriginalLocation = GetActorTransform();
}
void AItem::OnDrop()
{
	SetActorTransform(OriginalLocation);
}


