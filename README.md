# TestUE5 — first-person prototype

A minimal Unreal Engine 5.5 C++ starter project.

## Controls
- **W / A / S / D** — move
- **Mouse** — look around
- **Space** — jump

## Test arena
The game mode creates a small test arena at runtime so the project can be tested without committing a binary `.umap` file. It spawns a concrete-tinted floor, charcoal perimeter walls, colored jump platforms, a player start, a warm directional sun, sky atmosphere, skylight, and subtle fog. These use Unreal's built-in Basic Shapes mesh/material with runtime tint and roughness parameters. The configured startup map is Unreal's built-in `/Engine/Maps/Entry`.

Arena generation lives in `Source/TestUE5/TestUE5GameMode.cpp`. See [Docs/TEST_ARENA.md](Docs/TEST_ARENA.md).

## First-person character
`AFirstPersonTestCharacter` provides first-person movement and camera control. The camera has separate left/right sleeve and hand placeholder meshes, with movement-driven procedural bob/sway. The full-body placeholder is hidden from its own camera to avoid obstructing the view.

The character is still assembled from Unreal Engine basic cube and sphere meshes. It is not a finished realistic or skinned character. The next step for proper animation is importing a licensed skeletal arms mesh and wiring an Animation Blueprint. See [Docs/FIRST_PERSON_ANIMATION.md](Docs/FIRST_PERSON_ANIMATION.md).

## Build status
- `.github/workflows/validate.yml` checks the source layout and uploads a source ZIP. It does **not** compile the game.
- `.github/workflows/package-windows.yml` is a packaging workflow for a real Windows Shipping build. It runs only on manual dispatch and requires a Windows self-hosted GitHub Actions runner with **Unreal Engine 5.5 already installed** and the runner label `ue5-5.5`.
- The runner may be a remote/cloud Windows machine, so Unreal Engine does not need to be installed on the developer's personal PC. However, this repository workflow does not provision that machine or install Unreal Engine automatically.
- If UE 5.5 is installed in a custom directory, configure the runner's `UE_ROOT` environment variable or repository variable for the workflow's runner environment.
- After the workflow completes successfully, the packaged game files (including the `.exe`) are uploaded as the `TestUE5-Windows-Shipping` artifact for 14 days.

**Important:** the workflow file has been committed, but a runner has not been provisioned or tested from this repository yet. Therefore, no successful executable build is confirmed.
