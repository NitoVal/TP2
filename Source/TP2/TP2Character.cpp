// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP2Character.h"
#include "TP2Projectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "InteractionInterface.h"
#include "Item.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ATP2Character

ATP2Character::ATP2Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	HandPosition = CreateDefaultSubobject<USceneComponent>("HandPosition");
	HandPosition->SetupAttachment(FirstPersonCameraComponent);
	
	HeldItem = nullptr;
	CurrentInteractable = nullptr;
}

void ATP2Character::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

void ATP2Character::Tick(float DeltaSeconds)
{
}

void ATP2Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATP2Character::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATP2Character::Look);

		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ATP2Character::Interact);
		//Drop
		EnhancedInputComponent->BindAction(DropAction, ETriggerEvent::Triggered, this, &ATP2Character::DropItemInput);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void ATP2Character::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ATP2Character::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ATP2Character::Interact()
{
	const FVector StartLocation = FirstPersonCameraComponent->GetComponentTransform().GetLocation();
	const FVector EndLocation = StartLocation + FirstPersonCameraComponent->GetForwardVector() * 200;

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);
	
	FHitResult HitResult;
	bool bHit = GetWorld()->LineTraceSingleByObjectType(HitResult,
		StartLocation,
		EndLocation,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldDynamic),
		CollisionQueryParams
	);

	if (bHit && HitResult.GetActor())
	{
		AActor* HitActor = HitResult.GetActor();
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		if (HitActor->Implements<UInteractionInterface>())
		{
			IInteractionInterface* InteractionActor = Cast<IInteractionInterface>(HitActor);
			if (InteractionActor && HitComponent)
			{
				InteractionActor->Interact(HitComponent, this);
			}
		}
	}
}

void ATP2Character::PickupItem(AItem* Item)
{
	if (!HeldItem)
	{
		HeldItem = Item;
		HeldItem->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
		HeldItem->SetActorLocation(HandPosition->GetComponentLocation());
		HeldItem->SetActorRotation(FRotator(0,-90,0));
	}
}

void ATP2Character::DropItemInput()
{
	DropItem();
}

void ATP2Character::DropItem()
{
	if (HeldItem)
	{
		HeldItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		HeldItem->OnDrop();
		HeldItem = nullptr;
	}
}
