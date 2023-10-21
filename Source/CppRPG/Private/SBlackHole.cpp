// Fill out your copyright notice in the Description page of Project Settings.


#include "SBlackHole.h"
#include "Components/SphereComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

ASBlackHole::ASBlackHole()
{
	ForceComp = CreateDefaultSubobject<URadialForceComponent>("ForceComp");
	ForceComp->Radius = 1000.0f;
	ForceComp->ForceStrength = -250000.0f;
	ForceComp->RemoveObjectTypeToAffect(EObjectTypeQuery::ObjectTypeQuery1);
	ForceComp->SetupAttachment(ASBaseProjectile::SphereComp);

	DestroySphereComp = CreateDefaultSubobject<USphereComponent>("DestroySphereComp");
	DestroySphereComp->SetupAttachment(ForceComp);

	LifeTime = 4.0f;
	DestroyDelay = 0.2f;
}

void ASBlackHole::BeginPlay()
{
	Super::BeginPlay();
	DestroySphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASBlackHole::DestroyPulledActor);

	// 使用委托，使用摧毁其他Actor的函数摧毁自身，不用再写一个函数了
	FTimerDelegate DestroyActorTimerDelegate = FTimerDelegate::CreateUObject(this, &ASBlackHole::DestroyActor, Cast<AActor>(this));
	GetWorldTimerManager().SetTimer(DestroySelf_TimerHandle, DestroyActorTimerDelegate, LifeTime, false);
}

void ASBlackHole::DestroyPulledActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 只对启用了物理模拟的Actor生效
	if (OtherComp->IsSimulatingPhysics()) {
		// 使用委托，传递参数指明哪些Actor与碰撞体组件重叠，销毁这些Actor
		FTimerDelegate DestroyActorTimerDelegate = FTimerDelegate::CreateUObject(this, &ASBlackHole::DestroyActor, OtherActor);
		GetWorldTimerManager().SetTimer(Destroy_TimerHandle, DestroyActorTimerDelegate, DestroyDelay, false);
	}
}

void ASBlackHole::DestroyActor(AActor* TargetActor)
{
	TargetActor->Destroy();
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, TEXT("Destroy!"));
}
