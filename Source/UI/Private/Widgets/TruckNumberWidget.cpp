#include "Widgets/TruckNumberWidget.h"
#include "Components/TextBlock.h"

void UTruckNumberWidget::SetTruckNumberText(FText InText)
{
	TextBlockTruckNumber->SetText(InText);
}

int UTruckNumberWidget::GetTruckNumber() const
{
	auto Str = TextBlockTruckNumber->GetText().ToString();
	return FCString::Atoi(*Str);
}
