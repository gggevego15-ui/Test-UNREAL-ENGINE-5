using System;
using System.IO;
using UnityEditor;
using UnityEditor.Build.Reporting;
using UnityEditor.SceneManagement;
using UnityEngine;
using UnityEngine.SceneManagement;

namespace TestUE5.Editor
{
    public static class BuildProject
    {
        private const string ScenePath = "Assets/Scenes/Main.unity";

        [MenuItem("TestUE5/Generate Test Arena Scene")]
        public static void GenerateScene()
        {
            string projectRoot = Directory.GetParent(Application.dataPath).FullName;
            Directory.CreateDirectory(Path.Combine(projectRoot, "Assets", "Scenes"));
            EditorSceneManager.NewScene(NewSceneSetup.EmptyScene, NewSceneMode.Single);
            TestArenaBuilder.CreateArena();
            Scene scene = SceneManager.GetActiveScene();
            scene.name = "Main";
            if (!EditorSceneManager.SaveScene(scene, ScenePath))
                throw new Exception("Could not save " + ScenePath);
            EditorBuildSettings.scenes = new[] { new EditorBuildSettingsScene(ScenePath, true) };
            AssetDatabase.SaveAssets();
            Debug.Log("Generated test arena scene at " + ScenePath);
        }

        public static void PerformBuild()
        {
            GenerateScene();
            PlayerSettings.productName = "TestUE5 Unity";
            PlayerSettings.companyName = "sinrok";
            PlayerSettings.defaultScreenWidth = 1280;
            PlayerSettings.defaultScreenHeight = 720;
            PlayerSettings.fullScreenMode = FullScreenMode.FullScreenWindow;
            PlayerSettings.activeInputHandler = 0;
            string projectRoot = Directory.GetParent(Application.dataPath).FullName;
            string output = Path.Combine(projectRoot, "Build", "Windows", "TestUE5.exe");
            Directory.CreateDirectory(Path.GetDirectoryName(output));
            var options = new BuildPlayerOptions { scenes = new[] { ScenePath }, locationPathName = output, target = BuildTarget.StandaloneWindows64, options = BuildOptions.None };
            BuildReport report = BuildPipeline.BuildPlayer(options);
            if (report.summary.result != BuildResult.Succeeded)
                throw new Exception("Windows build failed: " + report.summary.result + " (" + report.summary.totalErrors + " errors)");
            Debug.Log("TestUE5 Windows build created: " + output);
        }
    }
}
