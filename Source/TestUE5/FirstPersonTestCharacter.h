#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FirstPersonTestCharacter.generated.h"

class UCameraComponent;
class UStaticMeshComponent;

UCLASS()
class TESTUE5_API AFirstPersonTestCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AFirstPersonTestCharacter();
    virtual void Tick(float DeltaSeconds) override;

protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
    void MoveForward(float Value);
    void MoveRight(float Value);
    void Turn(float Value);
    void LookUp(float Value);
    void JumpPressed();
    void JumpReleased();

    UPROPERTY(VisibleAnywhere, Category="Camera")
    TObjectPtr<UCameraComponent> FirstPersonCamera;

    // Third-person silhouette. Owner does not see these meshes in first person.
    UPROPERTY(VisibleAnywhere, Category="Character Visual")
    TObjectPtr<UStaticMeshComponent> BodyVisual;

    UPROPERTY(VisibleAnywhere, Category="Character Visual")
    TObjectPtr<UStaticMeshComponent> HeadVisual;

    UPROPERTY(VisibleAnywhere, Category="Character Visual")
    TObjectPtr<UStaticMeshComponent> LeftArmVisual;

    UPROPERTY(VisibleAnywhere, Category="Character Visual")
    TObjectPtr<UStaticMeshComponent> RightArmVisual;

    UPROPERTY(VisibleAnywhere, Category="Character Visual")
    TObjectPtr<UStaticMeshComponent> LeftLegVisual;

    UPROPERTY(VisibleAnywhere, Category="Character Visual")
    TObjectPtr<UStaticMeshComponent> RightLegVisual;

    // Camera-attached first-person arms; these are a placeholder rig for later skeletal animation.
    UPROPERTY(VisibleAnywhere, Category="First Person Arms")
    TObjectPtr<UStaticMeshComponent> LeftSleeveVisual;

    UPROPERTY(VisibleAnywhere, Category="First Person Arms")
    TObjectPtr<UStaticMeshComponent> RightSleeveVisual;

    UPROPERTY(VisibleAnywhere, Category="First Person Arms")
    TObjectPtr<UStaticMeshComponent> LeftHandVisual;

    UPROPERTY(VisibleAnywhere, Category="First Person Arms")
    TObjectPtr<UStaticMeshComponent> RightHandVisual;

    FVector CameraStartLocation;
    FVector LeftSleeveStartLocation;
    FVector RightSleeveStartLocation;
    float AnimationClock = 0.0f;
};
