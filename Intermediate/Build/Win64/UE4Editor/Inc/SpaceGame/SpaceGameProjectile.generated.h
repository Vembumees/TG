// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UPrimitiveComponent;
class AActor;
struct FVector;
struct FHitResult;
#ifdef SPACEGAME_SpaceGameProjectile_generated_h
#error "SpaceGameProjectile.generated.h already included, missing '#pragma once' in SpaceGameProjectile.h"
#endif
#define SPACEGAME_SpaceGameProjectile_generated_h

#define SpaceGame_Source_SpaceGame_SpaceGameProjectile_h_15_SPARSE_DATA
#define SpaceGame_Source_SpaceGame_SpaceGameProjectile_h_15_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execOnHit) \
	{ \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_HitComp); \
		P_GET_OBJECT(AActor,Z_Param_OtherActor); \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComp); \
		P_GET_STRUCT(FVector,Z_Param_NormalImpulse); \
		P_GET_STRUCT_REF(FHitResult,Z_Param_Out_Hit); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->OnHit(Z_Param_HitComp,Z_Param_OtherActor,Z_Param_OtherComp,Z_Param_NormalImpulse,Z_Param_Out_Hit); \
		P_NATIVE_END; \
	}


#define SpaceGame_Source_SpaceGame_SpaceGameProjectile_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOnHit) \
	{ \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_HitComp); \
		P_GET_OBJECT(AActor,Z_Param_OtherActor); \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComp); \
		P_GET_STRUCT(FVector,Z_Param_NormalImpulse); \
		P_GET_STRUCT_REF(FHitResult,Z_Param_Out_Hit); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->OnHit(Z_Param_HitComp,Z_Param_OtherActor,Z_Param_OtherComp,Z_Param_NormalImpulse,Z_Param_Out_Hit); \
		P_NATIVE_END; \
	}


#define SpaceGame_Source_SpaceGame_SpaceGameProjectile_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesASpaceGameProjectile(); \
	friend struct Z_Construct_UClass_ASpaceGameProjectile_Statics; \
public: \
	DECLARE_CLASS(ASpaceGameProjectile, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SpaceGame"), NO_API) \
	DECLARE_SERIALIZER(ASpaceGameProjectile) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define SpaceGame_Source_SpaceGame_SpaceGameProjectile_h_15_INCLASS \
private: \
	static void StaticRegisterNativesASpaceGameProjectile(); \
	friend struct Z_Construct_UClass_ASpaceGameProjectile_Statics; \
public: \
	DECLARE_CLASS(ASpaceGameProjectile, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SpaceGame"), NO_API) \
	DECLARE_SERIALIZER(ASpaceGameProjectile) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define SpaceGame_Source_SpaceGame_SpaceGameProjectile_h_15_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ASpaceGameProjectile(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ASpaceGameProjectile) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASpaceGameProjectile); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASpaceGameProjectile); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ASpaceGameProjectile(ASpaceGameProjectile&&); \
	NO_API ASpaceGameProjectile(const ASpaceGameProjectile&); \
public:


#define SpaceGame_Source_SpaceGame_SpaceGameProjectile_h_15_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ASpaceGameProjectile(ASpaceGameProjectile&&); \
	NO_API ASpaceGameProjectile(const ASpaceGameProjectile&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASpaceGameProjectile); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASpaceGameProjectile); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ASpaceGameProjectile)


#define SpaceGame_Source_SpaceGame_SpaceGameProjectile_h_15_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__ProjectileMesh() { return STRUCT_OFFSET(ASpaceGameProjectile, ProjectileMesh); } \
	FORCEINLINE static uint32 __PPO__ProjectileMovement() { return STRUCT_OFFSET(ASpaceGameProjectile, ProjectileMovement); }


#define SpaceGame_Source_SpaceGame_SpaceGameProjectile_h_12_PROLOG
#define SpaceGame_Source_SpaceGame_SpaceGameProjectile_h_15_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SpaceGame_Source_SpaceGame_SpaceGameProjectile_h_15_PRIVATE_PROPERTY_OFFSET \
	SpaceGame_Source_SpaceGame_SpaceGameProjectile_h_15_SPARSE_DATA \
	SpaceGame_Source_SpaceGame_SpaceGameProjectile_h_15_RPC_WRAPPERS \
	SpaceGame_Source_SpaceGame_SpaceGameProjectile_h_15_INCLASS \
	SpaceGame_Source_SpaceGame_SpaceGameProjectile_h_15_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define SpaceGame_Source_SpaceGame_SpaceGameProjectile_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SpaceGame_Source_SpaceGame_SpaceGameProjectile_h_15_PRIVATE_PROPERTY_OFFSET \
	SpaceGame_Source_SpaceGame_SpaceGameProjectile_h_15_SPARSE_DATA \
	SpaceGame_Source_SpaceGame_SpaceGameProjectile_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	SpaceGame_Source_SpaceGame_SpaceGameProjectile_h_15_INCLASS_NO_PURE_DECLS \
	SpaceGame_Source_SpaceGame_SpaceGameProjectile_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SPACEGAME_API UClass* StaticClass<class ASpaceGameProjectile>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID SpaceGame_Source_SpaceGame_SpaceGameProjectile_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
