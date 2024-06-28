// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"


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
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	//так будет взаиможействовать снаряд с мешом актера
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	// Получаем владельца снаряда
	auto MyOwner =GetOwner();
	// Если у снаряда нет владельца, выходим из функции
	if (MyOwner==nullptr) return;
	// Получаем контроллер владельца (инициатор)
	auto MyOwnerInstigator = MyOwner->GetInstigatorController();
	// Определяем класс типа урона (по умолчанию)
	auto DamageTypeClass=UDamageType::StaticClass();
	// Проверяем, что столкнувшийся актер валиден и не является самим снарядом или его владельцем
	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		// Наносим урон столкнувшемуся актеру
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, DamageTypeClass);
		// Уничтожаем снаряд после столкновения
		Destroy();
	}


}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

