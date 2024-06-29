// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	UPROPERTY(EditAnywhere,BlueprintReadWrite) float Speed_Tansk=400.0f;
	void HandleDistrucion();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void RotateTuret (FVector LookAtTarget);
	void Fier();

private:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category="Components",meta=(AllowPrivateAccess= "true"))
	class UCapsuleComponent* CapsuleComp;//заметка для меня если указать class то библеотеку не обязательно подключать
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category="Components",meta=(AllowPrivateAccess= "true"))
	class UStaticMeshComponent* TurretsMesh; 
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category="Components",meta=(AllowPrivateAccess= "true"))
	class UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category="Components",meta=(AllowPrivateAccess= "true"))
	class USceneComponent* ProjectileSpawn;
    //--
	UPROPERTY(EditDefaultsOnly,Category="Combat") TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* DeathParticles;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase *DeathSound;

};
