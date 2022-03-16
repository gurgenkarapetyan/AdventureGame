// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMovingPlatform::TogglePlatform()
{
	bIsActivatable = false;
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsActivatable)
	{
		FVector ActorLocation = GetActorLocation();
		ActorLocation.Y += SpeedOfPlatform;

		if (bIsDiagonal)
		{
			ActorLocation.Z += SpeedOfPlatform;
		}
		
		SetActorLocation(ActorLocation);
		if (ActorLocation.Y >= FirstEnd)
			{
			SpeedOfPlatform *= -1.0f;
		}

		if (ActorLocation.Y <= SecondEnd)
		{
			SpeedOfPlatform *= -1.0f;
		}
	}
	else if (bIsActivatable && bActivated)
	{
		FVector ActorLocation = GetActorLocation();

		ActorLocation.Y += SpeedOfPlatform;

		SetActorLocation(ActorLocation);
		if (ActorLocation.Y >= FirstEnd)
		{
			SpeedOfPlatform *= -1.0f;
		}

		if (ActorLocation.Y <= SecondEnd)
		{
			SpeedOfPlatform *= -1.0f;
		}

	}
}

