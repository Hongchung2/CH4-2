#include "PlayerState/CXPlayerState.h"
#include "Net/UnrealNetwork.h"

static int32 GMyTestCoin = 0;
static FAutoConsoleVariableRef CVarMyCustomDebugToggle(
	TEXT("cheat.addcoin"),
	GMyTestCoin,
	TEXT("코인을 입력한 수치만큼 증가 시킵니다."),
	FConsoleVariableDelegate::CreateLambda([](IConsoleVariable* CVar)
		{
			if (CVar)
			{
				UE_LOG(LogTemp, Warning, TEXT("콘솔 변수 변경됨 현재 값: %d"), CVar->GetInt());
				UE_LOG(LogTemp, Warning, TEXT("콘솔 변수 변경됨 GMyTestCoin 값: %d"), GMyTestCoin);

				if (GWorld)
				{
					if (GWorld->GetFirstPlayerController())
					{
						GWorld->GetFirstPlayerController()->GetPlayerState<ACXPlayerState>()->AddCoins(GMyTestCoin);
					}
				}
				GMyTestCoin = 0;
			}
		}),
	ECVF_Cheat
);

static FAutoConsoleVariableRef CVarAddCoinClient(TEXT("cheat.addcoin.client"), GMyTestCoin, TEXT("add coin test for client only"),
	FConsoleVariableDelegate::CreateLambda([](IConsoleVariable* CVar)
		{
			UE_LOG(LogTemp, Warning, TEXT("콘솔 변수 변경됨! GMyTestCoin 값: %d"), GMyTestCoin);

			if (GWorld)
			{
				if (GWorld->GetFirstPlayerController())
				{
					GWorld->GetFirstPlayerController()->GetPlayerState <ACXPlayerState>()->Coins += GMyTestCoin;
				}
			}
			GMyTestCoin = 0;
		}),
	ECVF_Cheat
);



ACXPlayerState::ACXPlayerState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACXPlayerState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (HasAuthority() == false)
	{
		return;
	}

	// 음수일 때만 회복, 0을 넘지 않게 제한
	if (BonusMaxSpeed < 0.f)
	{
		BonusMaxSpeed = FMath::Min(BonusMaxSpeed + PenaltyRecoveryPerSecond * DeltaSeconds, 0.f);
	}
}

void ACXPlayerState::CTSAddCoin_Implementation(const int32& Amount)
{
	AddCoins(Amount);
}

void ACXPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ThisClass, Coins, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(ThisClass, BonusMaxSpeed, COND_OwnerOnly) ;
}

void ACXPlayerState::AddCoins(int32 Amount)
{
	if (HasAuthority() == false || Amount <= 0)
	{
		return;
	}

	FString PlayerName = GetPlayerName();
	Coins += Amount;
	UE_LOG(LogTemp, Warning, TEXT("%s - AddCoins: %d(+%d"), *PlayerName, Coins, Amount);
}

bool ACXPlayerState::TryRemoveCoins(int32 Amount)
{
	if (HasAuthority() == false || Amount <= 0 || Coins < 5)
	{
		return false;
	}

	Coins -= Amount;
	return true;
}

void ACXPlayerState::AddBonusMaxSpeed(float Amount)
{
	if (HasAuthority() == false || Amount <= 0.f)
	{
		return;
	}

	BonusMaxSpeed += Amount;
}

FString ACXPlayerState::GetPlayerStateInfo() const
{
	return FString::Printf(TEXT("Coins: %d, BonusMaxSpeed: %.2f"), Coins, BonusMaxSpeed);
}

void ACXPlayerState::ApplyWheelHitPenalty()
{
	if (HasAuthority() == false)
	{
		return;
	}

	BonusMaxSpeed -= WheelHitPenalty;
	ForceNetUpdate(); // 맞은 순간 바로 클라에 반영
}

