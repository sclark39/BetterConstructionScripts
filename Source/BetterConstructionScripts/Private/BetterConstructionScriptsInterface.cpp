#include "BetterConstructionScriptsInterface.h"

template <class TActor>
void IBetterActorConstructionScripts::OnConstruction_ConstructComponents(TActor *Actor, EBetterComponentCSTiming Timing)
{
	const bool bAllowConstruction = Actor->ComponentConstructionScript == Timing;
	const bool bAllowEditorConstruction = Actor->ComponentEditorOnlyConstructionScript == Timing;
	const bool bAllowCachedConstruction = Actor->ComponentCachedConstructionScript == Timing;

	if (bAllowConstruction || bAllowEditorConstruction || bAllowCachedConstruction)
	{
		const bool bIsEditorWorld = (Actor->GetWorld()->WorldType == EWorldType::Editor);
		const bool bIsCached = Actor->bCachedConstructionHasRun;

		for (UActorComponent *Component : Actor->GetComponents())
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

template <class TActor> 
void IBetterActorConstructionScripts::OnConstruction(TActor *Actor)
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