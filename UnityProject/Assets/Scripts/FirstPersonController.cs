using UnityEngine;

namespace TestUE5
{
    [RequireComponent(typeof(CharacterController))]
    public sealed class FirstPersonController : MonoBehaviour
    {
        [Header("Movement")]
        [SerializeField] private float moveSpeed = 5f;
        [SerializeField] private float jumpHeight = 1.05f;
        [SerializeField] private float gravity = -18f;
        [SerializeField] private float mouseSensitivity = 2f;
        [SerializeField] private float lookLimit = 85f;

        private CharacterController characterController;
        private Camera playerCamera;
        private Transform armsRoot;
        private Vector3 velocity;
        private float pitch;
        private float bobClock;
        private Vector3 leftArmStart;
        private Vector3 rightArmStart;
        private bool cursorLocked = true;

        private void Awake()
        {
            characterController = GetComponent<CharacterController>();
            CreateCameraAndArms();
        }

        private void Start()
        {
            SetCursorLocked(true);
        }

        private void Update()
        {
            HandleCursor();
            HandleLook();
            HandleMovement();
            AnimateArms();
        }

        private void HandleCursor()
        {
            if (Input.GetKeyDown(KeyCode.Escape))
                SetCursorLocked(false);

            if (Input.GetMouseButtonDown(0) && !cursorLocked)
                SetCursorLocked(true);
        }

        private void SetCursorLocked(bool locked)
        {
            cursorLocked = locked;
            Cursor.lockState = locked ? CursorLockMode.Locked : CursorLockMode.None;
            Cursor.visible = !locked;
        }

        private void HandleLook()
        {
            if (!cursorLocked)
                return;

            float mouseX = Input.GetAxisRaw("Mouse X") * mouseSensitivity;
            float mouseY = Input.GetAxisRaw("Mouse Y") * mouseSensitivity;
            transform.Rotate(Vector3.up * mouseX);

            pitch = Mathf.Clamp(pitch - mouseY, -lookLimit, lookLimit);
            playerCamera.transform.localRotation = Quaternion.Euler(pitch, 0f, 0f);
        }

        private void HandleMovement()
        {
            float x = Input.GetAxisRaw("Horizontal");
            float z = Input.GetAxisRaw("Vertical");
            Vector3 input = Vector3.ClampMagnitude(transform.right * x + transform.forward * z, 1f);
            characterController.Move(input * moveSpeed * Time.deltaTime);

            if (characterController.isGrounded && velocity.y < 0f)
                velocity.y = -2f;

            if (Input.GetKeyDown(KeyCode.Space) && characterController.isGrounded)
                velocity.y = Mathf.Sqrt(jumpHeight * -2f * gravity);

            velocity.y += gravity * Time.deltaTime;
            characterController.Move(velocity * Time.deltaTime);
        }

        private void CreateCameraAndArms()
        {
            var cameraObject = new GameObject("FirstPersonCamera");
            cameraObject.transform.SetParent(transform, false);
            cameraObject.transform.localPosition = new Vector3(0f, 0.62f, 0f);
            playerCamera = cameraObject.AddComponent<Camera>();
            playerCamera.nearClipPlane = 0.03f;
            playerCamera.fieldOfView = 90f;
            cameraObject.AddComponent<AudioListener>();

            armsRoot = new GameObject("FirstPersonArms").transform;
            armsRoot.SetParent(playerCamera.transform, false);

            Material sleeveMaterial = CreateMaterial(new Color(0.13f, 0.19f, 0.26f), 0.55f);
            Material handMaterial = CreateMaterial(new Color(0.72f, 0.52f, 0.38f), 0.72f);
            leftArmStart = new Vector3(-0.24f, -0.27f, 0.48f);
            rightArmStart = new Vector3(0.24f, -0.27f, 0.48f);

            CreateArm("LeftSleeve", leftArmStart, new Vector3(0.13f, 0.12f, 0.34f), sleeveMaterial);
            CreateArm("RightSleeve", rightArmStart, new Vector3(0.13f, 0.12f, 0.34f), sleeveMaterial);
            CreateArm("LeftHand", leftArmStart + new Vector3(0f, 0.02f, 0.28f), new Vector3(0.085f, 0.075f, 0.09f), handMaterial, true);
            CreateArm("RightHand", rightArmStart + new Vector3(0f, 0.02f, 0.28f), new Vector3(0.085f, 0.075f, 0.09f), handMaterial, true);
        }

        private void CreateArm(string armName, Vector3 localPosition, Vector3 scale, Material material, bool sphere = false)
        {
            GameObject arm = GameObject.CreatePrimitive(sphere ? PrimitiveType.Sphere : PrimitiveType.Cube);
            arm.name = armName;
            arm.transform.SetParent(armsRoot, false);
            arm.transform.localPosition = localPosition;
            arm.transform.localScale = scale;
            var collider = arm.GetComponent<Collider>();
            if (collider != null)
                Destroy(collider);
            arm.GetComponent<Renderer>().sharedMaterial = material;
        }

        private void AnimateArms()
        {
            Vector3 horizontalVelocity = characterController.velocity;
            horizontalVelocity.y = 0f;
            float movement = Mathf.Clamp01(horizontalVelocity.magnitude / moveSpeed);
            bool grounded = characterController.isGrounded;

            if (movement > 0.05f && grounded)
                bobClock += Time.deltaTime * (8f + 4f * movement);

            float bob = movement > 0.05f && grounded ? Mathf.Sin(bobClock) * 0.012f : 0f;
            float sway = movement > 0.05f && grounded ? Mathf.Sin(bobClock * 0.5f) * 1.2f : 0f;

            if (armsRoot.childCount >= 2)
            {
                armsRoot.GetChild(0).localPosition = leftArmStart + new Vector3(0f, bob, 0f);
                armsRoot.GetChild(1).localPosition = rightArmStart + new Vector3(0f, -bob, 0f);
                armsRoot.GetChild(0).localRotation = Quaternion.Euler(0f, 0f, -8f + sway);
                armsRoot.GetChild(1).localRotation = Quaternion.Euler(0f, 0f, 8f - sway);
            }
            if (armsRoot.childCount >= 4)
            {
                armsRoot.GetChild(2).localPosition = leftArmStart + new Vector3(0f, 0.02f + bob, 0.28f);
                armsRoot.GetChild(3).localPosition = rightArmStart + new Vector3(0f, 0.02f - bob, 0.28f);
            }
        }

        private static Material CreateMaterial(Color color, float smoothness)
        {
            Shader shader = Shader.Find("Universal Render Pipeline/Lit");
            if (shader == null)
                shader = Shader.Find("Standard");
            var material = new Material(shader);
            material.color = color;
            if (material.HasProperty("_Smoothness"))
                material.SetFloat("_Smoothness", smoothness);
            return material;
        }
    }
}
