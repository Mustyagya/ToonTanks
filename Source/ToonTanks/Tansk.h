// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tansk.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATansk : public ABasePawn
{
	GENERATED_BODY()

public:

	ATansk();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void HandleDistrucion();

	APlayerController* GetTanskPlayerController() const {return TanskPlayerController;}
	//это мы получаем доступ до контроллера если он находится в привате или протектед, можно конечно сделать его публичным,
	//но нестоит этого делать 
	
private:

	UPROPERTY(VisibleAnywhere , Category = "Component") class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = "Component") class UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, Category="Movmend") float Speed_Tank=200.0f;
	UPROPERTY(EditAnywhere, Category="Movmend") float Turn_Rate=45.0f;
	void moved (float value);
	void turn (float value);
	APlayerController* TanskPlayerController;
protected:
	virtual  void BeginPlay() override;
	virtual  void Tick(float DeltaTime) override;
};
