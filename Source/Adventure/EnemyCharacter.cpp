// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Bullet.h"
#include "PlayerCharacter.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	Speed = 20.f;
	Health = 100.f;
	AttackTimeout = 1.f;
	TimeSinceLastAttack = 0.f;
	BulletLaunchInput = 2000.f;

	SightSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sight Sphere"));
	SightSphere->SetupAttachment(RootComponent);
	AttackRangeSphere= CreateDefaultSubobject<USphereComponent>(TEXT("Attack Range Sphere"));
	AttackRangeSphere->SetupAttachment(RootComponent);
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacterRef = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// calculate player location
	const FVector PlayerPosition = PlayerCharacterRef->GetActorLocation();
	const FVector DistanceDifference = PlayerPosition - GetActorLocation();
	const float DistanceToPlayer = DistanceDifference.Size();

	FRotator ToPlayerRotation = DistanceDifference.Rotation();
	ToPlayerRotation.Pitch = 0;

	if (!bIsDead)
	{
		RootComponent->SetWorldRotation(ToPlayerRotation);
	}

	if (DistanceToPlayer > SightSphere->GetScaledSphereRadius())
	{
		bIsAttacking = false;
		return;
	}

	if (IsInAttackRange(DistanceToPlayer) && !bIsDead)
	{
		if (TimeSinceLastAttack == 0)
		{
			Attack(PlayerCharacterRef);
		}

		TimeSinceLastAttack += DeltaTime;

		if (TimeSinceLastAttack > AttackTimeout)
		{
			TimeSinceLastAttack = 0.f;
		}

		return;
	}
}

void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Health -= DamageAmount;

	if (Health <= 0) {
	
		bIsDead = true;

	}

	return 0.0f;
}

void AEnemyCharacter::Attack(AActor* AttackTarget)
{
	if (BP_Bullet)
	{
		bIsAttacking = true;

		const FVector ForwardVector = GetActorForwardVector();
		FVector Nozzle = GetMesh()->GetBoneLocation("Neck1");

		Nozzle += ForwardVector * 55;

		FVector ToOpponent = AttackTarget->GetActorLocation() - Nozzle;
		ToOpponent.Normalize();

		ABullet* Arrow = GetWorld()->SpawnActor<ABullet>(BP_Bullet, Nozzle, RootComponent->GetComponentRotation());
		if (Arrow)
		{
			Arrow->GetCollisionSphere()->AddImpulse(ForwardVector * BulletLaunchInput);
		}
	}
}

bool AEnemyCharacter::IsInAttackRange(const float Distance)
{
	return Distance < AttackRangeSphere->GetScaledSphereRadius();
}

bool AEnemyCharacter::IsInSightRange(const float Distance)
{
	return Distance < SightSphere->GetScaledSphereRadius();
}

