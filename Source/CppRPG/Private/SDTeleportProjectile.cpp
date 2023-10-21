// Fill out your copyright notice in the Description page of Project Settings.


#include "SDTeleportProjectile.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"  // 播放特效使用
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
	// 碰到物体直接传送，并且要终止原来的Timer
	GetWorldTimerManager().ClearTimer(TH_ProjectileFlying);
	TeleportPlayer();
}

void ASDTeleportProjectile::TeleportPlayer()
{
	EffectComp->DestroyComponent();

	FTransform CurrentTrans = GetTransform();
	// 去除Pitch和Roll，防止传送后角色倾斜
	CurrentTrans = FTransform(FRotator(0, FRotator(CurrentTrans.GetRotation()).Yaw, 0), CurrentTrans.GetLocation(), CurrentTrans.GetScale3D());
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EndEffect, CurrentTrans);  // 在任意位置播放特效，#include "Kismet/GameplayStatics.h" 

	// 绑定委托事件，将传送位置传递给移动函数，不用再调用一次GetTransform()了
	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &ASDTeleportProjectile::MovePawn, CurrentTrans);
	GetWorldTimerManager().SetTimer(TH_Effect, TimerDelegate, EffectTime, false);
}

void ASDTeleportProjectile::MovePawn(FTransform CurrentTrans)
{
	APawn* OwnerPlayer = GetInstigator();
	OwnerPlayer->TeleportTo(CurrentTrans.GetLocation(), FRotator(CurrentTrans.GetRotation()));
}

