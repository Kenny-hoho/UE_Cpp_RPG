// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SBaseProjectile.generated.h"

class UParticleSystemComponent;
class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class CPPRPG_API ASBaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASBaseProjectile();

	UPROPERTY(EditAnywhere)
	float ProjectileMoveSpeed;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* EffectComp;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* MovementComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;

};
