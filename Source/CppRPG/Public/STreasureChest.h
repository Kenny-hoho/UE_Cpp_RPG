// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGameplayInterface.h"
#include "STreasureChest.generated.h"

class UStaticMeshComponent;

UCLASS()
class CPPRPG_API ASTreasureChest : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()

public:

	void Interact_Implementation(APawn* InstigatorPawn);

public:	
	// Sets default values for this actor's properties
	ASTreasureChest();

	UPROPERTY(EditAnywhere)
	float TargetPitch;

protected:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ChestBottom;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ChestLid;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
