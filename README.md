# TestUE5 — first-person prototype

**Active project:** Unity 6 LTS port in [UnityProject](UnityProject/). The original Unreal Engine 5.5 source remains in the repository as a backup/reference; it has not been deleted.

## Unity prototype

The Unity port recreates the original first-person test arena:
- WASD movement, mouse look, Space to jump, and Escape to release the mouse cursor.
- CharacterController collision and gravity.
- Procedural first-person sleeve/hand placeholders with movement bob and sway.
- Concrete floor, perimeter walls, four colored raised platforms, warm directional light, fill light, and subtle fog.
- A 1280×720 Windows player build.

### Open locally

1. Install Unity Hub and Unity **6000.0.58f1** (Unity 6 LTS).
2. In Unity Hub, click **Add / Open** and select this repository's `UnityProject` folder.
3. Open the project and let Unity import the scripts/packages.
4. From the Unity top menu choose **TestUE5 → Generate Test Arena Scene**.
5. Open `Assets/Scenes/Main.unity` and press Play.

Controls: **W/A/S/D** move, **mouse** looks, **Space** jumps, **Esc** releases the cursor, and click to lock it again.

## Build a Windows EXE with GitHub Actions

Workflow: [Build Unity Windows EXE](.github/workflows/unity-windows.yml).

1. In the repository open **Settings → Secrets and variables → Actions → New repository secret**.
2. Add a repository secret named **UNITY_LICENSE** containing your Unity license file contents. GameCI needs a valid Unity license to run the Editor in CI.
3. Open **Actions → Build Unity Windows EXE → Run workflow**. A push that changes `UnityProject/**` also triggers the workflow.
4. When the run succeeds, open the run and download artifact **TestUE5-Unity-Windows**. It contains `TestUE5.exe` and the supporting player data folder.

The workflow has been added, but it has **not yet been confirmed to build successfully**. No EXE is claimed to exist until a successful Actions run and artifact are verified.

## Original Unreal project

The original UE 5.5 files and its packaging workflow remain available for reference. They are not part of the Unity build.
