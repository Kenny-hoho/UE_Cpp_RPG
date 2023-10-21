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

	// ʹ��ί�У�ʹ�ôݻ�����Actor�ĺ����ݻ�����������дһ��������
	FTimerDelegate DestroyActorTimerDelegate = FTimerDelegate::CreateUObject(this, &ASBlackHole::DestroyActor, Cast<AActor>(this));
	GetWorldTimerManager().SetTimer(DestroySelf_TimerHandle, DestroyActorTimerDelegate, LifeTime, false);
}

void ASBlackHole::DestroyPulledActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// ֻ������������ģ���Actor��Ч
	if (OtherComp->IsSimulatingPhysics()) {
		// ʹ��ί�У����ݲ���ָ����ЩActor����ײ������ص���������ЩActor
		FTimerDelegate DestroyActorTimerDelegate = FTimerDelegate::CreateUObject(this, &ASBlackHole::DestroyActor, OtherActor);
		GetWorldTimerManager().SetTimer(Destroy_TimerHandle, DestroyActorTimerDelegate, DestroyDelay, false);
	}
}

void ASBlackHole::DestroyActor(AActor* TargetActor)
{
	TargetActor->Destroy();
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, TEXT("Destroy!"));
}
