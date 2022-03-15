// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class ADVENTURE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void OnAttack();
	
protected:
	virtual void BeginPlay() override;

	void MoveForward(float Amount);
	void MoveRight(float Amount);

	void Yaw(float Amount);
	void Pitch(float Amount);
	
private:
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	bool bIsWalking;
	
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	bool BHasKey;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	bool bDead;
	
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	bool bAttackStarted;

	bool bCanAttack;
	
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	float HealthPower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	float AttackTimeout;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	float TimeSinceLastStrike;
	
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	int Score;
	
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	UCapsuleComponent* TriggerCapsule;
};
