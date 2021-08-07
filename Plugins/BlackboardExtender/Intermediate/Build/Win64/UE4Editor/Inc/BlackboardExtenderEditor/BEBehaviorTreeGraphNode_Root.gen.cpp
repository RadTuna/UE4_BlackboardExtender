// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BlackboardExtenderEditor/Classes/BEBehaviorTreeGraphNode_Root.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBEBehaviorTreeGraphNode_Root() {}
// Cross Module References
	BLACKBOARDEXTENDEREDITOR_API UClass* Z_Construct_UClass_UBEBehaviorTreeGraphNode_Root_NoRegister();
	BLACKBOARDEXTENDEREDITOR_API UClass* Z_Construct_UClass_UBEBehaviorTreeGraphNode_Root();
	BLACKBOARDEXTENDEREDITOR_API UClass* Z_Construct_UClass_UBEBehaviorTreeGraphNode();
	UPackage* Z_Construct_UPackage__Script_BlackboardExtenderEditor();
	AIMODULE_API UClass* Z_Construct_UClass_UBlackboardData_NoRegister();
// End Cross Module References
	void UBEBehaviorTreeGraphNode_Root::StaticRegisterNativesUBEBehaviorTreeGraphNode_Root()
	{
	}
	UClass* Z_Construct_UClass_UBEBehaviorTreeGraphNode_Root_NoRegister()
	{
		return UBEBehaviorTreeGraphNode_Root::StaticClass();
	}
	struct Z_Construct_UClass_UBEBehaviorTreeGraphNode_Root_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BlackboardAsset_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_BlackboardAsset;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UBEBehaviorTreeGraphNode_Root_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBEBehaviorTreeGraphNode,
		(UObject* (*)())Z_Construct_UPackage__Script_BlackboardExtenderEditor,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBEBehaviorTreeGraphNode_Root_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/** Root node of this behavior tree, holds Blackboard data */" },
		{ "IncludePath", "BEBehaviorTreeGraphNode_Root.h" },
		{ "ModuleRelativePath", "Classes/BEBehaviorTreeGraphNode_Root.h" },
		{ "ToolTip", "Root node of this behavior tree, holds Blackboard data" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBEBehaviorTreeGraphNode_Root_Statics::NewProp_BlackboardAsset_MetaData[] = {
		{ "Category", "AI|BehaviorTree" },
		{ "ModuleRelativePath", "Classes/BEBehaviorTreeGraphNode_Root.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UBEBehaviorTreeGraphNode_Root_Statics::NewProp_BlackboardAsset = { "BlackboardAsset", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBEBehaviorTreeGraphNode_Root, BlackboardAsset), Z_Construct_UClass_UBlackboardData_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UBEBehaviorTreeGraphNode_Root_Statics::NewProp_BlackboardAsset_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBEBehaviorTreeGraphNode_Root_Statics::NewProp_BlackboardAsset_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UBEBehaviorTreeGraphNode_Root_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBEBehaviorTreeGraphNode_Root_Statics::NewProp_BlackboardAsset,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UBEBehaviorTreeGraphNode_Root_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBEBehaviorTreeGraphNode_Root>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UBEBehaviorTreeGraphNode_Root_Statics::ClassParams = {
		&UBEBehaviorTreeGraphNode_Root::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UBEBehaviorTreeGraphNode_Root_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UBEBehaviorTreeGraphNode_Root_Statics::PropPointers),
		0,
		0x000000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UBEBehaviorTreeGraphNode_Root_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UBEBehaviorTreeGraphNode_Root_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UBEBehaviorTreeGraphNode_Root()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UBEBehaviorTreeGraphNode_Root_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UBEBehaviorTreeGraphNode_Root, 3929090121);
	template<> BLACKBOARDEXTENDEREDITOR_API UClass* StaticClass<UBEBehaviorTreeGraphNode_Root>()
	{
		return UBEBehaviorTreeGraphNode_Root::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UBEBehaviorTreeGraphNode_Root(Z_Construct_UClass_UBEBehaviorTreeGraphNode_Root, &UBEBehaviorTreeGraphNode_Root::StaticClass, TEXT("/Script/BlackboardExtenderEditor"), TEXT("UBEBehaviorTreeGraphNode_Root"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UBEBehaviorTreeGraphNode_Root);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
