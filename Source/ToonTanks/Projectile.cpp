﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"



// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ProjectileMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent=ProjectileMesh;

	ProjectileMovementComponent=CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movment Component"));
	ProjectileMovementComponent->MaxSpeed=1300.0f; // это птолок по скорости
	ProjectileMovementComponent->InitialSpeed=1300.0f;//это по какой скорости он будет передвигатся

	TrailParticles=CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail"));
	TrailParticles->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	//так будет взаиможействовать снаряд с мешом актера
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	if (LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
	}

	
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	// Получаем владельца снаряда
	auto MyOwner =GetOwner();
	// Если у снаряда нет владельца, выходим из функции, Но 
	if (MyOwner==nullptr)
	{
		//Сначала его уничто жаем
		Destroy();
		//А потом возврощаем результат
		return;
	}
	// Получаем контроллер владельца (инициатор)
	//тут удаляем auto поскольку не рокемендуется его использовать так что меняем на AController*
	AController* MyOwnerInstigator = MyOwner->GetInstigatorController();
	// Определяем класс типа урона (по умолчанию)
	//тут удаляем auto поскольку не рокемендуется его использовать так что меняем на UClass*
	UClass* DamageTypeClass=UDamageType::StaticClass();
	// Проверяем, что столкнувшийся актер валиден и не является самим снарядом или его владельцем
	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		// Наносим урон столкнувшемуся актеру
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, DamageTypeClass);

		if (HitParticles)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this,HitParticles,GetActorLocation(),GetActorRotation());
		}
		
		if (HitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		}

		if (HitCameraShakeClass)
		{
			// UE 4.25 - ClientPlayCameraShake; UE 4.26+ ClientStartCameraShake
			GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(HitCameraShakeClass);
		}

	}
	// Уничтожаем снаряд после столкновения
	Destroy();
 
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

