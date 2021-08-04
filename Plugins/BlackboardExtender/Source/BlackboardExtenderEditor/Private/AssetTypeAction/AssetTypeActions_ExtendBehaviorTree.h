﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Toolkits/IToolkitHost.h"
#include "AssetTypeActions_Base.h"


class BLACKBOARDEXTENDEREDITOR_API FAssetTypeActions_ExtendBehaviorTree : public FAssetTypeActions_Base
{
public:
	FAssetTypeActions_ExtendBehaviorTree();
	~FAssetTypeActions_ExtendBehaviorTree();

	// IAssetTypeActions implementation
	virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_ExtendBehaviorTree", "Behavior Tree"); }
	virtual FColor GetTypeColor() const override { return FColor(149,70,255); }
	virtual UClass* GetSupportedClass() const override;
	virtual void OpenAssetEditor( const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>() ) override;
	virtual uint32 GetCategories() override;

private:
	void CreateBehaviorTreeEditor();

};