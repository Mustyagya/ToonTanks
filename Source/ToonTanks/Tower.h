// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()
public:
	virtual  void Tick(float DeltaTime) override;
	void HandleDistrucion();

protected:
	virtual  void BeginPlay() override;
private:
	class ATansk* Tansk;
	
	UPROPERTY(EditDefaultsOnly,Category="Combat")
	float Fier_Range=300.0f;
	FTimerHandle FierRateTimerHandle;
	float FierRate=2.0f;
	void CheckFierCondition();
	bool InFierRange();
	


	
	
};
