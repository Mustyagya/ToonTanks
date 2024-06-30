// Fill out your copyright notice in the Description page of Project Settings.


#include "Tansk.h"
#include"GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
//это библа для высчитывания дельтатайм

ATansk::ATansk()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring ARM"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera "));
	Camera->SetupAttachment(SpringArm);
}



//передвижение вперед/назад
void ATansk::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATansk::moved);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATansk::turn);
//так биндится действие на стрельбу.
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed ,this, &ATansk::Fier );
}

void ATansk::HandleDistrucion()
{
	Super::HandleDistrucion();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	//вот так будет прятать танк когда закончатся ХП!
	bAlive = false;
}

void ATansk::BeginPlay()
{
	Super::BeginPlay();
	TanskPlayerController= Cast<APlayerController>(GetController());

	}

void ATansk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(TanskPlayerController)
	{
		FHitResult HitResult;
		TanskPlayerController->GetHitResultUnderCursor(ECC_Visibility,false,HitResult);
		//DrawDebugSphere(GetWorld(),HitResult.ImpactPoint,25.0f,7,FColor::Red,false,-1.0f);
		RotateTuret (HitResult.ImpactPoint);

	}
}

// передвижение влев/вправо
void ATansk::moved(float value)
{
	FVector Deltalocation=FVector::ZeroVector;
	Deltalocation.X=value*Speed_Tank*UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(Deltalocation,true);
	//bSweep true, это пзволяет танку проходить сквозь обьекты, но в движке включить нужно блокировку колизии в капсуле
	//вот теперь танк будет двигатся по Х но только теперь через кнопки

}
//поворот влево и вправо
void ATansk::turn(float value)
{
	FRotator DeltaRotation=FRotator::ZeroRotator;
	DeltaRotation.Yaw=value*Turn_Rate*UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(DeltaRotation);
}

