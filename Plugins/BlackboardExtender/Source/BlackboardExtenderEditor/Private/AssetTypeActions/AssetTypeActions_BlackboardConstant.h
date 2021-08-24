// Copyright RadTuna. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"



class FAssetTypeActions_BlackboardConstant : public FAssetTypeActions_Base
{
public:
	FAssetTypeActions_BlackboardConstant();
	~FAssetTypeActions_BlackboardConstant();

	// IAssetTypeActions implementation
	virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_BlackboardConstant", "Blackboard Constant"); }
	virtual FColor GetTypeColor() const override { return FColor(/*201*/ 100, 29, 85); }
	virtual UClass* GetSupportedClass() const override;
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor) override;
	virtual uint32 GetCategories() override;
	
};
