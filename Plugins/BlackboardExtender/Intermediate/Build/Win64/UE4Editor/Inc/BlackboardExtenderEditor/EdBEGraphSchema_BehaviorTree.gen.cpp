// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BlackboardExtenderEditor/Classes/EdBEGraphSchema_BehaviorTree.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeEdBEGraphSchema_BehaviorTree() {}
// Cross Module References
	BLACKBOARDEXTENDEREDITOR_API UScriptStruct* Z_Construct_UScriptStruct_FBEBehaviorTreeSchemaAction_AutoArrange();
	UPackage* Z_Construct_UPackage__Script_BlackboardExtenderEditor();
	ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FEdGraphSchemaAction();
	BLACKBOARDEXTENDEREDITOR_API UClass* Z_Construct_UClass_UEdBEGraphSchema_BehaviorTree_NoRegister();
	BLACKBOARDEXTENDEREDITOR_API UClass* Z_Construct_UClass_UEdBEGraphSchema_BehaviorTree();
	AIGRAPH_API UClass* Z_Construct_UClass_UAIGraphSchema();
// End Cross Module References
class UScriptStruct* FBEBehaviorTreeSchemaAction_AutoArrange::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern BLACKBOARDEXTENDEREDITOR_API uint32 Get_Z_Construct_UScriptStruct_FBEBehaviorTreeSchemaAction_AutoArrange_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FBEBehaviorTreeSchemaAction_AutoArrange, Z_Construct_UPackage__Script_BlackboardExtenderEditor(), TEXT("BEBehaviorTreeSchemaAction_AutoArrange"), sizeof(FBEBehaviorTreeSchemaAction_AutoArrange), Get_Z_Construct_UScriptStruct_FBEBehaviorTreeSchemaAction_AutoArrange_Hash());
	}
	return Singleton;
}
template<> BLACKBOARDEXTENDEREDITOR_API UScriptStruct* StaticStruct<FBEBehaviorTreeSchemaAction_AutoArrange>()
{
	return FBEBehaviorTreeSchemaAction_AutoArrange::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FBEBehaviorTreeSchemaAction_AutoArrange(FBEBehaviorTreeSchemaAction_AutoArrange::StaticStruct, TEXT("/Script/BlackboardExtenderEditor"), TEXT("BEBehaviorTreeSchemaAction_AutoArrange"), false, nullptr, nullptr);
static struct FScriptStruct_BlackboardExtenderEditor_StaticRegisterNativesFBEBehaviorTreeSchemaAction_AutoArrange
{
	FScriptStruct_BlackboardExtenderEditor_StaticRegisterNativesFBEBehaviorTreeSchemaAction_AutoArrange()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("BEBehaviorTreeSchemaAction_AutoArrange")),new UScriptStruct::TCppStructOps<FBEBehaviorTreeSchemaAction_AutoArrange>);
	}
} ScriptStruct_BlackboardExtenderEditor_StaticRegisterNativesFBEBehaviorTreeSchemaAction_AutoArrange;
	struct Z_Construct_UScriptStruct_FBEBehaviorTreeSchemaAction_AutoArrange_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FBEBehaviorTreeSchemaAction_AutoArrange_Statics::Struct_MetaDataParams[] = {
		{ "Comment", "/** Action to auto arrange the graph */" },
		{ "ModuleRelativePath", "Classes/EdBEGraphSchema_BehaviorTree.h" },
		{ "ToolTip", "Action to auto arrange the graph" },
	};
#endif
	void* Z_Construct_UScriptStruct_FBEBehaviorTreeSchemaAction_AutoArrange_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FBEBehaviorTreeSchemaAction_AutoArrange>();
	}
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FBEBehaviorTreeSchemaAction_AutoArrange_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_BlackboardExtenderEditor,
		Z_Construct_UScriptStruct_FEdGraphSchemaAction,
		&NewStructOps,
		"BEBehaviorTreeSchemaAction_AutoArrange",
		sizeof(FBEBehaviorTreeSchemaAction_AutoArrange),
		alignof(FBEBehaviorTreeSchemaAction_AutoArrange),
		nullptr,
		0,
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FBEBehaviorTreeSchemaAction_AutoArrange_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBEBehaviorTreeSchemaAction_AutoArrange_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FBEBehaviorTreeSchemaAction_AutoArrange()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FBEBehaviorTreeSchemaAction_AutoArrange_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_BlackboardExtenderEditor();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("BEBehaviorTreeSchemaAction_AutoArrange"), sizeof(FBEBehaviorTreeSchemaAction_AutoArrange), Get_Z_Construct_UScriptStruct_FBEBehaviorTreeSchemaAction_AutoArrange_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FBEBehaviorTreeSchemaAction_AutoArrange_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FBEBehaviorTreeSchemaAction_AutoArrange_Hash() { return 796379529U; }
	void UEdBEGraphSchema_BehaviorTree::StaticRegisterNativesUEdBEGraphSchema_BehaviorTree()
	{
	}
	UClass* Z_Construct_UClass_UEdBEGraphSchema_BehaviorTree_NoRegister()
	{
		return UEdBEGraphSchema_BehaviorTree::StaticClass();
	}
	struct Z_Construct_UClass_UEdBEGraphSchema_BehaviorTree_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UEdBEGraphSchema_BehaviorTree_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UAIGraphSchema,
		(UObject* (*)())Z_Construct_UPackage__Script_BlackboardExtenderEditor,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UEdBEGraphSchema_BehaviorTree_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "EdBEGraphSchema_BehaviorTree.h" },
		{ "ModuleRelativePath", "Classes/EdBEGraphSchema_BehaviorTree.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UEdBEGraphSchema_BehaviorTree_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UEdBEGraphSchema_BehaviorTree>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UEdBEGraphSchema_BehaviorTree_Statics::ClassParams = {
		&UEdBEGraphSchema_BehaviorTree::StaticClass,
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
		0x000800A0u,
		METADATA_PARAMS(Z_Construct_UClass_UEdBEGraphSchema_BehaviorTree_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UEdBEGraphSchema_BehaviorTree_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UEdBEGraphSchema_BehaviorTree()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UEdBEGraphSchema_BehaviorTree_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UEdBEGraphSchema_BehaviorTree, 482925300);
	template<> BLACKBOARDEXTENDEREDITOR_API UClass* StaticClass<UEdBEGraphSchema_BehaviorTree>()
	{
		return UEdBEGraphSchema_BehaviorTree::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UEdBEGraphSchema_BehaviorTree(Z_Construct_UClass_UEdBEGraphSchema_BehaviorTree, &UEdBEGraphSchema_BehaviorTree::StaticClass, TEXT("/Script/BlackboardExtenderEditor"), TEXT("UEdBEGraphSchema_BehaviorTree"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UEdBEGraphSchema_BehaviorTree);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
