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
    PrimaryActorTick.bCanEverTick = true;
    GetCapsuleComponent()->InitCapsuleSize(34.0f, 88.0f);

    FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    FirstPersonCamera->SetupAttachment(GetCapsuleComponent());
    FirstPersonCamera->SetRelativeLocation(FVector(0.0f, 0.0f, 64.0f));
    FirstPersonCamera->bUsePawnControlRotation = true;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));

    auto ConfigureMesh = [](UStaticMeshComponent* Mesh)
    {
        Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        Mesh->SetGenerateOverlapEvents(false);
        Mesh->CastShadow = false;
    };

    // Simple full-body placeholder, visible to other players but hidden from its owner.
    BodyVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyVisual"));
    BodyVisual->SetupAttachment(GetCapsuleComponent());
    BodyVisual->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
    BodyVisual->SetRelativeScale3D(FVector(0.34f, 0.26f, 0.42f));
    ConfigureMesh(BodyVisual);
    BodyVisual->SetOwnerNoSee(true);
    if (CubeMesh.Succeeded()) BodyVisual->SetStaticMesh(CubeMesh.Object);

    HeadVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HeadVisual"));
    HeadVisual->SetupAttachment(GetCapsuleComponent());
    HeadVisual->SetRelativeLocation(FVector(0.0f, 0.0f, 59.0f));
    HeadVisual->SetRelativeScale3D(FVector(0.25f, 0.25f, 0.27f));
    ConfigureMesh(HeadVisual);
    HeadVisual->SetOwnerNoSee(true);
    if (SphereMesh.Succeeded()) HeadVisual->SetStaticMesh(SphereMesh.Object);

    LeftArmVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftArmVisual"));
    LeftArmVisual->SetupAttachment(GetCapsuleComponent());
    LeftArmVisual->SetRelativeLocation(FVector(0.0f, -29.0f, 2.0f));
    LeftArmVisual->SetRelativeScale3D(FVector(0.22f, 0.15f, 0.38f));
    ConfigureMesh(LeftArmVisual);
    LeftArmVisual->SetOwnerNoSee(true);
    if (CubeMesh.Succeeded()) LeftArmVisual->SetStaticMesh(CubeMesh.Object);

    RightArmVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightArmVisual"));
    RightArmVisual->SetupAttachment(GetCapsuleComponent());
    RightArmVisual->SetRelativeLocation(FVector(0.0f, 29.0f, 2.0f));
    RightArmVisual->SetRelativeScale3D(FVector(0.22f, 0.15f, 0.38f));
    ConfigureMesh(RightArmVisual);
    RightArmVisual->SetOwnerNoSee(true);
    if (CubeMesh.Succeeded()) RightArmVisual->SetStaticMesh(CubeMesh.Object);

    LeftLegVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftLegVisual"));
    LeftLegVisual->SetupAttachment(GetCapsuleComponent());
    LeftLegVisual->SetRelativeLocation(FVector(0.0f, -15.0f, -48.0f));
    LeftLegVisual->SetRelativeScale3D(FVector(0.23f, 0.13f, 0.36f));
    ConfigureMesh(LeftLegVisual);
    LeftLegVisual->SetOwnerNoSee(true);
    if (CubeMesh.Succeeded()) LeftLegVisual->SetStaticMesh(CubeMesh.Object);

    RightLegVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightLegVisual"));
    RightLegVisual->SetupAttachment(GetCapsuleComponent());
    RightLegVisual->SetRelativeLocation(FVector(0.0f, 15.0f, -48.0f));
    RightLegVisual->SetRelativeScale3D(FVector(0.23f, 0.13f, 0.36f));
    ConfigureMesh(RightLegVisual);
    RightLegVisual->SetOwnerNoSee(true);
    if (CubeMesh.Succeeded()) RightLegVisual->SetStaticMesh(CubeMesh.Object);

    // First-person sleeves extend forward from the bottom corners of the camera view.
    // Camera-local X is forward, Y is right, and Z is up.
    LeftSleeveVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftSleeveVisual"));
    LeftSleeveVisual->SetupAttachment(FirstPersonCamera);
    LeftSleeveVisual->SetRelativeLocation(FVector(38.0f, -19.0f, -22.0f));
    LeftSleeveVisual->SetRelativeRotation(FRotator(0.0f, -7.0f, -8.0f));
    LeftSleeveVisual->SetRelativeScale3D(FVector(0.30f, 0.115f, 0.115f));
    ConfigureMesh(LeftSleeveVisual);
    LeftSleeveVisual->SetOnlyOwnerSee(true);
    if (CubeMesh.Succeeded()) LeftSleeveVisual->SetStaticMesh(CubeMesh.Object);

    RightSleeveVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightSleeveVisual"));
    RightSleeveVisual->SetupAttachment(FirstPersonCamera);
    RightSleeveVisual->SetRelativeLocation(FVector(38.0f, 19.0f, -22.0f));
    RightSleeveVisual->SetRelativeRotation(FRotator(0.0f, 7.0f, 8.0f));
    RightSleeveVisual->SetRelativeScale3D(FVector(0.30f, 0.115f, 0.115f));
    ConfigureMesh(RightSleeveVisual);
    RightSleeveVisual->SetOnlyOwnerSee(true);
    if (CubeMesh.Succeeded()) RightSleeveVisual->SetStaticMesh(CubeMesh.Object);

    LeftHandVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftHandVisual"));
    LeftHandVisual->SetupAttachment(FirstPersonCamera);
    LeftHandVisual->SetRelativeLocation(FVector(62.0f, -19.0f, -23.0f));
    LeftHandVisual->SetRelativeScale3D(FVector(0.095f, 0.085f, 0.075f));
    ConfigureMesh(LeftHandVisual);
    LeftHandVisual->SetOnlyOwnerSee(true);
    if (SphereMesh.Succeeded()) LeftHandVisual->SetStaticMesh(SphereMesh.Object);

    RightHandVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightHandVisual"));
    RightHandVisual->SetupAttachment(FirstPersonCamera);
    RightHandVisual->SetRelativeLocation(FVector(62.0f, 19.0f, -23.0f));
    RightHandVisual->SetRelativeScale3D(FVector(0.095f, 0.085f, 0.075f));
    ConfigureMesh(RightHandVisual);
    RightHandVisual->SetOnlyOwnerSee(true);
    if (SphereMesh.Succeeded()) RightHandVisual->SetStaticMesh(SphereMesh.Object);

    CameraStartLocation = FirstPersonCamera->GetRelativeLocation();
    LeftSleeveStartLocation = LeftSleeveVisual->GetRelativeLocation();
    RightSleeveStartLocation = RightSleeveVisual->GetRelativeLocation();

    bUseControllerRotationYaw = true;
    GetCharacterMovement()->bOrientRotationToMovement = false;
    GetCharacterMovement()->MaxWalkSpeed = 500.0f;
    GetCharacterMovement()->JumpZVelocity = 460.0f;
    GetCharacterMovement()->AirControl = 0.30f;
}

