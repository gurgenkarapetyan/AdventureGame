// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupItem.generated.h"

class USphereComponent;

UCLASS()
class ADVENTURE_API APickupItem : public AActor
{
	GENERATED_BODY()
	
public:	
	APickupItem();

	virtual void Tick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	USphereComponent* CollisionSphere;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* MeshComponent;
};
