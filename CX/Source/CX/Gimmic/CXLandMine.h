#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CXLandMine.generated.h"

class USphereComponent;

UCLASS()
class CX_API ACXLandMine : public AActor
{
	GENERATED_BODY()
	
public:
	ACXLandMine();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(NetMulticast, Reliable)
	void MulticastPickupEffects();

protected:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LandMine")
	TObjectPtr<USceneComponent> SceneRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LandMine")
	TObjectPtr<USphereComponent> OverlapSphere;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LandMine")
	TObjectPtr<UStaticMeshComponent> ItemMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LandMine")
	TObjectPtr<UParticleSystem> PickupParticle;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LandMine")
	TObjectPtr<USoundBase> PickupSound;
};
