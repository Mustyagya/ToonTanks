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
		GameOver(false);//пока выключен чтобы сразу не было проигреша в игре
	}
		//это уже уничтожение турели
		 else if (ATower* DestroyedTower= Cast<ATower>(DeadActor))
		{
		 	DestroyedTower->HandleDistrucion();
		 	TargetTower--;//уменьшаем количество башен после их смерти
		 	if(TargetTower==0)
		 	{
		 		//если все башни уничтожены то это победа!
		 		GameOver(true);
		 	}
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
	//и тут в начале указываем количество турелей в мире
	TargetTower=GetTargetTowerCount();
	
	StartGame();//вот так сможем вызвать ивент в блупринт gameMode
	Tansk=Cast<ATansk>(UGameplayStatics::GetPlayerPawn(this,0));
	//подключаем свой плеер контроллер
	ToonTanksPlayerController=Cast<AToonTanksPlayerController>
	(UGameplayStatics::GetPlayerController(this,0));

	if (ToonTanksPlayerController)
	{
		ToonTanksPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate PlayerEnableTimerDelegate=FTimerDelegate::CreateUObject
		(ToonTanksPlayerController,&AToonTanksPlayerController::SetPlayerEnabledState,true);

		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle,PlayerEnableTimerDelegate,StartDay,false);
	}
}

int32 AToonTanksGameMode::GetTargetTowerCount()
{
	//делаем конвератацию автера башни в массви
	TArray<AActor*> Towers;
	//обращаемся кактерам башни через статический классы
	UGameplayStatics::GetAllActorsOfClass(this,ATower::StaticClass(),Towers);
	// и возврощаем их количество
	return Towers.Num();
}
