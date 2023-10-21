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
	float LifeTime;  // ���ƴ����ӵ��ɳ�ȥ������٣�Ҳ���Ǵ���Ŀ�����ģ�

	UPROPERTY(EditAnywhere, Category = "Teleport")
	float EffectTime;  // �ȴ���Ч������ɵ�ʱ��

	UPROPERTY(EditAnywhere, Category="Teleport")
	UParticleSystem* EndEffect;   // ����Ŀ�����Ч

	ASDTeleportProjectile();

protected:

	UFUNCTION()
	virtual void BeginPlay() override;

	void TeleportPlayer();  // ���ͽ�ɫ������ȷ�����͵㣬�����ӵ���Ч������Ŀ�����Ч���ȴ�

	void MovePawn(FTransform CurrentTrans);  // �������ͽ�ɫ�ĺ���

	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	FTimerHandle TH_ProjectileFlying;

	FTimerHandle TH_Effect;
};
