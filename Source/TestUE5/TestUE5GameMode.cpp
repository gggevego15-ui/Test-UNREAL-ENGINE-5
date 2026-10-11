#include "TestUE5GameMode.h"
#include "FirstPersonTestCharacter.h"

#include "Components/DirectionalLightComponent.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Components/SkyLightComponent.h"
#include "Engine/DirectionalLight.h"
#include "Engine/ExponentialHeightFog.h"
#include "Engine/SkyAtmosphere.h"
#include "Engine/SkyLight.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerStart.h"
#include "UObject/ConstructorHelpers.h"

namespace
{
    AStaticMeshActor* SpawnTestCube(
        UWorld* World,
        UStaticMesh* CubeMesh,
        const FVector& Location,
        const FVector& Scale,
        const FRotator& Rotation = FRotator::ZeroRotator)
    {
        if (!World || !CubeMesh)
        {
            return nullptr;
        }

        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        AStaticMeshActor* CubeActor = World->SpawnActor<AStaticMeshActor>(
            AStaticMeshActor::StaticClass(),
            FTransform(Rotation, Location, Scale),
            SpawnParams);

        if (CubeActor)
        {
            UStaticMeshComponent* MeshComponent = CubeActor->GetStaticMeshComponent();
            MeshComponent->SetStaticMesh(CubeMesh);
            MeshComponent->SetMobility(EComponentMobility::Static);
            MeshComponent->SetCollisionProfileName(TEXT("BlockAll"));
            MeshComponent->SetGenerateOverlapEvents(false);
        }

        return CubeActor;
    }
}

ATestUE5GameMode::ATestUE5GameMode()
{
    DefaultPawnClass = AFirstPersonTestCharacter::StaticClass();
}

void ATestUE5GameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
    Super::InitGame(MapName, Options, ErrorMessage);

    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    // Build a small playable test arena in code, so the prototype does not depend
    // on a binary .umap asset being manually created first.
    UStaticMesh* CubeMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (CubeMesh)
    {
        // Main floor: 60 m x 60 m, top surface at Z=0.
        SpawnTestCube(World, CubeMesh, FVector(0.0f, 0.0f, -50.0f), FVector(600.0f, 600.0f, 1.0f));

        // Low perimeter walls to make the test area's edges visible.
        SpawnTestCube(World, CubeMesh, FVector(0.0f, 3000.0f, 100.0f), FVector(600.0f, 1.0f, 3.0f));
        SpawnTestCube(World, CubeMesh, FVector(0.0f, -3000.0f, 100.0f), FVector(600.0f, 1.0f, 3.0f));
        SpawnTestCube(World, CubeMesh, FVector(3000.0f, 0.0f, 100.0f), FVector(1.0f, 600.0f, 3.0f));
        SpawnTestCube(World, CubeMesh, FVector(-3000.0f, 0.0f, 100.0f), FVector(1.0f, 600.0f, 3.0f));

        // A few raised platforms for basic movement/jump testing.
        SpawnTestCube(World, CubeMesh, FVector(550.0f, 0.0f, 35.0f), FVector(2.5f, 3.0f, 0.7f));
        SpawnTestCube(World, CubeMesh, FVector(900.0f, 0.0f, 105.0f), FVector(2.0f, 2.5f, 0.7f));
        SpawnTestCube(World, CubeMesh, FVector(1200.0f, 350.0f, 175.0f), FVector(2.0f, 2.0f, 0.7f));
        SpawnTestCube(World, CubeMesh, FVector(1500.0f, -350.0f, 245.0f), FVector(2.0f, 2.0f, 0.7f));
    }

    // Explicit start location above the floor. GameMode uses this when spawning the player.
    FActorSpawnParameters StartParams;
    StartParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    APlayerStart* PlayerStart = World->SpawnActor<APlayerStart>(
        APlayerStart::StaticClass(),
        FTransform(FRotator::ZeroRotator, FVector(0.0f, 0.0f, 100.0f)),
        StartParams);
    if (PlayerStart)
    {
        PlayerStart->SetActorLabel(TEXT("Test Arena Player Start"));
    }

    // Physically based sun and sky atmosphere.
    FActorSpawnParameters LightParams;
    LightParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    ASkyAtmosphere* Atmosphere = World->SpawnActor<ASkyAtmosphere>(
        ASkyAtmosphere::StaticClass(), FTransform::Identity, LightParams);
    if (Atmosphere)
    {
        Atmosphere->SetActorLabel(TEXT("Test Arena Sky Atmosphere"));
    }

    ADirectionalLight* Sun = World->SpawnActor<ADirectionalLight>(
        ADirectionalLight::StaticClass(),
        FTransform(FRotator(-35.0f, -25.0f, 0.0f), FVector::ZeroVector),
        LightParams);
    if (Sun)
    {
        Sun->GetLightComponent()->SetIntensity(100000.0f);
        Sun->GetLightComponent()->SetLightColor(FLinearColor(1.0f, 0.91f, 0.78f));
        Sun->GetLightComponent()->bAtmosphereSunLight = true;
        Sun->GetLightComponent()->AtmosphereSunLightIndex = 0;
        Sun->GetLightComponent()->SetCastShadows(true);
        Sun->SetActorLabel(TEXT("Test Arena Sun"));
    }

    ASkyLight* SkyLight = World->SpawnActor<ASkyLight>(
        ASkyLight::StaticClass(), FTransform::Identity, LightParams);
    if (SkyLight)
    {
        SkyLight->GetLightComponent()->SetMobility(EComponentMobility::Movable);
        SkyLight->GetLightComponent()->SetIntensity(1.0f);
        SkyLight->GetLightComponent()->SourceType = ESkyLightSourceType::SLS_CapturedScene;
        SkyLight->GetLightComponent()->bRealTimeCapture = true;
        SkyLight->SetActorLabel(TEXT("Test Arena Sky Light"));
    }

    AExponentialHeightFog* Fog = World->SpawnActor<AExponentialHeightFog>(
        AExponentialHeightFog::StaticClass(), FTransform::Identity, LightParams);
    if (Fog)
    {
        Fog->GetComponent()->SetFogDensity(0.003f);
        Fog->GetComponent()->SetFogHeightFalloff(0.2f);
        Fog->GetComponent()->SetFogInscatteringColor(FLinearColor(0.58f, 0.70f, 0.82f));
        Fog->SetActorLabel(TEXT("Test Arena Atmospheric Fog"));
    }
}
