// Copyright RadTuna. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BlackboardConstant.h"
#include "IDetailCustomization.h"


class FBlackboardConstantDetails : public IDetailCustomization
{
public:
	FBlackboardConstantDetails();

	static TSharedRef<IDetailCustomization> MakeInstance();

	// IDetailCustomization interface
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

private:
	TWeakObjectPtr<UBlackboardConstant> BlackboardConstantCached;
	
};
