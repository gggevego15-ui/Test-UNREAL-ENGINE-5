using UnityEngine;
using UnityEngine.Rendering;

namespace TestUE5
{
    public static class TestArenaBuilder
    {
        public static void CreateArena()
        {
            CreateBlock("Concrete Floor", new Vector3(0f, -0.5f, 0f), new Vector3(60f, 1f, 60f),
                new Color(0.34f, 0.36f, 0.38f), 0.1f);

            Color wall = new Color(0.16f, 0.19f, 0.22f);
            CreateBlock("North Wall", new Vector3(0f, 3f, 30f), new Vector3(60f, 6f, 1f), wall, 0.12f);
            CreateBlock("South Wall", new Vector3(0f, 3f, -30f), new Vector3(60f, 6f, 1f), wall, 0.12f);
            CreateBlock("East Wall", new Vector3(30f, 3f, 0f), new Vector3(1f, 6f, 60f), wall, 0.12f);
            CreateBlock("West Wall", new Vector3(-30f, 3f, 0f), new Vector3(1f, 6f, 60f), wall, 0.12f);

            CreateBlock("Platform Blue", new Vector3(5.5f, 0.35f, 0f), new Vector3(2.5f, 0.7f, 3f),
                new Color(0.18f, 0.36f, 0.43f), 0.45f);
            CreateBlock("Platform Amber", new Vector3(9f, 1.05f, 0f), new Vector3(2f, 0.7f, 2.5f),
                new Color(0.56f, 0.35f, 0.16f), 0.42f);
            CreateBlock("Platform Green", new Vector3(12f, 1.75f, 3.5f), new Vector3(2f, 0.7f, 2f),
                new Color(0.24f, 0.40f, 0.30f), 0.38f);
            CreateBlock("Platform Violet", new Vector3(15f, 2.45f, -3.5f), new Vector3(2f, 0.7f, 2f),
                new Color(0.35f, 0.31f, 0.45f), 0.42f);

            CreatePlayer();
            CreateLighting();
        }

        private static void CreateBlock(string objectName, Vector3 position, Vector3 scale, Color color, float smoothness)
        {
            GameObject block = GameObject.CreatePrimitive(PrimitiveType.Cube);
            block.name = objectName;
            block.transform.position = position;
            block.transform.localScale = scale;

            Shader shader = Shader.Find("Universal Render Pipeline/Lit");
            if (shader == null)
                shader = Shader.Find("Standard");
            var material = new Material(shader);
            material.color = color;
            if (material.HasProperty("_Smoothness"))
                material.SetFloat("_Smoothness", smoothness);
            block.GetComponent<Renderer>().sharedMaterial = material;
        }

        private static void CreatePlayer()
        {
            var player = new GameObject("FirstPersonPlayer");
            player.transform.position = new Vector3(0f, 1f, 0f);
            var controller = player.AddComponent<CharacterController>();
            controller.height = 1.76f;
            controller.radius = 0.34f;
            controller.center = new Vector3(0f, 0f, 0f);
            player.AddComponent<FirstPersonController>();
        }

        private static void CreateLighting()
        {
            RenderSettings.ambientMode = AmbientMode.Trilight;
            RenderSettings.ambientSkyColor = new Color(0.38f, 0.48f, 0.62f);
            RenderSettings.ambientEquatorColor = new Color(0.28f, 0.30f, 0.32f);
            RenderSettings.ambientGroundColor = new Color(0.13f, 0.13f, 0.14f);
            RenderSettings.fog = true;
            RenderSettings.fogColor = new Color(0.58f, 0.70f, 0.82f);
            RenderSettings.fogMode = FogMode.Exponential;
            RenderSettings.fogDensity = 0.003f;

            var sunObject = new GameObject("Warm Directional Sun");
            sunObject.transform.rotation = Quaternion.Euler(35f, 25f, 0f);
            var sun = sunObject.AddComponent<Light>();
            sun.type = LightType.Directional;
            sun.color = new Color(1f, 0.91f, 0.78f);
            sun.intensity = 1.3f;
            sun.shadows = LightShadows.Soft;
            RenderSettings.sun = sun;

            var fillObject = new GameObject("Soft Fill Light");
            fillObject.transform.rotation = Quaternion.Euler(25f, -140f, 0f);
            var fill = fillObject.AddComponent<Light>();
            fill.type = LightType.Directional;
            fill.color = new Color(0.55f, 0.68f, 1f);
            fill.intensity = 0.25f;
            fill.shadows = LightShadows.None;
        }
    }
}
