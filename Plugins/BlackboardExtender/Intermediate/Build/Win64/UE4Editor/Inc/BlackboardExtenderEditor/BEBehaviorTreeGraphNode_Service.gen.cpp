// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BlackboardExtenderEditor/Classes/BEBehaviorTreeGraphNode_Service.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBEBehaviorTreeGraphNode_Service() {}
// Cross Module References
	BLACKBOARDEXTENDEREDITOR_API UClass* Z_Construct_UClass_UBEBehaviorTreeGraphNode_Service_NoRegister();
	BLACKBOARDEXTENDEREDITOR_API UClass* Z_Construct_UClass_UBEBehaviorTreeGraphNode_Service();
	BLACKBOARDEXTENDEREDITOR_API UClass* Z_Construct_UClass_UBEBehaviorTreeGraphNode();
	UPackage* Z_Construct_UPackage__Script_BlackboardExtenderEditor();
// End Cross Module References
	void UBEBehaviorTreeGraphNode_Service::StaticRegisterNativesUBEBehaviorTreeGraphNode_Service()
	{
	}
	UClass* Z_Construct_UClass_UBEBehaviorTreeGraphNode_Service_NoRegister()
	{
		return UBEBehaviorTreeGraphNode_Service::StaticClass();
	}
	struct Z_Construct_UClass_UBEBehaviorTreeGraphNode_Service_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UBEBehaviorTreeGraphNode_Service_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBEBehaviorTreeGraphNode,
		(UObject* (*)())Z_Construct_UPackage__Script_BlackboardExtenderEditor,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBEBehaviorTreeGraphNode_Service_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "BEBehaviorTreeGraphNode_Service.h" },
		{ "ModuleRelativePath", "Classes/BEBehaviorTreeGraphNode_Service.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UBEBehaviorTreeGraphNode_Service_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBEBehaviorTreeGraphNode_Service>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UBEBehaviorTreeGraphNode_Service_Statics::ClassParams = {
		&UBEBehaviorTreeGraphNode_Service::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_UBEBehaviorTreeGraphNode_Service_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UBEBehaviorTreeGraphNode_Service_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UBEBehaviorTreeGraphNode_Service()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UBEBehaviorTreeGraphNode_Service_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UBEBehaviorTreeGraphNode_Service, 1941096702);
	template<> BLACKBOARDEXTENDEREDITOR_API UClass* StaticClass<UBEBehaviorTreeGraphNode_Service>()
	{
		return UBEBehaviorTreeGraphNode_Service::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UBEBehaviorTreeGraphNode_Service(Z_Construct_UClass_UBEBehaviorTreeGraphNode_Service, &UBEBehaviorTreeGraphNode_Service::StaticClass, TEXT("/Script/BlackboardExtenderEditor"), TEXT("UBEBehaviorTreeGraphNode_Service"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UBEBehaviorTreeGraphNode_Service);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
