// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Lq_PickupCountWidget.generated.h"

class UTextBlock;

UCLASS()
class LAGQUEST_API ULq_PickupCountWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetPickupCount(const int32 Count) const;

private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Text_PickupCount;
};
