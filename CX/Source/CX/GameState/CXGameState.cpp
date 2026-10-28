#include "GameState/CXGameState.h"
#include "Net/UnrealNetwork.h"
#include "PlayerState/CXPlayerState.h"
#include "GameFramework/PlayerState.h"

void ACXGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, CurrentGameState);
	DOREPLIFETIME(ThisClass, RemainingTime);
	DOREPLIFETIME(ThisClass, Winners);
}

void ACXGameState::SetGameState(EGameState NewGameState)
{
	if (!HasAuthority())
	{
		return;
	}

	CurrentGameState = NewGameState;
}

void ACXGameState::SetRemainingTime(int32 NewRemainingTime)
{
	if (!HasAuthority())
	{
		return;
	}

	RemainingTime = FMath::Max(0, NewRemainingTime);
}

bool ACXGameState::IsWinner(APlayerState* InPlayerState) const
{
	ACXPlayerState* CXPS = Cast<ACXPlayerState>(InPlayerState);
	return IsValid(CXPS) && Winners.Contains(CXPS);
}