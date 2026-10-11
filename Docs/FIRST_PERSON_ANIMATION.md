# First-person character and animation plan

## Current prototype

`AFirstPersonTestCharacter` now owns four camera-attached placeholder meshes: left/right sleeves and left/right hands. The player's full-body placeholder is hidden from its owning camera so it does not obstruct first-person view. The arms are visible only to their owner.

`Tick()` contains a small movement-driven arm bob/sway. This is intentionally a temporary procedural animation layer so the camera and arm placement can be tested before adding an actual rig.

## Recommended next animation step

1. Replace the cube/sphere placeholders with a skinned first-person arms mesh (for example, a properly licensed mannequin arms asset).
2. Import a skeleton and create an Animation Blueprint or a small first-person animation instance.
3. Add Idle, Walk/Run, Jump/Fall/Land, and interaction/eating animations.
4. Use a separate first-person arms mesh from the full-body character mesh to prevent camera clipping.
5. Keep the current input bindings and character movement in `AFirstPersonTestCharacter`; move animation state to an AnimInstance once a skeletal mesh is present.

## Current controls

- WASD: move
- Mouse: look
- Space: jump

The procedural meshes are placeholders, not a finished realistic or skinned character. The GitHub Actions workflow validates source files and packages them; it does not compile Unreal Engine because standard hosted runners do not include UE.
