// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class ADVENTURE_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	ABullet();
	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FORCEINLINE UShapeComponent* GetCollisionSphere() const { return CollisionSphere; }
protected:
	virtual void BeginPlay() override;


private:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	float Damage;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	UShapeComponent* CollisionSphere;
	
	
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* MeshComponent;
};
