// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SBaseProjectile.h"
#include "SDTeleportProjectile.generated.h"


UCLASS()
class CPPRPG_API ASDTeleportProjectile : public ASBaseProjectile
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, Category="Teleport")
	float LifeTime;  // 控制传送子弹飞出去多久销毁（也就是传送目标在哪）

	UPROPERTY(EditAnywhere, Category = "Teleport")
	float EffectTime;  // 等待特效播放完成的时间

	UPROPERTY(EditAnywhere, Category="Teleport")
	UParticleSystem* EndEffect;   // 传送目标点特效

	ASDTeleportProjectile();

protected:

	UFUNCTION()
	virtual void BeginPlay() override;

	void TeleportPlayer();  // 传送角色，包含确定传送点，销毁子弹特效，播放目标点特效并等待

	void MovePawn(FTransform CurrentTrans);  // 真正传送角色的函数

	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	FTimerHandle TH_ProjectileFlying;

	FTimerHandle TH_Effect;
};
