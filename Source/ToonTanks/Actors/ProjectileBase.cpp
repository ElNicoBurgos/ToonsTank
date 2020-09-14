// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->InitialSpeed = ProjectileSpeed;
	ProjectileMovement->MaxSpeed = ProjectileSpeed;
	InitialLifeSpan = 3.f;
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Try to get a reference to the owning class.
	AActor* MyOwer = GetOwner();

	// If for some reason we can't get a valid reference, return as we need to check against the owner. 
	if (!MyOwer) { return; }

	// If the other ISN'T self OR Owner AND exists, then apply damage. 
	if (OtherActor && OtherActor != this && OtherActor != MyOwer)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwer->GetInstigatorController(), this, DamageType);
		UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation());
		Destroy();

	}

}


