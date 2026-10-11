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
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"

namespace
{
    UMaterialInterface* LoadBasicShapeMaterial()
    {
        return LoadObject<UMaterialInterface>(nullptr, TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial"));
    }

    AStaticMeshActor* SpawnTestCube(
        UWorld* World,
        UStaticMesh* CubeMesh,
        UMaterialInterface* BaseMaterial,
        const FVector& Location,
        const FVector& Scale,
        const FLinearColor& Tint,
        float Roughness = 0.82f,
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

            if (BaseMaterial)
            {
                UMaterialInstanceDynamic* Material = UMaterialInstanceDynamic::Create(BaseMaterial, MeshComponent);
                if (Material)
                {
                    Material->SetVectorParameterValue(TEXT("Color"), Tint);
                    Material->SetScalarParameterValue(TEXT("Roughness"), Roughness);
                    MeshComponent->SetMaterial(0, Material);
                }
            }
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

    // Build a small playable arena using built-in Unreal meshes and material assets.
    UStaticMesh* CubeMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Cube.Cube"));
    UMaterialInterface* BasicMaterial = LoadBasicShapeMaterial();
    if (CubeMesh)
    {
        // Main floor: 60 m x 60 m, top surface at Z=0. Neutral concrete tint.
        SpawnTestCube(World, CubeMesh, BasicMaterial, FVector(0.0f, 0.0f, -50.0f),
            FVector(60.0f, 60.0f, 1.0f), FLinearColor(0.34f, 0.36f, 0.38f), 0.9f);

        // Perimeter walls: charcoal trim with warm safety-color accents at the corners.
        const FLinearColor WallColor(0.16f, 0.19f, 0.22f);
        SpawnTestCube(World, CubeMesh, BasicMaterial, FVector(0.0f, 3000.0f, 100.0f),
            FVector(60.0f, 1.0f, 3.0f), WallColor);
        SpawnTestCube(World, CubeMesh, BasicMaterial, FVector(0.0f, -3000.0f, 100.0f),
            FVector(60.0f, 1.0f, 3.0f), WallColor);
        SpawnTestCube(World, CubeMesh, BasicMaterial, FVector(3000.0f, 0.0f, 100.0f),
            FVector(1.0f, 60.0f, 3.0f), WallColor);
        SpawnTestCube(World, CubeMesh, BasicMaterial, FVector(-3000.0f, 0.0f, 100.0f),
            FVector(1.0f, 60.0f, 3.0f), WallColor);

        // Raised platforms use distinct muted colors so their edges are easy to read.
        SpawnTestCube(World, CubeMesh, BasicMaterial, FVector(550.0f, 0.0f, 35.0f),
            FVector(2.5f, 3.0f, 0.7f), FLinearColor(0.18f, 0.36f, 0.43f), 0.55f);
        SpawnTestCube(World, CubeMesh, BasicMaterial, FVector(900.0f, 0.0f, 105.0f),
            FVector(2.0f, 2.5f, 0.7f), FLinearColor(0.56f, 0.35f, 0.16f), 0.58f);
        SpawnTestCube(World, CubeMesh, BasicMaterial, FVector(1200.0f, 350.0f, 175.0f),
            FVector(2.0f, 2.0f, 0.7f), FLinearColor(0.24f, 0.40f, 0.30f), 0.62f);
        SpawnTestCube(World, CubeMesh, BasicMaterial, FVector(1500.0f, -350.0f, 245.0f),
            FVector(2.0f, 2.0f, 0.7f), FLinearColor(0.35f, 0.31f, 0.45f), 0.58f);
    }

    // Spawn point is 100 cm above the floor.
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    World->SpawnActor<APlayerStart>(
        APlayerStart::StaticClass(),
        FTransform(FRotator::ZeroRotator, FVector(0.0f, 0.0f, 100.0f)),
        SpawnParams);

    // Atmosphere, warm directional sunlight, skylight and subtle distance haze.
    FActorSpawnParameters LightParams;
    LightParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    World->SpawnActor<ASkyAtmosphere>(ASkyAtmosphere::StaticClass(), FTransform::Identity, LightParams);

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
    }

    ASkyLight* SkyLight = World->SpawnActor<ASkyLight>(
        ASkyLight::StaticClass(), FTransform::Identity, LightParams);
    if (SkyLight)
    {
        SkyLight->GetLightComponent()->SetMobility(EComponentMobility::Movable);
        SkyLight->GetLightComponent()->SetIntensity(1.0f);
        SkyLight->GetLightComponent()->SourceType = ESkyLightSourceType::SLS_CapturedScene;
        SkyLight->GetLightComponent()->bRealTimeCapture = true;
    }

    AExponentialHeightFog* Fog = World->SpawnActor<AExponentialHeightFog>(
        AExponentialHeightFog::StaticClass(), FTransform::Identity, LightParams);
    if (Fog)
    {
        Fog->GetComponent()->SetFogDensity(0.003f);
        Fog->GetComponent()->SetFogHeightFalloff(0.2f);
        Fog->GetComponent()->SetFogInscatteringColor(FLinearColor(0.58f, 0.70f, 0.82f));
    }
}
