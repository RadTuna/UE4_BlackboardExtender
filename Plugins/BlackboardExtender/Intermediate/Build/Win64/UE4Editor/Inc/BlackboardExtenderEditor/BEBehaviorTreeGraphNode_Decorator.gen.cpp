// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BlackboardExtenderEditor/Classes/BEBehaviorTreeGraphNode_Decorator.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBEBehaviorTreeGraphNode_Decorator() {}
// Cross Module References
	BLACKBOARDEXTENDEREDITOR_API UClass* Z_Construct_UClass_UBEBehaviorTreeGraphNode_Decorator_NoRegister();
	BLACKBOARDEXTENDEREDITOR_API UClass* Z_Construct_UClass_UBEBehaviorTreeGraphNode_Decorator();
	BLACKBOARDEXTENDEREDITOR_API UClass* Z_Construct_UClass_UBEBehaviorTreeGraphNode();
	UPackage* Z_Construct_UPackage__Script_BlackboardExtenderEditor();
// End Cross Module References
	void UBEBehaviorTreeGraphNode_Decorator::StaticRegisterNativesUBEBehaviorTreeGraphNode_Decorator()
	{
	}
	UClass* Z_Construct_UClass_UBEBehaviorTreeGraphNode_Decorator_NoRegister()
	{
		return UBEBehaviorTreeGraphNode_Decorator::StaticClass();
	}
	struct Z_Construct_UClass_UBEBehaviorTreeGraphNode_Decorator_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UBEBehaviorTreeGraphNode_Decorator_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBEBehaviorTreeGraphNode,
		(UObject* (*)())Z_Construct_UPackage__Script_BlackboardExtenderEditor,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBEBehaviorTreeGraphNode_Decorator_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "BEBehaviorTreeGraphNode_Decorator.h" },
		{ "ModuleRelativePath", "Classes/BEBehaviorTreeGraphNode_Decorator.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UBEBehaviorTreeGraphNode_Decorator_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBEBehaviorTreeGraphNode_Decorator>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UBEBehaviorTreeGraphNode_Decorator_Statics::ClassParams = {
		&UBEBehaviorTreeGraphNode_Decorator::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x000000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UBEBehaviorTreeGraphNode_Decorator_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UBEBehaviorTreeGraphNode_Decorator_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UBEBehaviorTreeGraphNode_Decorator()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UBEBehaviorTreeGraphNode_Decorator_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UBEBehaviorTreeGraphNode_Decorator, 2025465856);
	template<> BLACKBOARDEXTENDEREDITOR_API UClass* StaticClass<UBEBehaviorTreeGraphNode_Decorator>()
	{
		return UBEBehaviorTreeGraphNode_Decorator::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UBEBehaviorTreeGraphNode_Decorator(Z_Construct_UClass_UBEBehaviorTreeGraphNode_Decorator, &UBEBehaviorTreeGraphNode_Decorator::StaticClass, TEXT("/Script/BlackboardExtenderEditor"), TEXT("UBEBehaviorTreeGraphNode_Decorator"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UBEBehaviorTreeGraphNode_Decorator);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
