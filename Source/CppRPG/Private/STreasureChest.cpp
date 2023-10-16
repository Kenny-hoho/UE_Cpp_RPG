// Fill out your copyright notice in the Description page of Project Settings.


#include "STreasureChest.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASTreasureChest::ASTreasureChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ChestBottom = CreateDefaultSubobject<UStaticMeshComponent>("ChestBottom");
	RootComponent = ChestBottom;

	ChestLid = CreateDefaultSubobject<UStaticMeshComponent>("ChestLid");
	ChestLid->SetupAttachment(ChestBottom);

	GoldMesh = CreateDefaultSubobject<UStaticMeshComponent>("GoldMesh");
	GoldMesh->SetupAttachment(ChestBottom);

	TargetPitch = 110;
}

// Called when the game starts or when spawned
void ASTreasureChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASTreasureChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASTreasureChest::Interact_Implementation(APawn* InstigatorPawn)
{
	ChestLid->SetRelativeRotation(FRotator(TargetPitch, 0, 0));
}
