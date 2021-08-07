// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BlackboardExtenderEditor/Classes/BEBehaviorTreeDecoratorGraphNode_Logic.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBEBehaviorTreeDecoratorGraphNode_Logic() {}
// Cross Module References
	BLACKBOARDEXTENDEREDITOR_API UEnum* Z_Construct_UEnum_BlackboardExtenderEditor_EBEDecoratorLogicMode();
	UPackage* Z_Construct_UPackage__Script_BlackboardExtenderEditor();
	BLACKBOARDEXTENDEREDITOR_API UClass* Z_Construct_UClass_UBEBehaviorTreeDecoratorGraphNode_Logic_NoRegister();
	BLACKBOARDEXTENDEREDITOR_API UClass* Z_Construct_UClass_UBEBehaviorTreeDecoratorGraphNode_Logic();
	BLACKBOARDEXTENDEREDITOR_API UClass* Z_Construct_UClass_UBEBehaviorTreeDecoratorGraphNode();
// End Cross Module References
	static UEnum* EBEDecoratorLogicMode_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_BlackboardExtenderEditor_EBEDecoratorLogicMode, Z_Construct_UPackage__Script_BlackboardExtenderEditor(), TEXT("EBEDecoratorLogicMode"));
		}
		return Singleton;
	}
	template<> BLACKBOARDEXTENDEREDITOR_API UEnum* StaticEnum<EBEDecoratorLogicMode::Type>()
	{
		return EBEDecoratorLogicMode_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_EBEDecoratorLogicMode(EBEDecoratorLogicMode_StaticEnum, TEXT("/Script/BlackboardExtenderEditor"), TEXT("EBEDecoratorLogicMode"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_BlackboardExtenderEditor_EBEDecoratorLogicMode_Hash() { return 2063514477U; }
	UEnum* Z_Construct_UEnum_BlackboardExtenderEditor_EBEDecoratorLogicMode()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_BlackboardExtenderEditor();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("EBEDecoratorLogicMode"), 0, Get_Z_Construct_UEnum_BlackboardExtenderEditor_EBEDecoratorLogicMode_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "EBEDecoratorLogicMode::Sink", (int64)EBEDecoratorLogicMode::Sink },
				{ "EBEDecoratorLogicMode::And", (int64)EBEDecoratorLogicMode::And },
				{ "EBEDecoratorLogicMode::Or", (int64)EBEDecoratorLogicMode::Or },
				{ "EBEDecoratorLogicMode::Not", (int64)EBEDecoratorLogicMode::Not },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "And.Name", "EBEDecoratorLogicMode::And" },
				{ "ModuleRelativePath", "Classes/BEBehaviorTreeDecoratorGraphNode_Logic.h" },
				{ "Not.Name", "EBEDecoratorLogicMode::Not" },
				{ "Or.Name", "EBEDecoratorLogicMode::Or" },
				{ "Sink.Name", "EBEDecoratorLogicMode::Sink" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_BlackboardExtenderEditor,
				nullptr,
				"EBEDecoratorLogicMode",
				"EBEDecoratorLogicMode::Type",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::Namespaced,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	void UBEBehaviorTreeDecoratorGraphNode_Logic::StaticRegisterNativesUBEBehaviorTreeDecoratorGraphNode_Logic()
	{
	}
	UClass* Z_Construct_UClass_UBEBehaviorTreeDecoratorGraphNode_Logic_NoRegister()
	{
		return UBEBehaviorTreeDecoratorGraphNode_Logic::StaticClass();
	}
	struct Z_Construct_UClass_UBEBehaviorTreeDecoratorGraphNode_Logic_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_LogicMode_MetaData[];
#endif
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_LogicMode;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UBEBehaviorTreeDecoratorGraphNode_Logic_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBEBehaviorTreeDecoratorGraphNode,
		(UObject* (*)())Z_Construct_UPackage__Script_BlackboardExtenderEditor,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBEBehaviorTreeDecoratorGraphNode_Logic_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "BEBehaviorTreeDecoratorGraphNode_Logic.h" },
		{ "ModuleRelativePath", "Classes/BEBehaviorTreeDecoratorGraphNode_Logic.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBEBehaviorTreeDecoratorGraphNode_Logic_Statics::NewProp_LogicMode_MetaData[] = {
		{ "ModuleRelativePath", "Classes/BEBehaviorTreeDecoratorGraphNode_Logic.h" },
	};
#endif
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_UBEBehaviorTreeDecoratorGraphNode_Logic_Statics::NewProp_LogicMode = { "LogicMode", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBEBehaviorTreeDecoratorGraphNode_Logic, LogicMode), Z_Construct_UEnum_BlackboardExtenderEditor_EBEDecoratorLogicMode, METADATA_PARAMS(Z_Construct_UClass_UBEBehaviorTreeDecoratorGraphNode_Logic_Statics::NewProp_LogicMode_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBEBehaviorTreeDecoratorGraphNode_Logic_Statics::NewProp_LogicMode_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UBEBehaviorTreeDecoratorGraphNode_Logic_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBEBehaviorTreeDecoratorGraphNode_Logic_Statics::NewProp_LogicMode,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UBEBehaviorTreeDecoratorGraphNode_Logic_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBEBehaviorTreeDecoratorGraphNode_Logic>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UBEBehaviorTreeDecoratorGraphNode_Logic_Statics::ClassParams = {
		&UBEBehaviorTreeDecoratorGraphNode_Logic::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UBEBehaviorTreeDecoratorGraphNode_Logic_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UBEBehaviorTreeDecoratorGraphNode_Logic_Statics::PropPointers),
		0,
		0x000000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UBEBehaviorTreeDecoratorGraphNode_Logic_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UBEBehaviorTreeDecoratorGraphNode_Logic_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UBEBehaviorTreeDecoratorGraphNode_Logic()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UBEBehaviorTreeDecoratorGraphNode_Logic_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UBEBehaviorTreeDecoratorGraphNode_Logic, 497316882);
	template<> BLACKBOARDEXTENDEREDITOR_API UClass* StaticClass<UBEBehaviorTreeDecoratorGraphNode_Logic>()
	{
		return UBEBehaviorTreeDecoratorGraphNode_Logic::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UBEBehaviorTreeDecoratorGraphNode_Logic(Z_Construct_UClass_UBEBehaviorTreeDecoratorGraphNode_Logic, &UBEBehaviorTreeDecoratorGraphNode_Logic::StaticClass, TEXT("/Script/BlackboardExtenderEditor"), TEXT("UBEBehaviorTreeDecoratorGraphNode_Logic"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UBEBehaviorTreeDecoratorGraphNode_Logic);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
