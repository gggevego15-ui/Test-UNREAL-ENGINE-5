# Runtime-generated test arena

The prototype builds its test environment in `ATestUE5GameMode::InitGame()` using meshes and material assets shipped with Unreal Engine.

## Included

- A 60 m × 60 m floor with a muted concrete-grey tint and high roughness.
- Charcoal perimeter walls.
- Four raised platforms with distinct, subdued blue, amber, green, and violet tints.
- A `PlayerStart` above the floor.
- Warm directional sunlight with shadows.
- Sky atmosphere, skylight, and subtle exponential height fog.

## Materials

The arena uses Unreal's built-in Basic Shapes cube mesh and Basic Shape material. Runtime material instances set the `Color` tint and `Roughness` scalar parameters; no external texture downloads or third-party assets are required. This keeps the repository lightweight while giving the greybox readable surface colors and a less glossy appearance.

If the installed engine version does not expose those parameters on its Basic Shape material, the shapes may fall back to the engine material's default appearance. A later polish pass can replace these with project-owned PBR materials and texture maps.

## Why runtime generation?

A real Unreal `.umap` is a binary editor asset and cannot be authored safely as a plain text file through the GitHub file API. Spawning the prototype geometry from C++ lets the test arena appear when the configured startup map is played, without pretending a text file is a real map asset.

## How to test

1. Open `TestUE5.uproject` in Unreal Engine 5.5.
2. Allow Unreal to compile the C++ project if prompted.
3. Open the configured startup map (`/Engine/Maps/Entry`) or any playable map using `TestUE5GameMode`.
4. Press Play. The game mode generates the arena during initialization.
5. Use WASD, mouse look, and Space to move around and test the raised platforms.

## Limitations

This is still a greybox arena, not photorealistic final art: it uses tinted built-in materials rather than custom scanned concrete, decals, normal maps, or surface wear. GitHub Actions validates source structure but does not compile the game because standard hosted runners do not include Unreal Engine.
