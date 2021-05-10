// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "BetterConstructionScriptsInterface.h"
#include "Components/ActorComponent.h"
#include "Components/SceneComponent.h"

#include "BetterConstructionScriptsComponents.generated.h"


UCLASS(Blueprintable)
class UBetterActorComponent : public UActorComponent, public IBetterComponentConstructionScripts
{
	GENERATED_BODY()
public:
};


UCLASS(Blueprintable)
class UBetterSceneComponent : public USceneComponent, public IBetterComponentConstructionScripts
{
	GENERATED_BODY()
public:
};