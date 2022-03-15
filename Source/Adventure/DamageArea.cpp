// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageArea.h"
#include "Components/BoxComponent.h"

ADamageArea::ADamageArea()
{
	PrimaryActorTick.bCanEverTick = true;


	DamageBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Damage Box"));
	RootComponent = DamageBoxComponent;

	DamageBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ADamageArea::OnBeginOverlap);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(DamageBoxComponent);
}

void ADamageArea::OnBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void ADamageArea::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADamageArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

