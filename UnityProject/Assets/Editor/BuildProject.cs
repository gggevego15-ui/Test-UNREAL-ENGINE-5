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

        public static void PerformBuild()
        {
            Directory.CreateDirectory("Assets/Scenes");
            EditorSceneManager.NewScene(NewSceneSetup.EmptyScene, NewSceneMode.Single);
            TestArenaBuilder.CreateArena();
            var scene = SceneManager.GetActiveScene();
            scene.name = "Main";
            EditorSceneManager.SaveScene(scene, ScenePath);
            EditorBuildSettings.scenes = new[]
            {
                new EditorBuildSettingsScene(ScenePath, true)
            };

            PlayerSettings.productName = "TestUE5 Unity";
            PlayerSettings.companyName = "sinrok";
            PlayerSettings.defaultScreenWidth = 1280;
            PlayerSettings.defaultScreenHeight = 720;
            PlayerSettings.fullScreenMode = FullScreenMode.FullScreenWindow;
            PlayerSettings.activeInputHandler = 0;

            string output = Path.GetFullPath("Build/Windows/TestUE5.exe");
            Directory.CreateDirectory(Path.GetDirectoryName(output));
            var options = new BuildPlayerOptions
            {
                scenes = new[] { ScenePath },
                locationPathName = output,
                target = BuildTarget.StandaloneWindows64,
                options = BuildOptions.None
            };

            BuildReport report = BuildPipeline.BuildPlayer(options);
            if (report.summary.result != BuildResult.Succeeded)
                throw new Exception("Windows build failed: " + report.summary.result + " (" + report.summary.totalErrors + " errors)");

            Debug.Log("TestUE5 Windows build created: " + output);
        }
    }
}
