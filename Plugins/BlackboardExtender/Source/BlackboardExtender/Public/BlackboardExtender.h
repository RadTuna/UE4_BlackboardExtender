// Copyright 2021 RadTuna. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class FToolBarBuilder;
class FMenuBuilder;

class BLACKBOARDEXTENDER_API FBlackboardExtenderModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
