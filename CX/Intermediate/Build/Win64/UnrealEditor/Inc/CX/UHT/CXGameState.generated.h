// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "GameState/CXGameState.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class APlayerState;
enum class EGameState : uint8;
#ifdef CX_CXGameState_generated_h
#error "CXGameState.generated.h already included, missing '#pragma once' in CXGameState.h"
#endif
#define CX_CXGameState_generated_h

#define FID_Project_UnrealEngine_CX_Source_CX_GameState_CXGameState_h_21_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execIsWinner); \
	DECLARE_FUNCTION(execGetCurrentGameState); \
	DECLARE_FUNCTION(execGetRemainingTime);


#define FID_Project_UnrealEngine_CX_Source_CX_GameState_CXGameState_h_21_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesACXGameState(); \
	friend struct Z_Construct_UClass_ACXGameState_Statics; \
public: \
	DECLARE_CLASS(ACXGameState, AGameStateBase, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/CX"), NO_API) \
	DECLARE_SERIALIZER(ACXGameState) \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		CurrentGameState=NETFIELD_REP_START, \
		RemainingTime, \
		Winners, \
		NETFIELD_REP_END=Winners	}; \
	NO_API virtual void ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const override;


#define FID_Project_UnrealEngine_CX_Source_CX_GameState_CXGameState_h_21_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ACXGameState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	ACXGameState(ACXGameState&&); \
	ACXGameState(const ACXGameState&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ACXGameState); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ACXGameState); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ACXGameState) \
	NO_API virtual ~ACXGameState();


#define FID_Project_UnrealEngine_CX_Source_CX_GameState_CXGameState_h_18_PROLOG
#define FID_Project_UnrealEngine_CX_Source_CX_GameState_CXGameState_h_21_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Project_UnrealEngine_CX_Source_CX_GameState_CXGameState_h_21_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Project_UnrealEngine_CX_Source_CX_GameState_CXGameState_h_21_INCLASS_NO_PURE_DECLS \
	FID_Project_UnrealEngine_CX_Source_CX_GameState_CXGameState_h_21_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> CX_API UClass* StaticClass<class ACXGameState>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Project_UnrealEngine_CX_Source_CX_GameState_CXGameState_h


#define FOREACH_ENUM_EGAMESTATE(op) \
	op(EGameState::Waiting) \
	op(EGameState::Playing) \
	op(EGameState::Finished) 

enum class EGameState : uint8;
template<> struct TIsUEnumClass<EGameState> { enum { Value = true }; };
template<> CX_API UEnum* StaticEnum<EGameState>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
