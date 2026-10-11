# TestUE5 — first-person prototype

A minimal Unreal Engine 5.5 C++ starter project.

## Controls
- **W / A / S / D** — move
- **Mouse** — look around
- **Space** — jump

## Character
`AFirstPersonTestCharacter` provides first-person camera and movement. The placeholder body is assembled from Unreal Engine built-in cube and sphere meshes at runtime; it is not yet a rigged or animated character asset.

## Build status
The GitHub Actions workflow validates the source layout and uploads a source ZIP. Standard GitHub-hosted Windows runners do not include Unreal Engine, so this workflow cannot compile a playable `.exe` by itself. A real UE build requires an Unreal Engine installation available to the runner, typically a configured self-hosted Windows runner with UE 5.5 installed and licensed.

The project does not yet include a custom `.umap` level or final art assets. Open it in Unreal Editor, create/open a level, add a floor and lighting, then press Play to test the controller.
