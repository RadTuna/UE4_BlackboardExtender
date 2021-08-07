// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BlackboardExtenderEditor/Classes/EdBEGraphSchema_BehaviorTreeDecorator.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeEdBEGraphSchema_BehaviorTreeDecorator() {}
// Cross Module References
	BLACKBOARDEXTENDEREDITOR_API UScriptStruct* Z_Construct_UScriptStruct_FBEDecoratorSchemaAction_NewNode();
	UPackage* Z_Construct_UPackage__Script_BlackboardExtenderEditor();
	ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FEdGraphSchemaAction();
	BLACKBOARDEXTENDEREDITOR_API UClass* Z_Construct_UClass_UBEBehaviorTreeDecoratorGraphNode_NoRegister();
	BLACKBOARDEXTENDEREDITOR_API UClass* Z_Construct_UClass_UEdBEGraphSchema_BehaviorTreeDecorator_NoRegister();
	BLACKBOARDEXTENDEREDITOR_API UClass* Z_Construct_UClass_UEdBEGraphSchema_BehaviorTreeDecorator();
	ENGINE_API UClass* Z_Construct_UClass_UEdGraphSchema();
// End Cross Module References
class UScriptStruct* FBEDecoratorSchemaAction_NewNode::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern BLACKBOARDEXTENDEREDITOR_API uint32 Get_Z_Construct_UScriptStruct_FBEDecoratorSchemaAction_NewNode_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FBEDecoratorSchemaAction_NewNode, Z_Construct_UPackage__Script_BlackboardExtenderEditor(), TEXT("BEDecoratorSchemaAction_NewNode"), sizeof(FBEDecoratorSchemaAction_NewNode), Get_Z_Construct_UScriptStruct_FBEDecoratorSchemaAction_NewNode_Hash());
	}
	return Singleton;
}
template<> BLACKBOARDEXTENDEREDITOR_API UScriptStruct* StaticStruct<FBEDecoratorSchemaAction_NewNode>()
{
	return FBEDecoratorSchemaAction_NewNode::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FBEDecoratorSchemaAction_NewNode(FBEDecoratorSchemaAction_NewNode::StaticStruct, TEXT("/Script/BlackboardExtenderEditor"), TEXT("BEDecoratorSchemaAction_NewNode"), false, nullptr, nullptr);
static struct FScriptStruct_BlackboardExtenderEditor_StaticRegisterNativesFBEDecoratorSchemaAction_NewNode
{
	FScriptStruct_BlackboardExtenderEditor_StaticRegisterNativesFBEDecoratorSchemaAction_NewNode()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("BEDecoratorSchemaAction_NewNode")),new UScriptStruct::TCppStructOps<FBEDecoratorSchemaAction_NewNode>);
	}
} ScriptStruct_BlackboardExtenderEditor_StaticRegisterNativesFBEDecoratorSchemaAction_NewNode;
	struct Z_Construct_UScriptStruct_FBEDecoratorSchemaAction_NewNode_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_NodeTemplate_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_NodeTemplate;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FBEDecoratorSchemaAction_NewNode_Statics::Struct_MetaDataParams[] = {
		{ "Comment", "/** Action to add a node to the graph */" },
		{ "ModuleRelativePath", "Classes/EdBEGraphSchema_BehaviorTreeDecorator.h" },
		{ "ToolTip", "Action to add a node to the graph" },
	};
