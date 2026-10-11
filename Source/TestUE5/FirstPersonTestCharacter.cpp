#include "FirstPersonTestCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "UObject/ConstructorHelpers.h"

AFirstPersonTestCharacter::AFirstPersonTestCharacter()
{
    PrimaryActorTick.bCanEverTick = false;
    GetCapsuleComponent()->InitCapsuleSize(34.0f, 88.0f);

    FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    FirstPersonCamera->SetupAttachment(GetCapsuleComponent());
    FirstPersonCamera->SetRelativeLocation(FVector(0.0f, 0.0f, 64.0f));
    FirstPersonCamera->bUsePawnControlRotation = true;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));

    BodyVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyVisual"));
    BodyVisual->SetupAttachment(GetCapsuleComponent());
    BodyVisual->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
    BodyVisual->SetRelativeScale3D(FVector(0.34f, 0.26f, 0.42f));
    BodyVisual->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    if (CubeMesh.Succeeded()) BodyVisual->SetStaticMesh(CubeMesh.Object);

    HeadVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HeadVisual"));
    HeadVisual->SetupAttachment(GetCapsuleComponent());
    HeadVisual->SetRelativeLocation(FVector(0.0f, 0.0f, 59.0f));
    HeadVisual->SetRelativeScale3D(FVector(0.25f, 0.25f, 0.27f));
    HeadVisual->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    if (SphereMesh.Succeeded()) HeadVisual->SetStaticMesh(SphereMesh.Object);

    LeftArmVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftArmVisual"));
    LeftArmVisual->SetupAttachment(GetCapsuleComponent());
    LeftArmVisual->SetRelativeLocation(FVector(0.0f, -29.0f, 2.0f));
    LeftArmVisual->SetRelativeScale3D(FVector(0.22f, 0.15f, 0.38f));
    LeftArmVisual->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    if (CubeMesh.Succeeded()) LeftArmVisual->SetStaticMesh(CubeMesh.Object);

    RightArmVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightArmVisual"));
    RightArmVisual->SetupAttachment(GetCapsuleComponent());
    RightArmVisual->SetRelativeLocation(FVector(0.0f, 29.0f, 2.0f));
    RightArmVisual->SetRelativeScale3D(FVector(0.22f, 0.15f, 0.38f));
    RightArmVisual->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    if (CubeMesh.Succeeded()) RightArmVisual->SetStaticMesh(CubeMesh.Object);

    LeftLegVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftLegVisual"));
    LeftLegVisual->SetupAttachment(GetCapsuleComponent());
    LeftLegVisual->SetRelativeLocation(FVector(0.0f, -15.0f, -48.0f));
    LeftLegVisual->SetRelativeScale3D(FVector(0.23f, 0.13f, 0.36f));
    LeftLegVisual->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    if (CubeMesh.Succeeded()) LeftLegVisual->SetStaticMesh(CubeMesh.Object);

    RightLegVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightLegVisual"));
    RightLegVisual->SetupAttachment(GetCapsuleComponent());
    RightLegVisual->SetRelativeLocation(FVector(0.0f, 15.0f, -48.0f));
    RightLegVisual->SetRelativeScale3D(FVector(0.23f, 0.13f, 0.36f));
    RightLegVisual->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    if (CubeMesh.Succeeded()) RightLegVisual->SetStaticMesh(CubeMesh.Object);

    bUseControllerRotationYaw = true;
    GetCharacterMovement()->bOrientRotationToMovement = false;
    GetCharacterMovement()->MaxWalkSpeed = 500.0f;
    GetCharacterMovement()->JumpZVelocity = 460.0f;
    GetCharacterMovement()->AirControl = 0.30f;
}

void AFirstPersonTestCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void AFirstPersonTestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    check(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AFirstPersonTestCharacter::MoveForward);
    PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AFirstPersonTestCharacter::MoveRight);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AFirstPersonTestCharacter::Turn);
    PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AFirstPersonTestCharacter::LookUp);
    PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AFirstPersonTestCharacter::JumpPressed);
    PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &AFirstPersonTestCharacter::JumpReleased);
}

void AFirstPersonTestCharacter::MoveForward(float Value)
{
    if (Controller && Value != 0.0f)
        AddMovementInput(FRotationMatrix(Controller->GetControlRotation()).GetUnitAxis(EAxis::X), Value);
}

void AFirstPersonTestCharacter::MoveRight(float Value)
{
    if (Controller && Value != 0.0f)
        AddMovementInput(FRotationMatrix(Controller->GetControlRotation()).GetUnitAxis(EAxis::Y), Value);
}

void AFirstPersonTestCharacter::Turn(float Value) { AddControllerYawInput(Value); }
void AFirstPersonTestCharacter::LookUp(float Value) { AddControllerPitchInput(Value); }
void AFirstPersonTestCharacter::JumpPressed() { Jump(); }
void AFirstPersonTestCharacter::JumpReleased() { StopJumping(); }
