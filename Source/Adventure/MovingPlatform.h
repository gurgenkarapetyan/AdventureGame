// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class ADVENTURE_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	AMovingPlatform();
	
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void TogglePlatform();

private:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	float SpeedOfPlatform;
	
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	float FirstEnd;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	float SecondEnd;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	bool bIsDiagonal;
	
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	bool bIsActivatable;

	bool bActivated;

	
};
