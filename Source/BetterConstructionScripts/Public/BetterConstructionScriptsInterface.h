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
	static void OnConstruction(TActor *Actor)
	{
		if (!Actor->GetWorld())
			return;

		const EWorldType::Type WorldType = Actor->GetWorld()->WorldType;

		const bool bConstructionAllowed = (WorldType != EWorldType::EditorPreview && WorldType != EWorldType::GamePreview);
		if (!bConstructionAllowed)
			return;

		const bool isEditorWorld = (WorldType == EWorldType::Editor);
		const bool isCached = Actor->bCachedConstructionHasRun;

		OnConstruction_ConstructComponents(Actor, EBetterComponentCSTiming::RunBeforeActor);

#if WITH_EDITOR
		if (isEditorWorld)
			Actor->Execute_EditorOnlyConstructionScript(Actor);
#endif // #if WITH_EDITOR

		if (isEditorWorld || !isCached)
			Actor->Execute_CachedConstructionScript(Actor);

		OnConstruction_ConstructComponents(Actor, EBetterComponentCSTiming::RunAfterActor);

		// By saving this value into a UPROPERTY, we can distinguish between placed 
		// and freshly spawned actors.
		Actor->bCachedConstructionHasRun = true;
	}

private:
	template <class TActor>
	static void OnConstruction_ConstructComponents(TActor *Actor, EBetterComponentCSTiming Timing)
	{
		const bool bAllowConstruction = Actor->ComponentConstructionScript == Timing;
		const bool bAllowEditorConstruction = Actor->ComponentEditorOnlyConstructionScript == Timing;
		const bool bAllowCachedConstruction = Actor->ComponentCachedConstructionScript == Timing;

		if (bAllowConstruction || bAllowEditorConstruction || bAllowCachedConstruction)
		{
			const bool bIsEditorWorld = (Actor->GetWorld()->WorldType == EWorldType::Editor);
			const bool bIsCached = Actor->bCachedConstructionHasRun;

			for (UActorComponent* Component : Actor->GetComponents())
			{
				if (Component->Implements<UBetterComponentConstructionScripts>())
				{
					if (bAllowConstruction)
						IBetterComponentConstructionScripts::Execute_ConstructionScript(Component);

#if WITH_EDITOR
					if (bAllowEditorConstruction && bIsEditorWorld)
						IBetterComponentConstructionScripts::Execute_EditorOnlyConstructionScript(Component);
#endif // #if WITH_EDITOR

					if (bAllowCachedConstruction && (bIsEditorWorld || !bIsCached))
						IBetterComponentConstructionScripts::Execute_CachedConstructionScript(Component);
				}
			}
		}
	}

};