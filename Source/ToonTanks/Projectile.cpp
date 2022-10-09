// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile"));
	RootComponent = ProjectileMesh;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("Movement Component");
	MovementComponent->InitialSpeed = 100;
	MovementComponent->MaxSpeed = 500;

	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail"));
	TrailParticles->SetupAttachment(RootComponent);

	UGameplayStatics::PlaySoundAtLocation(
		this,
		LaunchSound,
		 GetActorLocation(),
		 GetActorRotation()
	);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	auto MyOwner = GetOwner();
	if (MyOwner)
	{
		auto BaseOwnerInstigator = MyOwner->GetInstigatorController();
		auto DamageTypeClass = UDamageType::StaticClass();

		if (OtherActor && OtherActor != this && OtherActor != MyOwner)
		{
			UGameplayStatics::ApplyDamage(
				OtherActor,
				Damage,
				BaseOwnerInstigator,
				this,
				DamageTypeClass
			);
			if (HitParticles)
			{
				UGameplayStatics::SpawnEmitterAtLocation(
					this,
					HitParticles,
					GetActorLocation(),
					GetActorRotation()
				);
			}
			if (HitSound)
			{
				UGameplayStatics::PlaySoundAtLocation(
					this,
					HitSound,
					GetActorLocation(),
					GetActorRotation()
				);
			}
			if (HitCameraShakeClass)
			{
				GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
			}
		}
	}
	Destroy();
}

