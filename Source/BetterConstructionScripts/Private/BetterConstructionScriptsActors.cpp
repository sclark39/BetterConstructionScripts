// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "BetterConstructionScriptsActors.h"

void ABetterActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	IBetterActorConstructionScripts::OnConstruction(this);
}

void ABetterStaticMeshActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	IBetterActorConstructionScripts::OnConstruction(this);
}

void ABetterSkeletalMeshActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	IBetterActorConstructionScripts::OnConstruction(this);
}
