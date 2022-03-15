// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageArea.generated.h"

class UBoxComponent;

UCLASS()
class ADVENTURE_API ADamageArea : public AActor
{
	GENERATED_BODY()
	
public:	
	ADamageArea();
		
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	float Damage;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	UBoxComponent* DamageBoxComponent;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* MeshComponent;
	
};