#endif
	void* Z_Construct_UScriptStruct_FBEDecoratorSchemaAction_NewNode_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FBEDecoratorSchemaAction_NewNode>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FBEDecoratorSchemaAction_NewNode_Statics::NewProp_NodeTemplate_MetaData[] = {
		{ "Comment", "/** Template of node we want to create */" },
		{ "ModuleRelativePath", "Classes/EdBEGraphSchema_BehaviorTreeDecorator.h" },
		{ "ToolTip", "Template of node we want to create" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FBEDecoratorSchemaAction_NewNode_Statics::NewProp_NodeTemplate = { "NodeTemplate", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FBEDecoratorSchemaAction_NewNode, NodeTemplate), Z_Construct_UClass_UBEBehaviorTreeDecoratorGraphNode_NoRegister, METADATA_PARAMS(Z_Construct_UScriptStruct_FBEDecoratorSchemaAction_NewNode_Statics::NewProp_NodeTemplate_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBEDecoratorSchemaAction_NewNode_Statics::NewProp_NodeTemplate_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FBEDecoratorSchemaAction_NewNode_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBEDecoratorSchemaAction_NewNode_Statics::NewProp_NodeTemplate,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FBEDecoratorSchemaAction_NewNode_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_BlackboardExtenderEditor,
		Z_Construct_UScriptStruct_FEdGraphSchemaAction,
		&NewStructOps,
		"BEDecoratorSchemaAction_NewNode",
		sizeof(FBEDecoratorSchemaAction_NewNode),
		alignof(FBEDecoratorSchemaAction_NewNode),
		Z_Construct_UScriptStruct_FBEDecoratorSchemaAction_NewNode_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBEDecoratorSchemaAction_NewNode_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FBEDecoratorSchemaAction_NewNode_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBEDecoratorSchemaAction_NewNode_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FBEDecoratorSchemaAction_NewNode()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FBEDecoratorSchemaAction_NewNode_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_BlackboardExtenderEditor();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("BEDecoratorSchemaAction_NewNode"), sizeof(FBEDecoratorSchemaAction_NewNode), Get_Z_Construct_UScriptStruct_FBEDecoratorSchemaAction_NewNode_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FBEDecoratorSchemaAction_NewNode_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FBEDecoratorSchemaAction_NewNode_Hash() { return 3829824035U; }
	void UEdBEGraphSchema_BehaviorTreeDecorator::StaticRegisterNativesUEdBEGraphSchema_BehaviorTreeDecorator()
	{
	}
	UClass* Z_Construct_UClass_UEdBEGraphSchema_BehaviorTreeDecorator_NoRegister()
	{
		return UEdBEGraphSchema_BehaviorTreeDecorator::StaticClass();
	}
	struct Z_Construct_UClass_UEdBEGraphSchema_BehaviorTreeDecorator_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PC_Boolean_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_PC_Boolean;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UEdBEGraphSchema_BehaviorTreeDecorator_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UEdGraphSchema,
		(UObject* (*)())Z_Construct_UPackage__Script_BlackboardExtenderEditor,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UEdBEGraphSchema_BehaviorTreeDecorator_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "EdBEGraphSchema_BehaviorTreeDecorator.h" },
		{ "ModuleRelativePath", "Classes/EdBEGraphSchema_BehaviorTreeDecorator.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UEdBEGraphSchema_BehaviorTreeDecorator_Statics::NewProp_PC_Boolean_MetaData[] = {
		{ "ModuleRelativePath", "Classes/EdBEGraphSchema_BehaviorTreeDecorator.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UEdBEGraphSchema_BehaviorTreeDecorator_Statics::NewProp_PC_Boolean = { "PC_Boolean", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UEdBEGraphSchema_BehaviorTreeDecorator, PC_Boolean), METADATA_PARAMS(Z_Construct_UClass_UEdBEGraphSchema_BehaviorTreeDecorator_Statics::NewProp_PC_Boolean_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UEdBEGraphSchema_BehaviorTreeDecorator_Statics::NewProp_PC_Boolean_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UEdBEGraphSchema_BehaviorTreeDecorator_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEdBEGraphSchema_BehaviorTreeDecorator_Statics::NewProp_PC_Boolean,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UEdBEGraphSchema_BehaviorTreeDecorator_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UEdBEGraphSchema_BehaviorTreeDecorator>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UEdBEGraphSchema_BehaviorTreeDecorator_Statics::ClassParams = {
		&UEdBEGraphSchema_BehaviorTreeDecorator::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UEdBEGraphSchema_BehaviorTreeDecorator_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UEdBEGraphSchema_BehaviorTreeDecorator_Statics::PropPointers),
		0,
		0x000800A0u,
		METADATA_PARAMS(Z_Construct_UClass_UEdBEGraphSchema_BehaviorTreeDecorator_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UEdBEGraphSchema_BehaviorTreeDecorator_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UEdBEGraphSchema_BehaviorTreeDecorator()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UEdBEGraphSchema_BehaviorTreeDecorator_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UEdBEGraphSchema_BehaviorTreeDecorator, 2003438471);
	template<> BLACKBOARDEXTENDEREDITOR_API UClass* StaticClass<UEdBEGraphSchema_BehaviorTreeDecorator>()
	{
		return UEdBEGraphSchema_BehaviorTreeDecorator::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UEdBEGraphSchema_BehaviorTreeDecorator(Z_Construct_UClass_UEdBEGraphSchema_BehaviorTreeDecorator, &UEdBEGraphSchema_BehaviorTreeDecorator::StaticClass, TEXT("/Script/BlackboardExtenderEditor"), TEXT("UEdBEGraphSchema_BehaviorTreeDecorator"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UEdBEGraphSchema_BehaviorTreeDecorator);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
