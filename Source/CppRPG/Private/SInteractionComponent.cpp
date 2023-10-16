// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"
#include "SGameplayInterface.h"
#include "SCharacter.h"


// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void USInteractionComponent::PrimaryInteract()
{
	// ���ü���˭��Ч
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(30.0f);

	AActor* MyOwner = GetOwner();

	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector End = EyeLocation + (EyeRotation.Vector() * 250.0f);

	// �����߼��
	//FHitResult Hit;
	//GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams);

	// Sweep���
	TArray<FHitResult> Hits;
	GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, CollisionShape);

	for (FHitResult Hit : Hits) {
		AActor* HitActor = Hit.GetActor();
		if (HitActor) {
			if (HitActor->Implements<USGameplayInterface>()) {
				// ����ת��ΪPawn
				APawn* MyPawn = Cast<APawn>(MyOwner);
				ISGameplayInterface::Execute_Interact(HitActor, MyPawn);// HitActor��ִ��Interact�Ķ���MyPawn��Interact�����Ķ���
			}
		}
		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, CollisionShape.GetSphereRadius(), 32, FColor::Blue, false, 2.0f, 0, 2.0f);
		break;
	}

	DrawDebugLine(GetWorld(), EyeLocation, End, FColor::Red, false, 2.0f, 0, 3);
}