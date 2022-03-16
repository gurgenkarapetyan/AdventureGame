// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class USphereComponent;
class APlayerCharacter;

UCLASS()
class ADVENTURE_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();
	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
	void Attack(AActor* AttackTarget);

	bool IsInAttackRange(const float Distance);

	bool IsInSightRange(const float Distance);
	
protected:
	virtual void BeginPlay() override;

private:
	APlayerCharacter* PlayerCharacterRef;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	float Speed;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	float Health;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	float AttackDamage;
	
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	float AttackTimeout;
	
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	float TimeSinceLastAttack;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	float BulletLaunchInput;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	bool bIsAttacking;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	bool bIsDead;
	
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	UClass* BP_Bullet;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	USphereComponent* SightSphere;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	USphereComponent* AttackRangeSphere;
};
