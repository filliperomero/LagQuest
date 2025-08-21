// Copyright Fillipe Romero. All Rights Reserved.

#include "UI/Lq_PickupCountWidget.h"
#include "Components/TextBlock.h"

void ULq_PickupCountWidget::SetPickupCount(const int32 Count) const
{
	Text_PickupCount->SetText(FText::AsNumber(Count));
}
