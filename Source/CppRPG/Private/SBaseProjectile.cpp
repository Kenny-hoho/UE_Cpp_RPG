// Fill out your copyright notice in the Description page of Project Settings.


#include "SBaseProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "SCharacter.h"

// Sets default values
ASBaseProjectile::ASBaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMoveSpeed = 500.0f;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComp");
	MovementComp->ProjectileGravityScale = 0.0f;

}

void ASBaseProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	FVector ProjectileVelocity = FVector(0, 0, 0);

	APawn* OwnerPawn = GetInstigator();

	ASCharacter* OwnerChar = Cast<ASCharacter>(OwnerPawn);
	if (OwnerChar) {
		ProjectileVelocity = (OwnerChar->AimTarget - GetActorLocation()).GetSafeNormal() * ProjectileMoveSpeed;
	}

	MovementComp->Velocity = ProjectileVelocity;
}

// Called when the game starts or when spawned
void ASBaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASBaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



