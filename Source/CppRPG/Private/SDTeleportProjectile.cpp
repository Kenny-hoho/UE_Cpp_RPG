// Fill out your copyright notice in the Description page of Project Settings.


#include "SDTeleportProjectile.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"  // ������Чʹ��
#include "Particles/ParticleSystemComponent.h"

ASDTeleportProjectile::ASDTeleportProjectile()
{
	LifeTime = 1.0f;
	EffectTime = 0.3f;
}

void ASDTeleportProjectile::BeginPlay()
{
	Super::BeginPlay();

	SphereComp->OnComponentHit.AddDynamic(this, &ASDTeleportProjectile::OnActorHit);

	GetWorldTimerManager().SetTimer(TH_ProjectileFlying, this, &ASDTeleportProjectile::TeleportPlayer, LifeTime, false);
}

void ASDTeleportProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// ��������ֱ�Ӵ��ͣ�����Ҫ��ֹԭ����Timer
	GetWorldTimerManager().ClearTimer(TH_ProjectileFlying);
	TeleportPlayer();
}

void ASDTeleportProjectile::TeleportPlayer()
{
	EffectComp->DestroyComponent();

	FTransform CurrentTrans = GetTransform();
	// ȥ��Pitch��Roll����ֹ���ͺ��ɫ��б
	CurrentTrans = FTransform(FRotator(0, FRotator(CurrentTrans.GetRotation()).Yaw, 0), CurrentTrans.GetLocation(), CurrentTrans.GetScale3D());
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EndEffect, CurrentTrans);  // ������λ�ò�����Ч��#include "Kismet/GameplayStatics.h" 

	// ��ί���¼���������λ�ô��ݸ��ƶ������������ٵ���һ��GetTransform()��
	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &ASDTeleportProjectile::MovePawn, CurrentTrans);
	GetWorldTimerManager().SetTimer(TH_Effect, TimerDelegate, EffectTime, false);
}

void ASDTeleportProjectile::MovePawn(FTransform CurrentTrans)
{
	APawn* OwnerPlayer = GetInstigator();
	OwnerPlayer->TeleportTo(CurrentTrans.GetLocation(), FRotator(CurrentTrans.GetRotation()));
}

