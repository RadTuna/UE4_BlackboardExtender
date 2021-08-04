// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BlackboardExtenderEditor/Public/BlackboardDataV2Factory.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBlackboardDataV2Factory() {}
// Cross Module References
	BLACKBOARDEXTENDEREDITOR_API UClass* Z_Construct_UClass_UBlackboardDataV2Factory_NoRegister();
	BLACKBOARDEXTENDEREDITOR_API UClass* Z_Construct_UClass_UBlackboardDataV2Factory();
	UNREALED_API UClass* Z_Construct_UClass_UFactory();
	UPackage* Z_Construct_UPackage__Script_BlackboardExtenderEditor();
// End Cross Module References
	void UBlackboardDataV2Factory::StaticRegisterNativesUBlackboardDataV2Factory()
	{
	}
	UClass* Z_Construct_UClass_UBlackboardDataV2Factory_NoRegister()
	{
		return UBlackboardDataV2Factory::StaticClass();
	}
	struct Z_Construct_UClass_UBlackboardDataV2Factory_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UBlackboardDataV2Factory_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UFactory,
		(UObject* (*)())Z_Construct_UPackage__Script_BlackboardExtenderEditor,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBlackboardDataV2Factory_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "BlackboardDataV2Factory.h" },
		{ "ModuleRelativePath", "Public/BlackboardDataV2Factory.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UBlackboardDataV2Factory_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBlackboardDataV2Factory>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UBlackboardDataV2Factory_Statics::ClassParams = {
		&UBlackboardDataV2Factory::StaticClass,
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
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UBlackboardDataV2Factory_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UBlackboardDataV2Factory_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UBlackboardDataV2Factory()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UBlackboardDataV2Factory_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UBlackboardDataV2Factory, 304181809);
	template<> BLACKBOARDEXTENDEREDITOR_API UClass* StaticClass<UBlackboardDataV2Factory>()
	{
		return UBlackboardDataV2Factory::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UBlackboardDataV2Factory(Z_Construct_UClass_UBlackboardDataV2Factory, &UBlackboardDataV2Factory::StaticClass, TEXT("/Script/BlackboardExtenderEditor"), TEXT("UBlackboardDataV2Factory"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UBlackboardDataV2Factory);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
