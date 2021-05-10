// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"

#include "BetterConstructionScriptsInterface.generated.h"

UENUM()
enum class EBetterComponentCSTiming : uint8
{
	Disabled,
	RunBeforeActor,
	RunAfterActor
};

UINTERFACE(BlueprintType)
class BETTERCONSTRUCTIONSCRIPTS_API UBetterComponentConstructionScripts : public UInterface
{
	GENERATED_BODY()
};

class BETTERCONSTRUCTIONSCRIPTS_API IBetterComponentConstructionScripts
{
	GENERATED_BODY()
public:

	// This construction script will run in editor and in game for components of placed actors, and must be a child component
	// of a BetterConstructionScript Actor with Component Construction scripts enabled. 
	UFUNCTION(BlueprintImplementableEvent, CallInEditor)
	bool ConstructionScript();

	// This construction script will only run in game for freshly spawned actors, and will only run in editor for 
	// placed actors. This component must be a child component of a BetterConstructionScript Actor with Component 
	// Construction scripts enabled.
	UFUNCTION(BlueprintImplementableEvent, CallInEditor)
	bool CachedConstructionScript();

	// This construction script will only run in editor for components of placed actors, and must be a child component
	// of a BetterConstructionScript Actor with Component Construction scripts enabled. 
	UFUNCTION(BlueprintImplementableEvent, CallInEditor)
	bool EditorOnlyConstructionScript();
};

UINTERFACE()
class BETTERCONSTRUCTIONSCRIPTS_API UBetterActorConstructionScripts : public UInterface
{
	GENERATED_BODY()
};

class BETTERCONSTRUCTIONSCRIPTS_API IBetterActorConstructionScripts
{
	GENERATED_BODY()
public:

	// This construction script will only run in game for freshly spawned actors, and will only run in editor for 
	// placed actors. This version of the construction script brings the Play In Editor behavior of the default 
	// construction script into packaged builds.
	UFUNCTION(BlueprintImplementableEvent, CallInEditor)
	bool CachedConstructionScript();

	// This construction script will only ever run in editor, not in game.
	UFUNCTION(BlueprintImplementableEvent, CallInEditor)
	bool EditorOnlyConstructionScript();	

	template <class TActor>
	static void OnConstruction(TActor *Actor);

private:
	template <class TActor>
	static void OnConstruction_ConstructComponents(TActor *Actor, EBetterComponentCSTiming Timing);

};