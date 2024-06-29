// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include  "Components/SceneComponent.h"
#include  "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Projectile.h"
#include "Particles/ParticleSystem.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    CapsuleComp=CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	RootComponent=CapsuleComp;
	
	BaseMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);
	
	TurretsMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	TurretsMesh->SetupAttachment(BaseMesh);

	ProjectileSpawn=CreateDefaultSubobject<USceneComponent>(TEXT("Spaw Point"));
	ProjectileSpawn->SetupAttachment(TurretsMesh);
	
}

void ABasePawn::HandleDistrucion()
{
	if (DeathParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation(), GetActorRotation());
	}
	
	if (DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}

}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	//партикал спецэфект на уничтожение обьекта танка/турели
	

	
}

void ABasePawn::RotateTuret(FVector LookAtTarget)
{
	FVector ToTarget=LookAtTarget-TurretsMesh->GetComponentLocation();//  берем местоположение меша башни и отнимае от вектора куда смотри башня LookAtTarget
	FRotator LookAtRotation=FRotator(0.0f,ToTarget.Rotation().Yaw,0.0f);
	TurretsMesh->SetWorldRotation(FMath::RInterpTo(TurretsMesh->GetComponentRotation(),LookAtRotation,UGameplayStatics::GetWorldDeltaSeconds(this), 5.0f));

	//так указівается что нужны координатыпо Yaw , а остальные оставим по нулю.

}
//стрельба
void ABasePawn::Fier()
{
	// Получаем местоположение компонента, откуда будет запускаться снаряд
	FVector Location=ProjectileSpawn->GetComponentLocation() ;
	// Получаем ориентацию (вращение) компонента, откуда будет запускаться снаряд
	FRotator Rotation=ProjectileSpawn->GetComponentRotation();
	// Спавним (создаем) снаряд в мире игры по указанным координатам и ориентации
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,Location,Rotation);
	// Устанавливаем владельца для снаряда
	// Это важно для определения, кто именно выпустил снаряд, что может использоваться для
	// учета урона и других взаимодействий в игре
		Projectile->SetOwner(this);
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//FVector DeltaLocation (0.0f);
	//DeltaLocation.X=2.0f;
	//AddActorLocalOffset(DeltaLocation);
	//так будут двигатся все обьекты (танки с турелями ) по Х. все эти три строки за это отвичают

}




