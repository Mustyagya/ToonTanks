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

protected:
	virtual void BeginPlay() override;
	
};
