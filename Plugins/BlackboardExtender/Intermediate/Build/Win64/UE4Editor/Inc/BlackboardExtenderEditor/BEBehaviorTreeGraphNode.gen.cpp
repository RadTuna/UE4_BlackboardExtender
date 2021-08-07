// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BlackboardExtenderEditor/Classes/BEBehaviorTreeGraphNode.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBEBehaviorTreeGraphNode() {}
// Cross Module References
	BLACKBOARDEXTENDEREDITOR_API UClass* Z_Construct_UClass_UBEBehaviorTreeGraphNode_NoRegister();
	BLACKBOARDEXTENDEREDITOR_API UClass* Z_Construct_UClass_UBEBehaviorTreeGraphNode();
	AIGRAPH_API UClass* Z_Construct_UClass_UAIGraphNode();
	UPackage* Z_Construct_UPackage__Script_BlackboardExtenderEditor();
// End Cross Module References
	void UBEBehaviorTreeGraphNode::StaticRegisterNativesUBEBehaviorTreeGraphNode()
	{
	}
	UClass* Z_Construct_UClass_UBEBehaviorTreeGraphNode_NoRegister()
	{
		return UBEBehaviorTreeGraphNode::StaticClass();
	}
	struct Z_Construct_UClass_UBEBehaviorTreeGraphNode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bInjectedNode_MetaData[];
#endif
		static void NewProp_bInjectedNode_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bInjectedNode;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Services_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Services;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Services_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Decorators_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Decorators;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Decorators_Inner;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UBEBehaviorTreeGraphNode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UAIGraphNode,
		(UObject* (*)())Z_Construct_UPackage__Script_BlackboardExtenderEditor,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBEBehaviorTreeGraphNode_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "BEBehaviorTreeGraphNode.h" },
		{ "ModuleRelativePath", "Classes/BEBehaviorTreeGraphNode.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBEBehaviorTreeGraphNode_Statics::NewProp_bInjectedNode_MetaData[] = {
		{ "Comment", "/** if set, this node was injected from subtree and shouldn't be edited */" },
		{ "ModuleRelativePath", "Classes/BEBehaviorTreeGraphNode.h" },
		{ "ToolTip", "if set, this node was injected from subtree and shouldn't be edited" },
	};
#endif
	void Z_Construct_UClass_UBEBehaviorTreeGraphNode_Statics::NewProp_bInjectedNode_SetBit(void* Obj)
	{
		((UBEBehaviorTreeGraphNode*)Obj)->bInjectedNode = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UBEBehaviorTreeGraphNode_Statics::NewProp_bInjectedNode = { "bInjectedNode", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Bool , RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(uint8), sizeof(UBEBehaviorTreeGraphNode), &Z_Construct_UClass_UBEBehaviorTreeGraphNode_Statics::NewProp_bInjectedNode_SetBit, METADATA_PARAMS(Z_Construct_UClass_UBEBehaviorTreeGraphNode_Statics::NewProp_bInjectedNode_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBEBehaviorTreeGraphNode_Statics::NewProp_bInjectedNode_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBEBehaviorTreeGraphNode_Statics::NewProp_Services_MetaData[] = {
		{ "Comment", "/** only some of behavior tree nodes support services */" },
		{ "ModuleRelativePath", "Classes/BEBehaviorTreeGraphNode.h" },
		{ "ToolTip", "only some of behavior tree nodes support services" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UBEBehaviorTreeGraphNode_Statics::NewProp_Services = { "Services", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBEBehaviorTreeGraphNode, Services), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UBEBehaviorTreeGraphNode_Statics::NewProp_Services_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBEBehaviorTreeGraphNode_Statics::NewProp_Services_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UBEBehaviorTreeGraphNode_Statics::NewProp_Services_Inner = { "Services", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UBEBehaviorTreeGraphNode_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBEBehaviorTreeGraphNode_Statics::NewProp_Decorators_MetaData[] = {
		{ "Comment", "/** only some of behavior tree nodes support decorators */" },
		{ "ModuleRelativePath", "Classes/BEBehaviorTreeGraphNode.h" },
		{ "ToolTip", "only some of behavior tree nodes support decorators" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UBEBehaviorTreeGraphNode_Statics::NewProp_Decorators = { "Decorators", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBEBehaviorTreeGraphNode, Decorators), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UBEBehaviorTreeGraphNode_Statics::NewProp_Decorators_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBEBehaviorTreeGraphNode_Statics::NewProp_Decorators_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UBEBehaviorTreeGraphNode_Statics::NewProp_Decorators_Inner = { "Decorators", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UBEBehaviorTreeGraphNode_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UBEBehaviorTreeGraphNode_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBEBehaviorTreeGraphNode_Statics::NewProp_bInjectedNode,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBEBehaviorTreeGraphNode_Statics::NewProp_Services,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBEBehaviorTreeGraphNode_Statics::NewProp_Services_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBEBehaviorTreeGraphNode_Statics::NewProp_Decorators,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBEBehaviorTreeGraphNode_Statics::NewProp_Decorators_Inner,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UBEBehaviorTreeGraphNode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBEBehaviorTreeGraphNode>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UBEBehaviorTreeGraphNode_Statics::ClassParams = {
		&UBEBehaviorTreeGraphNode::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UBEBehaviorTreeGraphNode_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UBEBehaviorTreeGraphNode_Statics::PropPointers),
		0,
		0x000000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UBEBehaviorTreeGraphNode_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UBEBehaviorTreeGraphNode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UBEBehaviorTreeGraphNode()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UBEBehaviorTreeGraphNode_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UBEBehaviorTreeGraphNode, 345634856);
	template<> BLACKBOARDEXTENDEREDITOR_API UClass* StaticClass<UBEBehaviorTreeGraphNode>()
	{
		return UBEBehaviorTreeGraphNode::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UBEBehaviorTreeGraphNode(Z_Construct_UClass_UBEBehaviorTreeGraphNode, &UBEBehaviorTreeGraphNode::StaticClass, TEXT("/Script/BlackboardExtenderEditor"), TEXT("UBEBehaviorTreeGraphNode"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UBEBehaviorTreeGraphNode);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
