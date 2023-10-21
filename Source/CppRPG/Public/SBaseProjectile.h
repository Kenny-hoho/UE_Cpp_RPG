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

	UPROPERTY(EditAnywhere, Category="Attribute of Base Projectile")
	float ProjectileMoveSpeed;

	UPROPERTY(VisibleAnywhere, Category = "Attribute of Base Projectile")
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, Category = "Attribute of Base Projectile")
	UParticleSystemComponent* EffectComp;

	UPROPERTY(VisibleAnywhere, Category = "Attribute of Base Projectile")
	UProjectileMovementComponent* MovementComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;

};
