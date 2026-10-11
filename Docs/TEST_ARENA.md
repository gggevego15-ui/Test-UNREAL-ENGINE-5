# Runtime-generated test arena

The current prototype builds a simple test environment from engine-provided assets in `ATestUE5GameMode::InitGame()`.

## Included

- A broad floor with blocking collision.
- Four low boundary walls.
- Four raised platforms for testing movement and jumping.
- A `PlayerStart` above the floor.
- Directional sunlight configured as the atmosphere sun.
- Sky atmosphere and a skylight for ambient illumination.
- Light exponential height fog for depth.

## Why runtime generation?

A real Unreal `.umap` is a binary editor asset and cannot be authored safely as a plain text file through the GitHub file API. Spawning the prototype geometry from C++ lets the test arena appear when the configured startup map is played, without pretending a text file is a real map asset.

## How to test

1. Open `TestUE5.uproject` in Unreal Engine 5.5.
2. Allow Unreal to compile the C++ project if prompted.
3. Open the configured startup map (`/Engine/Maps/Entry`) or any playable map using `TestUE5GameMode`.
4. Press Play. The game mode generates the arena during initialization.
5. Use WASD, mouse look, and Space to move around and test the raised platforms.

## Limitations

This is a greybox test area, not a finished environment. The floor and platforms use the engine's default cube mesh and currently have no custom materials. GitHub Actions only validates files and packages source; a runner with Unreal Engine installed is required for a real game build.
