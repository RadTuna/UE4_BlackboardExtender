// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BlackboardExtenderEditor/Classes/BEBehaviorTreeGraph.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBEBehaviorTreeGraph() {}
// Cross Module References
	BLACKBOARDEXTENDEREDITOR_API UClass* Z_Construct_UClass_UBEBehaviorTreeGraph_NoRegister();
	BLACKBOARDEXTENDEREDITOR_API UClass* Z_Construct_UClass_UBEBehaviorTreeGraph();
	AIGRAPH_API UClass* Z_Construct_UClass_UAIGraph();
	UPackage* Z_Construct_UPackage__Script_BlackboardExtenderEditor();
// End Cross Module References
	void UBEBehaviorTreeGraph::StaticRegisterNativesUBEBehaviorTreeGraph()
	{
	}
	UClass* Z_Construct_UClass_UBEBehaviorTreeGraph_NoRegister()
	{
		return UBEBehaviorTreeGraph::StaticClass();
	}
	struct Z_Construct_UClass_UBEBehaviorTreeGraph_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bIsUsingModCounter_MetaData[];
#endif
		static void NewProp_bIsUsingModCounter_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bIsUsingModCounter;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ModCounter_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_ModCounter;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UBEBehaviorTreeGraph_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UAIGraph,
		(UObject* (*)())Z_Construct_UPackage__Script_BlackboardExtenderEditor,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBEBehaviorTreeGraph_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "BEBehaviorTreeGraph.h" },
		{ "ModuleRelativePath", "Classes/BEBehaviorTreeGraph.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBEBehaviorTreeGraph_Statics::NewProp_bIsUsingModCounter_MetaData[] = {
		{ "ModuleRelativePath", "Classes/BEBehaviorTreeGraph.h" },
	};
#endif
	void Z_Construct_UClass_UBEBehaviorTreeGraph_Statics::NewProp_bIsUsingModCounter_SetBit(void* Obj)
	{
		((UBEBehaviorTreeGraph*)Obj)->bIsUsingModCounter = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UBEBehaviorTreeGraph_Statics::NewProp_bIsUsingModCounter = { "bIsUsingModCounter", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UBEBehaviorTreeGraph), &Z_Construct_UClass_UBEBehaviorTreeGraph_Statics::NewProp_bIsUsingModCounter_SetBit, METADATA_PARAMS(Z_Construct_UClass_UBEBehaviorTreeGraph_Statics::NewProp_bIsUsingModCounter_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBEBehaviorTreeGraph_Statics::NewProp_bIsUsingModCounter_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBEBehaviorTreeGraph_Statics::NewProp_ModCounter_MetaData[] = {
		{ "Comment", "/** increased with every graph rebuild, used to refresh data from subtrees */" },
		{ "ModuleRelativePath", "Classes/BEBehaviorTreeGraph.h" },
		{ "ToolTip", "increased with every graph rebuild, used to refresh data from subtrees" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_UBEBehaviorTreeGraph_Statics::NewProp_ModCounter = { "ModCounter", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBEBehaviorTreeGraph, ModCounter), METADATA_PARAMS(Z_Construct_UClass_UBEBehaviorTreeGraph_Statics::NewProp_ModCounter_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBEBehaviorTreeGraph_Statics::NewProp_ModCounter_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UBEBehaviorTreeGraph_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBEBehaviorTreeGraph_Statics::NewProp_bIsUsingModCounter,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBEBehaviorTreeGraph_Statics::NewProp_ModCounter,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UBEBehaviorTreeGraph_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBEBehaviorTreeGraph>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UBEBehaviorTreeGraph_Statics::ClassParams = {
		&UBEBehaviorTreeGraph::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UBEBehaviorTreeGraph_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UBEBehaviorTreeGraph_Statics::PropPointers),
		0,
		0x000000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UBEBehaviorTreeGraph_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UBEBehaviorTreeGraph_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UBEBehaviorTreeGraph()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UBEBehaviorTreeGraph_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UBEBehaviorTreeGraph, 902807651);
	template<> BLACKBOARDEXTENDEREDITOR_API UClass* StaticClass<UBEBehaviorTreeGraph>()
	{
		return UBEBehaviorTreeGraph::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UBEBehaviorTreeGraph(Z_Construct_UClass_UBEBehaviorTreeGraph, &UBEBehaviorTreeGraph::StaticClass, TEXT("/Script/BlackboardExtenderEditor"), TEXT("UBEBehaviorTreeGraph"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UBEBehaviorTreeGraph);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
