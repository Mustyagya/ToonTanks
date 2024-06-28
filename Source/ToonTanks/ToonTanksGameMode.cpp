// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tansk.h"
#include "ToonTanksPlayerController.h"
#include "Tower.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if(DeadActor==Tansk)
	{
		//если танк мертв, то вызываем функцию HandleDistrucion
		Tansk->HandleDistrucion();
		//и отключаем контроллер елси он включен  проверяем
		if (ToonTanksPlayerController)
		{
			//это новый варинат отключения контроллера
			ToonTanksPlayerController->SetPlayerEnabledState(false);
				
		}
	}
		//это уже уничтожение турели
		 else if (ATower* DestroyedTower= Cast<ATower>(DeadActor))
		{
		 	DestroyedTower->HandleDistrucion();
		}
		
	}
void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	HandelGameStart();
	}
//функция для старта через 3 секунды 
void AToonTanksGameMode::HandelGameStart()
{

	Tansk=Cast<ATansk>(UGameplayStatics::GetPlayerPawn(this,0));
	//подключаем свой плеер контроллер
	ToonTanksPlayerController=Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this,0));

	if (ToonTanksPlayerController)
	{
		ToonTanksPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate PlayerEnableTimerDelegate=FTimerDelegate::CreateUObject
		(ToonTanksPlayerController,&AToonTanksPlayerController::SetPlayerEnabledState,true);

		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle,PlayerEnableTimerDelegate,StartDay,false);
	}
}
