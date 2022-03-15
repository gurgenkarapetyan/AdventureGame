// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Bullet.h"
#include "Components/CapsuleComponent.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	AttackTimeout = 1.5;
	TimeSinceLastStrike = 0.f;
	BulletLaunchImpulse = 5000.0f;
	bCanAttack = true;
	bAttackStarted = false;

	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Component"));
	TriggerCapsule->InitCapsuleSize(55.0f, 96.0f);
	TriggerCapsule->SetCollisionProfileName(TEXT("Trigger"));
	TriggerCapsule->SetupAttachment(RootComponent);

	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnOverlapBegin);
}

void APlayerCharacter::OnOverlapBegin(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeSinceLastStrike += DeltaTime;

	if (TimeSinceLastStrike > AttackTimeout && !bCanAttack)
	{
		bCanAttack = true;
		TimeSinceLastStrike = 0.f;
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Yaw", this, &APlayerCharacter::Yaw);
	PlayerInputComponent->BindAxis("Pitch", this, &APlayerCharacter::Pitch);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::Jump);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &APlayerCharacter::OnAttack);
}

void APlayerCharacter::MoveForward(float Amount)
{
	if (Controller && Amount)
	{
		bIsWalking = true;

		FVector ForwardVector = GetActorForwardVector();
		AddMovementInput(ForwardVector, Amount);
	}

	if (Amount == 0)
	{
		bIsWalking = false;
	}
}

void APlayerCharacter::MoveRight(float Amount)
{
	if (Controller && Amount)
	{
		FVector RightVector = GetActorRightVector();
		AddMovementInput(RightVector, Amount);
	}
}

void APlayerCharacter::Yaw(float Amount)
{
	AddControllerYawInput(200.f * Amount * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::Pitch(float Amount)
{
	AddControllerPitchInput(200.f * Amount * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::OnAttack()
{
	bAttackStarted = true;
	if (bCanAttack)
	{
		const FVector ForwardVector = GetActorForwardVector();
		FVector Nozzle = GetMesh()->GetBoneLocation("ArmR3");

		Nozzle += ForwardVector * 55.f;

		ABullet* Bullet = GetWorld()->SpawnActor<ABullet>(BP_FireBall, Nozzle, RootComponent->GetComponentRotation());
		bCanAttack = false;

		if (Bullet)
		{
			Bullet->GetCollisionSphere()->AddImpulse(ForwardVector * BulletLaunchImpulse);
		}
	}
}


float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

