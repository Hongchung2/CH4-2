// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "CXPawn.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef CX_CXPawn_generated_h
#error "CXPawn.generated.h already included, missing '#pragma once' in CXPawn.h"
#endif
#define CX_CXPawn_generated_h

#define FID_Project_UnrealEngine_CX_Source_CX_CXPawn_h_29_RPC_WRAPPERS_NO_PURE_DECLS \
	virtual bool ServerRPCSpawnLandMine_Validate(); \
	virtual void ServerRPCSpawnLandMine_Implementation(); \
	virtual void CTSAttack_Implementation(); \
	virtual void MulticastHitEffect_Implementation(FVector const& TraceStart, FVector const& TraceEnd, bool bHitVehicle, FVector ImpactPoint, FVector ImpactNormal); \
	DECLARE_FUNCTION(execServerRPCSpawnLandMine); \
	DECLARE_FUNCTION(execCTSAttack); \
	DECLARE_FUNCTION(execMulticastHitEffect);


#define FID_Project_UnrealEngine_CX_Source_CX_CXPawn_h_29_CALLBACK_WRAPPERS
#define FID_Project_UnrealEngine_CX_Source_CX_CXPawn_h_29_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesACXPawn(); \
	friend struct Z_Construct_UClass_ACXPawn_Statics; \
public: \
	DECLARE_CLASS(ACXPawn, AWheeledVehiclePawn, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/CX"), NO_API) \
	DECLARE_SERIALIZER(ACXPawn) \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		bThrottleBroken=NETFIELD_REP_START, \
		NETFIELD_REP_END=bThrottleBroken	}; \
	NO_API virtual void ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const override;


#define FID_Project_UnrealEngine_CX_Source_CX_CXPawn_h_29_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	ACXPawn(ACXPawn&&); \
	ACXPawn(const ACXPawn&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ACXPawn); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ACXPawn); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(ACXPawn) \
	NO_API virtual ~ACXPawn();


#define FID_Project_UnrealEngine_CX_Source_CX_CXPawn_h_26_PROLOG
#define FID_Project_UnrealEngine_CX_Source_CX_CXPawn_h_29_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Project_UnrealEngine_CX_Source_CX_CXPawn_h_29_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Project_UnrealEngine_CX_Source_CX_CXPawn_h_29_CALLBACK_WRAPPERS \
	FID_Project_UnrealEngine_CX_Source_CX_CXPawn_h_29_INCLASS_NO_PURE_DECLS \
	FID_Project_UnrealEngine_CX_Source_CX_CXPawn_h_29_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> CX_API UClass* StaticClass<class ACXPawn>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Project_UnrealEngine_CX_Source_CX_CXPawn_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
