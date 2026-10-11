# TestUE5 — first-person prototype

A minimal Unreal Engine 5.5 C++ starter project.

## Controls
- **W / A / S / D** — move
- **Mouse** — look around
- **Space** — jump

## Test arena
The game mode creates a small test arena at runtime so the project can be tested without committing a binary `.umap` file. It spawns a floor, perimeter walls, jump platforms, a player start, a directional sun, sky atmosphere, skylight, and light fog. The configured startup map is Unreal's built-in `/Engine/Maps/Entry`.

Arena generation lives in `Source/TestUE5/TestUE5GameMode.cpp`. See [Docs/TEST_ARENA.md](Docs/TEST_ARENA.md).

## First-person character
`AFirstPersonTestCharacter` provides first-person movement and camera control. The camera has separate left/right sleeve and hand placeholder meshes, with movement-driven procedural bob/sway. The full-body placeholder is hidden from its own camera to avoid obstructing the view.

The character is still assembled from Unreal Engine basic cube and sphere meshes. It is not a finished realistic or skinned character. The next step for proper animation is importing a licensed skeletal arms mesh and wiring an Animation Blueprint. See [Docs/FIRST_PERSON_ANIMATION.md](Docs/FIRST_PERSON_ANIMATION.md).

## Build status
The GitHub Actions workflow validates the source layout and uploads a source ZIP. Standard GitHub-hosted Windows runners do not include Unreal Engine, so this workflow cannot compile a playable `.exe` by itself. A real UE build requires an Unreal Engine installation available to the runner, typically a configured self-hosted Windows runner with UE 5.5 installed and licensed.
