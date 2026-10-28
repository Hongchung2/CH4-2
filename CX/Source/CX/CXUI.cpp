#include "CXUI.h"
#include "ChatUI.h"
#include "Components/TextBlock.h"
#include "GameState/CXGameState.h"
#include "GameFramework/PlayerState.h"

void UCXUI::OnNewChatMessage(const FString& InSender, const FString& InMessage)
{
	UI_Chat->OnNewChatMessage(InSender, InMessage);
}

void UCXUI::UpdateSpeed(float NewSpeed)
{
	float FormattedSpeed = FMath::Abs(NewSpeed) * (bIsMPH ? 0.022f : 0.036f);

	OnSpeedUpdate(FormattedSpeed);
}

void UCXUI::UpdateGear(int32 NewGear)
{
	OnGearUpdate(NewGear);
}

void UCXUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	ACXGameState* GS = GetWorld()->GetWorld()->GetGameState<ACXGameState>();
	if (IsValid(GS) == false)
	{
		return;
	}

	RemainingTimeText->SetText(FText::AsNumber(GS->GetRemainingTime()));

	if (GS->GetCurrentGameState() == EGameState::Finished)
	{
		const bool bWin = GS->IsWinner(GetOwningPlayerState());
		ResultText->SetText(FText::FromString(bWin ? TEXT("Victory!") : TEXT("Defeat!")));
	}
	else
	{
		ResultText->SetText(FText::GetEmpty());
	}
	
}