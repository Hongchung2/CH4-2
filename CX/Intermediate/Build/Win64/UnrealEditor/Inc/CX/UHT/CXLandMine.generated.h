// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Gimmic/CXLandMine.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
class UPrimitiveComponent;
struct FHitResult;
#ifdef CX_CXLandMine_generated_h
#error "CXLandMine.generated.h already included, missing '#pragma once' in CXLandMine.h"
#endif
#define CX_CXLandMine_generated_h

#define FID_Project_UnrealEngine_CX_Source_CX_Gimmic_CXLandMine_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	virtual void MulticastPickupEffects_Implementation(); \
	DECLARE_FUNCTION(execMulticastPickupEffects); \
	DECLARE_FUNCTION(execOnOverlapSphereBeginOverlap);


#define FID_Project_UnrealEngine_CX_Source_CX_Gimmic_CXLandMine_h_12_CALLBACK_WRAPPERS
#define FID_Project_UnrealEngine_CX_Source_CX_Gimmic_CXLandMine_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesACXLandMine(); \
	friend struct Z_Construct_UClass_ACXLandMine_Statics; \
public: \
	DECLARE_CLASS(ACXLandMine, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/CX"), NO_API) \
	DECLARE_SERIALIZER(ACXLandMine)


#define FID_Project_UnrealEngine_CX_Source_CX_Gimmic_CXLandMine_h_12_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	ACXLandMine(ACXLandMine&&); \
	ACXLandMine(const ACXLandMine&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ACXLandMine); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ACXLandMine); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ACXLandMine) \
	NO_API virtual ~ACXLandMine();


#define FID_Project_UnrealEngine_CX_Source_CX_Gimmic_CXLandMine_h_9_PROLOG
#define FID_Project_UnrealEngine_CX_Source_CX_Gimmic_CXLandMine_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Project_UnrealEngine_CX_Source_CX_Gimmic_CXLandMine_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Project_UnrealEngine_CX_Source_CX_Gimmic_CXLandMine_h_12_CALLBACK_WRAPPERS \
	FID_Project_UnrealEngine_CX_Source_CX_Gimmic_CXLandMine_h_12_INCLASS_NO_PURE_DECLS \
	FID_Project_UnrealEngine_CX_Source_CX_Gimmic_CXLandMine_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> CX_API UClass* StaticClass<class ACXLandMine>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Project_UnrealEngine_CX_Source_CX_Gimmic_CXLandMine_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
