// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "GameFramework/Actor.h"
#include "Engine/StaticMeshActor.h"
#include "Animation/SkeletalMeshActor.h"

#include "BetterConstructionScriptsInterface.h"
#include "BetterConstructionScriptsActors.generated.h"

UCLASS()
class BETTERCONSTRUCTIONSCRIPTS_API ABetterActor : public AActor, public IBetterActorConstructionScripts
{
	GENERATED_BODY()
public:

	//~ Begin BetterConstructionScripts Interface
	UPROPERTY()
	bool bCachedConstructionHasRun = false;
	
	// When should Better Components' Construction Script occur?
	UPROPERTY(EditDefaultsOnly, Category = "Better Construction Scripts")
	EBetterComponentCSTiming ComponentConstructionScript = EBetterComponentCSTiming::Disabled;

	// When should Better Components' Editor Only Construction Script occur?
	UPROPERTY(EditDefaultsOnly, Category = "Better Construction Scripts")
	EBetterComponentCSTiming ComponentEditorOnlyConstructionScript = EBetterComponentCSTiming::Disabled;
	
	// When should Better Components' Cached Construction Script occur?
	UPROPERTY(EditDefaultsOnly, Category = "Better Construction Scripts")
	EBetterComponentCSTiming ComponentCachedConstructionScript = EBetterComponentCSTiming::Disabled;

	virtual void OnConstruction(const FTransform& Transform) override;
	//~ End BetterConstructionScripts Interface

};


UCLASS()
class BETTERCONSTRUCTIONSCRIPTS_API ABetterStaticMeshActor : public AStaticMeshActor, public IBetterActorConstructionScripts
{
	GENERATED_BODY()
public:

	//~ Begin BetterConstructionScripts Interface
	UPROPERTY()
		bool bCachedConstructionHasRun = false;

	// When should Better Components' Construction Script occur?
	UPROPERTY(EditDefaultsOnly, Category = "Better Construction Scripts")
		EBetterComponentCSTiming ComponentConstructionScript = EBetterComponentCSTiming::Disabled;

	// When should Better Components' Editor Only Construction Script occur?
	UPROPERTY(EditDefaultsOnly, Category = "Better Construction Scripts")
		EBetterComponentCSTiming ComponentEditorOnlyConstructionScript = EBetterComponentCSTiming::Disabled;

	// When should Better Components' Cached Construction Script occur?
	UPROPERTY(EditDefaultsOnly, Category = "Better Construction Scripts")
		EBetterComponentCSTiming ComponentCachedConstructionScript = EBetterComponentCSTiming::Disabled;

	virtual void OnConstruction(const FTransform& Transform) override;
	//~ End BetterConstructionScripts Interface

};

UCLASS()
class BETTERCONSTRUCTIONSCRIPTS_API ABetterSkeletalMeshActor : public ASkeletalMeshActor, public IBetterActorConstructionScripts
{
	GENERATED_BODY()
public:


	//~ Begin BetterConstructionScripts Interface
	UPROPERTY()
		bool bCachedConstructionHasRun = false;

	// When should Better Components' Construction Script occur?
	UPROPERTY(EditDefaultsOnly, Category = "Better Construction Scripts")
		EBetterComponentCSTiming ComponentConstructionScript = EBetterComponentCSTiming::Disabled;

	// When should Better Components' Editor Only Construction Script occur?
	UPROPERTY(EditDefaultsOnly, Category = "Better Construction Scripts")
		EBetterComponentCSTiming ComponentEditorOnlyConstructionScript = EBetterComponentCSTiming::Disabled;

	// When should Better Components' Cached Construction Script occur?
	UPROPERTY(EditDefaultsOnly, Category = "Better Construction Scripts")
		EBetterComponentCSTiming ComponentCachedConstructionScript = EBetterComponentCSTiming::Disabled;

	virtual void OnConstruction(const FTransform& Transform) override;
	//~ End BetterConstructionScripts Interface

};
