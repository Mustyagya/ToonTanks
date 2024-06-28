// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tansk.h"
#include "VectorTypes.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
	if (InFierRange())
	{

		RotateTuret(Tansk->GetActorLocation());
	}
}

void ATower::HandleDistrucion()
{
	Super::HandleDistrucion();
	Destroy();
	//так будет уничтожатся башня!
	
}

void ATower::BeginPlay()
{
	Super::BeginPlay();
	Tansk= Cast<ATansk>(UGameplayStatics::GetPlayerPawn(this,0));
	//я пока не понял но закоменчу. вызываем менеджер по таймеру, устанавливаем таймер.
	//(указываем перменну что связанны с таймером, далье указываем на этот же класс где должен сработать таймер,
	// указываем ссылку на функции где будет срабатывать таймер, указываем перменную через сколько должен срабатывтаь таймер (2 секунды), а булевая отвечает за цикличность)
	GetWorldTimerManager().SetTimer(FierRateTimerHandle,this,&ATower::CheckFierCondition,FierRate,true);
}

void ATower::CheckFierCondition()
{
	
	if (InFierRange())
	{
		Fier();
	}
}

bool ATower::InFierRange()
{
	if (Tansk)
	{
		float Distance =FVector::Dist(GetActorLocation(), Tansk->GetActorLocation());
		if (Distance<=Fier_Range)
		{
			return true;;
		}
	}
	return false;
}
