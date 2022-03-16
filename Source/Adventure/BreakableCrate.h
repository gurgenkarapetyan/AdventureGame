// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BreakableCrate.generated.h"

class UBoxComponent;
class UParticleSystemComponent;

UCLASS()
class ADVENTURE_API ABreakableCrate : public AActor
{
	GENERATED_BODY()
	
public:	
	ABreakableCrate();

	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	virtual void BeginPlay() override;

	void LootDrop();

private:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	float Health;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	UClass* BP_PickupItem;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	UBoxComponent* CollisionBox;
	
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	UParticleSystemComponent* Explosion;
};
