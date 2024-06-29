// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	void ActorDied (AActor* DeadActor);
protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintImplementableEvent) void StartGame();
	UFUNCTION(BlueprintImplementableEvent) void GameOver(bool bWonGame);
	
private:
	//подключаем классы
	//танка
	 class ATansk* Tansk;
	//плеер контроллер
	class AToonTanksPlayerController* ToonTanksPlayerController;
	//это перменная для тсарта игры чере з 3 секунды
	float StartDay = 3.0f;
    //это как раз функция для этого
	void HandelGameStart();
	//нужно узнать сколько турелей унчтожено чтобы выиграть в игре
	int32 TargetTower=0;
	int32 GetTargetTowerCount();


};
