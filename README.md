# Better Construction Scripts for UE4

Unreal's default Construction Script has differing behavior during Play in Editor than Packaged builds. In Packaged Builds, all Construction Scripts are executed at run-time, which can create large frame 1 spikes while loading a level if there are a lot of placed actors with construction script setup.

This plugin adds two new construction script variants that can be used with Actors, and integrated easily into any other of actors as needed:
- **CachedConstructionScript** - This reproduces the Play in Editor behavior in the packaged build, only running in editor for Placed Actors. In order for this to function properly, and values that the construction script changes must be non-transient and saved into the level data. If an actor with a CachedConstructionScript is spawned in fresh during runtime, the CachedConstructionScript will be run.
- **EditorOnlyConstructionScript** - This will only ever run in editor, never during run time. This is the best option to ensure that you aren't accidentally adding extra processing to your packaged build for in-editor convenience features that are intended to be development only.

In addition, this also adds functionality for Construction Scripts on Components, as long as the component is attached to a BetterConstructionScript supporting Actor. These components have three construction script options:
- **ConstructionScript** - A construction script that will always run, regardless of if in PIE or in a Packaged build.
- **CachedConstructionScript** - Same as above.
- **EditorOnlyConstructionScript** - Same as above.

*Warning: Because of how these construction scripts are implemented, some care does need to be taken in how they are used. They can be powerful but lack the safeguarding of the default actor's Construction Scripts.*
