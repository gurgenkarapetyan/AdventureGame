// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakableCrate.h"

#include "PickupItem.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"

ABreakableCrate::ABreakableCrate()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	RootComponent = CollisionBox;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(CollisionBox);

	Explosion = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Explosion"));
	Explosion->AttachToComponent(CollisionBox, FAttachmentTransformRules::KeepRelativeTransform, FName(""));

	Health = 100.f;
}

void ABreakableCrate::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABreakableCrate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ABreakableCrate::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Health -= DamageAmount;

	if (Health <= 0)
	{
		LootDrop();

		Explosion->ToggleActive();
		MeshComponent->ToggleVisibility(false);

		SetLifeSpan(0.1);
	}
	
	return 0.f;
}

void ABreakableCrate::LootDrop()
{
	if (FMath::RandRange(0, 10) > 5)
	{
		const FVector Up = GetActorUpVector();
		FVector Offset = CollisionBox->GetComponentLocation();
		Offset += Up;

		APickupItem* Pickup = GetWorld()->SpawnActor<APickupItem>(BP_PickupItem, Offset, RootComponent->GetComponentRotation());
	}
}