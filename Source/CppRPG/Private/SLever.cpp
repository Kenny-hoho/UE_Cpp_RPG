// Fill out your copyright notice in the Description page of Project Settings.


#include "SLever.h"
#include "Components/StaticMeshComponent.h"
#include "STreasureChest.h"
#include "SExplosiveBarrel.h"

// Sets default values
ASLever::ASLever()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;

	LeverMesh = CreateDefaultSubobject<UStaticMeshComponent>("LeverMesh");
	LeverMesh->SetupAttachment(BaseMesh);

	LeverMesh->SetRelativeRotation(FRotator(30, 0, 0));
}

// Called when the game starts or when spawned
void ASLever::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASLever::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ASLever::Interact_Implementation(APawn* InstigatorPawn)
{
	LeverMesh->SetRelativeRotation(FRotator(-30, 0, 0));

	// ´ò¿ª±¦Ïä
	//ASTreasureChest* TreasureChest = Cast<ASTreasureChest>(ControlledActor);
	//TreasureChest->Interact_Implementation(InstigatorPawn);

	// Òý±¬Õ¨Ò©Í°
	ASExplosiveBarrel* Barrel = Cast<ASExplosiveBarrel>(ControlledActor);
	Barrel->Fire();
}