void AFirstPersonTestCharacter::BeginPlay()
{
    Super::BeginPlay();
    AnimationClock = 0.0f;
}

void AFirstPersonTestCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    // Lightweight procedural bob to prove the animation hook works before a skeletal rig is added.
    const FVector Velocity = GetVelocity();
    const float HorizontalSpeed = FVector(Velocity.X, Velocity.Y, 0.0f).Size();
    const float MoveAmount = FMath::Clamp(HorizontalSpeed / GetCharacterMovement()->MaxWalkSpeed, 0.0f, 1.0f);
    const bool bOnGround = GetCharacterMovement()->IsMovingOnGround();

    if (MoveAmount > 0.05f && bOnGround)
        AnimationClock += DeltaSeconds * (8.0f + 4.0f * MoveAmount);

    const float Bob = (MoveAmount > 0.05f && bOnGround) ? FMath::Sin(AnimationClock) * 1.8f : 0.0f;
    const float Sway = (MoveAmount > 0.05f && bOnGround) ? FMath::Sin(AnimationClock * 0.5f) * 1.2f : 0.0f;

    LeftSleeveVisual->SetRelativeLocation(LeftSleeveStartLocation + FVector(0.0f, 0.0f, Bob));
    RightSleeveVisual->SetRelativeLocation(RightSleeveStartLocation + FVector(0.0f, 0.0f, -Bob));
    LeftSleeveVisual->SetRelativeRotation(FRotator(0.0f, -7.0f + Sway, -8.0f));
    RightSleeveVisual->SetRelativeRotation(FRotator(0.0f, 7.0f - Sway, 8.0f));
    LeftHandVisual->SetRelativeLocation(FVector(62.0f, -19.0f, -23.0f + Bob));
    RightHandVisual->SetRelativeLocation(FVector(62.0f, 19.0f, -23.0f - Bob));
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
