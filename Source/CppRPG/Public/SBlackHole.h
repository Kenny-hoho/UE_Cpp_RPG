// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SBaseProjectile.h"
#include "SBlackHole.generated.h"

class URadialForceComponent;
class USphereComponent;

UCLASS()
class CPPRPG_API ASBlackHole : public ASBaseProjectile
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* ForceComp;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* DestroySphereComp;

	// 生命周期
	UPROPERTY(EditAnywhere)
	float LifeTime;

	// 延迟销毁被吸引的Actor
	UPROPERTY(EditAnywhere)
	float DestroyDelay;

	ASBlackHole();

	virtual void BeginPlay() override;

	UFUNCTION()
	void DestroyPulledActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:

	FTimerHandle Destroy_TimerHandle;

	FTimerHandle DestroySelf_TimerHandle;

	void DestroyActor(AActor* TargetActor);
};
