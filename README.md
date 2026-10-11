# TestUE5 — first-person prototype

A minimal Unreal Engine 5.5 C++ starter project.

## Controls
- **W / A / S / D** — move
- **Mouse** — look around
- **Space** — jump

## First-person character
`AFirstPersonTestCharacter` provides first-person movement and camera control. The camera now has separate left/right sleeve and hand placeholder meshes, hidden from other viewers and animated with a lightweight movement-driven bob/sway. The full-body placeholder is hidden from its own camera to prevent obstructing the view.

The model is still built from Unreal Engine's basic cube and sphere meshes. It is a functional placeholder, not a realistic skinned character. The code now has a `Tick()` animation hook; the next step for proper animation is importing a licensed skeletal arms mesh and wiring an Animation Blueprint. See [`Docs/FIRST_PERSON_ANIMATION.md`](Docs/FIRST_PERSON_ANIMATION.md).

## Build status
The GitHub Actions workflow validates the source layout and uploads a source ZIP. Standard GitHub-hosted Windows runners do not include Unreal Engine, so this workflow cannot compile a playable `.exe` by itself. A real UE build requires an Unreal Engine installation available to the runner, typically a configured self-hosted Windows runner with UE 5.5 installed and licensed.

The project does not yet include a custom `.umap` level or final art assets. Open it in Unreal Editor, create/open a level, add a floor and lighting, then press Play to test the controller.
