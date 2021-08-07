// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BlackboardExtender/Public/BEBlackboardData.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBEBlackboardData() {}
// Cross Module References
	BLACKBOARDEXTENDER_API UClass* Z_Construct_UClass_UBEBlackboardData_NoRegister();
	BLACKBOARDEXTENDER_API UClass* Z_Construct_UClass_UBEBlackboardData();
	AIMODULE_API UClass* Z_Construct_UClass_UBlackboardData();
	UPackage* Z_Construct_UPackage__Script_BlackboardExtender();
// End Cross Module References
	void UBEBlackboardData::StaticRegisterNativesUBEBlackboardData()
	{
	}
	UClass* Z_Construct_UClass_UBEBlackboardData_NoRegister()
	{
		return UBEBlackboardData::StaticClass();
	}
	struct Z_Construct_UClass_UBEBlackboardData_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_EDITORONLY_DATA
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Categories_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Categories;
		static const UE4CodeGen_Private::FTextPropertyParams NewProp_Categories_Inner;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#endif // WITH_EDITORONLY_DATA
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UBEBlackboardData_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBlackboardData,
		(UObject* (*)())Z_Construct_UPackage__Script_BlackboardExtender,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBEBlackboardData_Statics::Class_MetaDataParams[] = {
		{ "AutoExpandCategories", "Blackboard" },
		{ "IncludePath", "BEBlackboardData.h" },
		{ "ModuleRelativePath", "Public/BEBlackboardData.h" },
	};
#endif
#if WITH_EDITORONLY_DATA
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBEBlackboardData_Statics::NewProp_Categories_MetaData[] = {
		{ "Category", "Blackboard" },
		{ "ModuleRelativePath", "Public/BEBlackboardData.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UBEBlackboardData_Statics::NewProp_Categories = { "Categories", nullptr, (EPropertyFlags)0x0010000800000001, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBEBlackboardData, Categories), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UBEBlackboardData_Statics::NewProp_Categories_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBEBlackboardData_Statics::NewProp_Categories_MetaData)) };
	const UE4CodeGen_Private::FTextPropertyParams Z_Construct_UClass_UBEBlackboardData_Statics::NewProp_Categories_Inner = { "Categories", nullptr, (EPropertyFlags)0x0000000800000000, UE4CodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UBEBlackboardData_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBEBlackboardData_Statics::NewProp_Categories,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBEBlackboardData_Statics::NewProp_Categories_Inner,
	};
#endif // WITH_EDITORONLY_DATA
	const FCppClassTypeInfoStatic Z_Construct_UClass_UBEBlackboardData_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBEBlackboardData>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UBEBlackboardData_Statics::ClassParams = {
		&UBEBlackboardData::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		IF_WITH_EDITORONLY_DATA(Z_Construct_UClass_UBEBlackboardData_Statics::PropPointers, nullptr),
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		IF_WITH_EDITORONLY_DATA(UE_ARRAY_COUNT(Z_Construct_UClass_UBEBlackboardData_Statics::PropPointers), 0),
		0,
		0x009000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UBEBlackboardData_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UBEBlackboardData_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UBEBlackboardData()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UBEBlackboardData_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UBEBlackboardData, 874513126);
	template<> BLACKBOARDEXTENDER_API UClass* StaticClass<UBEBlackboardData>()
	{
		return UBEBlackboardData::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UBEBlackboardData(Z_Construct_UClass_UBEBlackboardData, &UBEBlackboardData::StaticClass, TEXT("/Script/BlackboardExtender"), TEXT("UBEBlackboardData"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UBEBlackboardData);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
