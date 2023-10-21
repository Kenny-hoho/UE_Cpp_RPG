// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "KismetClasses.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "SInteractionComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ���õ��ɱ�
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;

	// ���������
	CameraComp = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComp->SetupAttachment(SpringArmComp);

	// ��ת�ӽ�ʱ��ɫģ�Ͳ��������ת
	bUseControllerRotationYaw = false;
	
	// ����ת�����˶�
	GetCharacterMovement()->bOrientRotationToMovement = true;

	// ���ý������
	InteractionComp = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");

	AimTarget = FVector(0, 0, 0);
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FCollisionObjectQueryParams CollisionQueryParams;
	CollisionQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	CollisionQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);

	FHitResult Hit;
	FVector Start = CameraComp->GetComponentLocation();
	FVector End = Start + CameraComp->GetComponentRotation().Vector() * 10000.0f;

	GetWorld()->LineTraceSingleByObjectType(Hit, Start, End, CollisionQueryParams);
	// DrawDebugLine(GetWorld(), Start + FVector(20, 0, 0), End, FColor::Red, false, 0.0f, 0, 0.5f);

	if (Hit.bBlockingHit) {
		AimTarget = Hit.ImpactPoint;
		DrawDebugString(GetWorld(), AimTarget, TEXT("HIT"), 0, FColor::Red, 0.2f);
	}
	else {
		AimTarget = End;
	}
}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Basic Movement
	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);

	// Camera Movement
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	// Jump
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

	// Primary Attack
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);

	// Ultimate Attack
	PlayerInputComponent->BindAction("UltimateAttack", IE_Pressed, this, &ASCharacter::UltimateAttack);

	// Primary Interact
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ASCharacter::PrimaryInteract);

	// Teleport
	PlayerInputComponent->BindAction("Teleport", IE_Pressed, this, &ASCharacter::Teleport);
}


void ASCharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	AddMovementInput(ControlRot.Vector(), Value);
}

void ASCharacter::MoveRight(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	FVector RightVec = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVec, Value);
}

void ASCharacter::PrimaryAttack()
{
	// ���Ź���������̫��
	PlayAnimMontage(AttackAnim);

	// ����Timer���ӳ�����projectile
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::PrimaryAttack_TimerDelay, 0.2f);
}

void ASCharacter::PrimaryAttack_TimerDelay()
{
	// �����з����ӵ�
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	FTransform SpawnTransform = FTransform(GetControlRotation(), HandLocation);

	// �������ɹ���
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; // ���������ɵĵط��Ƿ������ײ������
	SpawnParams.Instigator = this;

	// ����
	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTransform, SpawnParams);
}

void ASCharacter::UltimateAttack()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_UltimateAttack, this, &ASCharacter::UltimateAttack_TimerDelay, 0.3f);
}

void ASCharacter::UltimateAttack_TimerDelay()
{
	// �����з����ӵ�
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	FTransform SpawnTransform = FTransform(GetControlRotation(), HandLocation + FVector(0, 0, 150.0f));

	// �������ɹ���
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; // ���������ɵĵط��Ƿ������ײ������
	SpawnParams.Instigator = this;

	// ����
	GetWorld()->SpawnActor<AActor>(UltimateProjectileClass, SpawnTransform, SpawnParams);
}

void ASCharacter::Teleport()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::Teleport_TimerDelay, 0.3f);
}

void ASCharacter::Teleport_TimerDelay()
{
	// �����з����ӵ�
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	FTransform SpawnTransform = FTransform(GetControlRotation(), HandLocation);

	// �������ɹ���
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; // ���������ɵĵط��Ƿ������ײ������
	SpawnParams.Instigator = this;

	// ����
	GetWorld()->SpawnActor<AActor>(TeleportClass, SpawnTransform, SpawnParams);
}

void ASCharacter::PrimaryInteract()
{
	InteractionComp->PrimaryInteract();
}
