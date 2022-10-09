// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	 
	// Sets default values for this actor's properties
	AProjectile();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnHit(
		UPrimitiveComponent* HitComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit
	);
	
private:
	UPROPERTY(EditAnywhere)
	float Damage = 50.f;
	
	UPROPERTY(VisibleAnywhere,  Category = "Movement")
	class UProjectileMovementComponent* MovementComponent;
// BulletMesh
    UPROPERTY(EditDefaultsOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* ProjectileMesh;
// Visual
	UPROPERTY(EditAnywhere, Category = "Combat")
    UParticleSystem* HitParticles;
	
    UPROPERTY(EditAnywhere, Category = "Combat")
    UParticleSystemComponent* TrailParticles;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<UCameraShakeBase> HitCameraShakeClass;
// Sound
	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* HitSound;
};