// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupItem.h"

#include "Components/SphereComponent.h"

APickupItem::APickupItem()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	RootComponent = MeshComponent;
	
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
	CollisionSphere->SetupAttachment(MeshComponent);
}

void APickupItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void APickupItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

