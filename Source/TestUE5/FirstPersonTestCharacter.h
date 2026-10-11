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
};
