// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "ChatUI.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef CX_ChatUI_generated_h
#error "ChatUI.generated.h already included, missing '#pragma once' in ChatUI.h"
#endif
#define CX_ChatUI_generated_h

#define FID_Project_UnrealEngine_CH4_2_CX_Source_CX_ChatUI_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execOnChatInputTextCommitted);


#define FID_Project_UnrealEngine_CH4_2_CX_Source_CX_ChatUI_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUChatUI(); \
	friend struct Z_Construct_UClass_UChatUI_Statics; \
public: \
	DECLARE_CLASS(UChatUI, UUserWidget, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/CX"), NO_API) \
	DECLARE_SERIALIZER(UChatUI)


#define FID_Project_UnrealEngine_CH4_2_CX_Source_CX_ChatUI_h_14_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UChatUI(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UChatUI(UChatUI&&); \
	UChatUI(const UChatUI&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UChatUI); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UChatUI); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UChatUI) \
	NO_API virtual ~UChatUI();


#define FID_Project_UnrealEngine_CH4_2_CX_Source_CX_ChatUI_h_11_PROLOG
#define FID_Project_UnrealEngine_CH4_2_CX_Source_CX_ChatUI_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Project_UnrealEngine_CH4_2_CX_Source_CX_ChatUI_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Project_UnrealEngine_CH4_2_CX_Source_CX_ChatUI_h_14_INCLASS_NO_PURE_DECLS \
	FID_Project_UnrealEngine_CH4_2_CX_Source_CX_ChatUI_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> CX_API UClass* StaticClass<class UChatUI>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Project_UnrealEngine_CH4_2_CX_Source_CX_ChatUI_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
