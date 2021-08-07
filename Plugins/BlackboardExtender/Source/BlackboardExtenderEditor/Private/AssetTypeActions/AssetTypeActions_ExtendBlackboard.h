// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Toolkits/IToolkitHost.h"
#include "AssetTypeActions_Base.h"


class BLACKBOARDEXTENDEREDITOR_API FAssetTypeActions_ExtendBlackboard : public FAssetTypeActions_Base
{
public:
	FAssetTypeActions_ExtendBlackboard();
	~FAssetTypeActions_ExtendBlackboard();

	// IAssetTypeActions implementation
	virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_ExtendBlackboard", "Extended Blackboard"); }
	virtual FColor GetTypeColor() const override { return FColor(201, 29, 85); }
	virtual UClass* GetSupportedClass() const override;
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor) override;
	virtual uint32 GetCategories() override;
	
};
