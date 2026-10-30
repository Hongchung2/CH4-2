#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "CXPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class CX_API ACXPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	ACXPlayerState();
	virtual void Tick(float DeltaSeconds) override;

	void ApplyWheelHitPenalty();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Penalty")
	float WheelHitPenalty = 20.f; // 한 번 맞을 때 줄어드는 속도 피해량
	UPROPERTY(EditDefaultsOnly, Category = "Penalty")
	float PenaltyRecoveryPerSecond = 5.f; // 초당 속도 회복량

public:
	UFUNCTION(Client, Reliable)
	void CTSAddCoin(const int32& Amount);
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


	int32 GetCoins() const { return Coins; }
	float GetBonusMaxSPeed() const { return BonusMaxSpeed; }

	void AddCoins(int32 Amount);
	bool TryRemoveCoins(int32 Amount);

	void AddBonusMaxSpeed(float Amount);

	UFUNCTION(BlueprintCallable)
	FString GetPlayerStateInfo() const;

public:
	UPROPERTY(Replicated)
	int32 Coins = 0;

	UPROPERTY(Replicated)
	float BonusMaxSpeed = 0.f;
};
