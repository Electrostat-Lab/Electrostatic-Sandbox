package com.serial4j.example.jme;

import com.jme3.app.SimpleApplication;
import com.jme3.asset.AssetManager;
import com.jme3.bullet.BulletAppState;
import com.jme3.bullet.PhysicsSpace;
import com.jme3.bullet.collision.shapes.BoxCollisionShape;
import com.jme3.bullet.collision.shapes.CompoundCollisionShape;
import com.jme3.bullet.collision.shapes.SphereCollisionShape;
import com.jme3.bullet.control.RigidBodyControl;
import com.jme3.bullet.control.VehicleControl;
import com.jme3.bullet.util.CollisionShapeFactory;
import com.jme3.font.BitmapText;
import com.jme3.input.ChaseCamera;
import com.jme3.input.KeyInput;
import com.jme3.input.controls.ActionListener;
import com.jme3.input.controls.KeyTrigger;
import com.jme3.light.AmbientLight;
import com.jme3.light.DirectionalLight;
import com.jme3.material.Material;
import com.jme3.material.RenderState;
import com.jme3.math.ColorRGBA;
import com.jme3.math.FastMath;
import com.jme3.math.Quaternion;
import com.jme3.math.Vector3f;
import com.jme3.renderer.queue.RenderQueue;
import com.jme3.scene.Geometry;
import com.jme3.scene.Node;
import com.jme3.scene.Spatial;
import com.jme3.scene.shape.Sphere;
import com.jme3.shadow.DirectionalLightShadowRenderer;
import com.jme3.system.AppSettings;
import com.jme3.util.SkyFactory;
import com.serial4j.core.hid.device.dataframe.DataFrameDevice;
import com.serial4j.core.hid.device.dataframe.registry.JoystickRegistry;
import com.serial4j.core.serial.SerialPort;
import com.serial4j.core.terminal.FilePermissions;
import com.serial4j.core.terminal.TerminalDevice;
import com.serial4j.core.terminal.control.BaudRate;

/**
 * Examines the standard device {@link DataFrameDevice} using a Joystick module through
 * encoding/decoding data via {@link JoystickRegistry}.
 *
 * @author pavl_g
 */
public class JoystickCarExample extends SimpleApplication implements DataFrameDevice.ReportDescriptor.DecoderListener<JoystickRegistry> {

    private static String[] args;
    private final Vector3f jumpForce = new Vector3f(0, 20000f, 0);
    private final float accelerationPower = 10000f;
    private float accelerationForce = 0f;
    private volatile boolean isTerminated = false;
    private Node vehicleNode;
    private BulletAppState bulletAppState;
    private VehicleControl vehicle;
    private DataFrameDevice<JoystickRegistry> dataFrameDevice;
    private BitmapText joystickValue;
    private String action;
    private ChaseCamera chaseCamera;

    public static void main(String[] args) {
        JoystickCarExample jmeGame = new JoystickCarExample();
        final AppSettings appSettings = new AppSettings(true);
        appSettings.setFullscreen(true);
        appSettings.setResolution(1366, 768);
        jmeGame.setSettings(appSettings);
        jmeGame.start();
        JoystickCarExample.args = args;
    }

    @Override
    public void simpleInitApp() {
        bulletAppState = new BulletAppState();
        stateManager.attach(bulletAppState);
        bulletAppState.setDebugEnabled(true);
        joystickValue = new BitmapText(guiFont);
        joystickValue.setColor(ColorRGBA.Black);
        guiNode.attachChild(joystickValue);
        joystickValue.setLocalTranslation(settings.getWidth() / 2f - joystickValue.getLocalScale().x,
                settings.getHeight() / 2f - joystickValue.getLocalScale().y, 0);

        addSky();
        createPhysicsTestWorld(rootNode, getAssetManager(), bulletAppState.getPhysicsSpace());
        buildPlayer();
        setupKeys();
    }

    private void setupKeys() {
        dataFrameDevice = new DataFrameDevice<>(new TerminalDevice(), new SerialPort(JoystickCarExample.args[0]));
        dataFrameDevice.setOperativePermissions((FilePermissions)
                FilePermissions.build().append(FilePermissions.OperativeConst.O_RDONLY));
        dataFrameDevice.init();
        dataFrameDevice.getTerminalDevice().setBaudRate(BaudRate.B57600);
        dataFrameDevice.setDecoderListener(this);

        new Thread(() -> {
            while (!isTerminated) {
                dataFrameDevice.receive();
            }
        }).start();
    }

    private void addSky() {
        Geometry sky = (Geometry) SkyFactory.createSky(assetManager, assetManager.loadTexture("RocketLeauge/assets/Textures/sky.jpg"), Vector3f.UNIT_XYZ, SkyFactory.EnvMapType.EquirectMap);
        /*uses low depth level*/
        sky.getMaterial().getAdditionalRenderState().setDepthFunc(RenderState.TestFunction.LessOrEqual);
        getRootNode().attachChild(sky);
    }

    private PhysicsSpace getPhysicsSpace() {
        return bulletAppState.getPhysicsSpace();
    }

    /**
     * creates a simple physics test world with a floor, an obstacle and some test boxes
     *
     * @param rootNode     where lights and geometries should be added
     * @param assetManager for loading assets
     * @param space        where collision objects should be added
     */
    private void createPhysicsTestWorld(Node rootNode, AssetManager assetManager, PhysicsSpace space) {

        Spatial floorGeometry = assetManager.loadModel("RocketLeauge/assets/Scenes/SoccerPlayGround.j3o");
        Material material = new Material(assetManager, "Common/MatDefs/Misc/Unshaded.j3md");
        material.setTexture("ColorMap", assetManager.loadTexture("RocketLeauge/assets/Textures/soccer.jpg"));
        floorGeometry.setMaterial(material);
        floorGeometry.addLight(new AmbientLight(ColorRGBA.White));

        DirectionalLight directionalLight = new DirectionalLight(new Vector3f(-0.5f, -0.5f, -0.5f).normalize());
        directionalLight.setColor(ColorRGBA.White.mult(2f));
        rootNode.addLight(directionalLight);

        floorGeometry.setLocalTranslation(0f, -10f, 0f);
        floorGeometry.setLocalScale(15f, floorGeometry.getLocalScale().getY() * 4, 20f);
        floorGeometry.addControl(new RigidBodyControl(CollisionShapeFactory.createMeshShape(floorGeometry), 0));
        rootNode.attachChild(floorGeometry);
        space.add(floorGeometry);

        //ball sphere with mesh collision shape
        Sphere sphere = new Sphere(15, 15, 5f);
        Geometry sphereGeometry = new Geometry("Sphere", sphere);
        sphereGeometry.setMaterial(Utils.createMat(assetManager, ColorRGBA.White, "RocketLeauge/assets/Textures/soccerTex.jpg"));
        sphereGeometry.setLocalTranslation(0f, -5f, 0f);
        sphereGeometry.setShadowMode(RenderQueue.ShadowMode.Cast);

        RigidBodyControl ballControl = new RigidBodyControl(new SphereCollisionShape(5f), 0.5f);
        ballControl.setFriction(2f);
        ballControl.setLinearVelocity(new Vector3f(0.2f, 0.2f, 0.2f));
        ballControl.setRollingFriction(1f);


        sphereGeometry.addControl(ballControl);
        rootNode.attachChild(sphereGeometry);
        space.add(sphereGeometry);

        DirectionalLightShadowRenderer dlsr = new DirectionalLightShadowRenderer(assetManager, 512, 1);
        dlsr.setLight(directionalLight);
        dlsr.setShadowIntensity(0.2f);
        dlsr.setLambda(0.55f);
        dlsr.setShadowZExtend(23f);
        dlsr.setShadowZFadeLength(8f);
        floorGeometry.setShadowMode(RenderQueue.ShadowMode.CastAndReceive);
        viewPort.addProcessor(dlsr);

    }

    private void buildPlayer() {
        cam.setFrustumFar(2000f);

        Spatial chassis = assetManager.loadModel("RocketLeauge/assets/Models/camaro.gltf");
        chassis.setLocalRotation(new Quaternion().fromAngleAxis(FastMath.PI, Vector3f.UNIT_Y));
        chassis.setShadowMode(RenderQueue.ShadowMode.Cast);
        chassis.setLocalScale(2.2f, 2.2f, 2.2f);
        chassis.setLocalTranslation(new Vector3f(0, 2f, 0));

        //create a compound shape and attach the BoxCollisionShape for the car body at 0,1,0
        //this shifts the effective center of mass of the BoxCollisionShape to 0,-1,0
        CompoundCollisionShape compoundShape = new CompoundCollisionShape();
        BoxCollisionShape box = new BoxCollisionShape(chassis.getLocalScale().add(2f, 0, 8f));

        compoundShape.addChildShape(box, new Vector3f(0, 4f, 0));

        //colors
        ((Node) chassis).getChild("glass").setMaterial(Utils.createMat(assetManager, ColorRGBA.Black, ""));
        ((Node) chassis).getChild("engine").setMaterial(Utils.createMat(assetManager, ColorRGBA.Black, ""));
        ((Node) chassis).getChild("radiator").setMaterial(Utils.createMat(assetManager, ColorRGBA.Black, ""));
        ((Node) chassis).getChild("chassis").setMaterial(Utils.createMat(assetManager, ColorRGBA.Cyan.mult(1.005f), ""));
        ((Node) chassis).getChild("nitro").setMaterial(Utils.createMat(assetManager, new ColorRGBA(0f, 0f, 5f, 1f), "RocketLeauge/assets/Textures/metalBareTex.jpg"));

        ((Node) chassis).getChild("front1").setMaterial(Utils.createMat(assetManager, ColorRGBA.Yellow, ""));
        ((Node) chassis).getChild("front2").setMaterial(Utils.createMat(assetManager, ColorRGBA.Yellow, ""));
        ((Node) chassis).getChild("front3").setMaterial(Utils.createMat(assetManager, ColorRGBA.Yellow, ""));
        ((Node) chassis).getChild("front4").setMaterial(Utils.createMat(assetManager, ColorRGBA.Yellow, ""));

        ((Node) chassis).getChild("back1").setMaterial(Utils.createMat(assetManager, ColorRGBA.Red, ""));
        ((Node) chassis).getChild("back2").setMaterial(Utils.createMat(assetManager, ColorRGBA.Red, ""));
        ((Node) chassis).getChild("back3").setMaterial(Utils.createMat(assetManager, ColorRGBA.Red, ""));
        ((Node) chassis).getChild("back4").setMaterial(Utils.createMat(assetManager, ColorRGBA.Red, ""));
        ((Node) chassis).getChild("mirrors").setMaterial(Utils.createMat(assetManager, ColorRGBA.White, ""));


        //create vehicle node
        vehicleNode = new Node("vehicleNode");
        vehicleNode.attachChild(chassis);
        vehicleNode.setShadowMode(RenderQueue.ShadowMode.Cast);
        vehicle = new VehicleControl(compoundShape, 600f);
        vehicleNode.addControl(vehicle);
        vehicle.setPhysicsLocation(new Vector3f(20f, 5f, 10f));

        // create a node for the camera
        Node cameraNode = new Node("camera");
        cameraNode.setLocalTranslation(0, 5f, -25f);
        vehicleNode.attachChild(cameraNode);

        chaseCamera = new ChaseCamera(cam, vehicleNode, inputManager);
        chaseCamera.setEnabled(true);
        chaseCamera.setDragToRotate(true);

        inputManager.addMapping("TriggerCamera", new KeyTrigger(KeyInput.KEY_C));
        inputManager.addListener((ActionListener) (name, isPressed, tpf) -> {
            if (name.equals("TriggerCamera") && isPressed) {
                chaseCamera.setEnabled(!chaseCamera.isEnabled());
            }
        }, "TriggerCamera");

        //setting suspension values for wheels, this can be a bit tricky
        //see also https://docs.google.com/Doc?docid=0AXVUZ5xw6XpKZGNuZG56a3FfMzU0Z2NyZnF4Zmo&hl=en
        float stiffness = 30.0f;//200=f1 car
        float compValue = 0.5f; //(should be lower than damp)
        float dampValue = 3f;
        //compression force of spring(Shock Producer)
        vehicle.setSuspensionCompression(compValue * 2.0f * FastMath.sqrt(stiffness));
        //stretch force of spring(Shock Absorber)
        vehicle.setSuspensionDamping(dampValue * 2.0f * FastMath.sqrt(stiffness));
        vehicle.setSuspensionStiffness(stiffness);
        vehicle.setMaxSuspensionForce(FastMath.pow(2, 20));
        vehicle.setMass(2000f);

        //Create four wheels and add them at their locations
        Vector3f wheelDirection = new Vector3f(0, -1F, 0); // was 0, -1, 0
        Vector3f wheelAxle = new Vector3f(-6, 0, 0); // was -1, 0, 0
        float radius = 0.95f;
        float restLength = 0.1f;
        float yOff = radius;
        float xOff = 3.5f * radius;
        float zOff = 6.5f * radius;

        Node wheel1 = Utils.createWheel(assetManager);
        wheel1.getChild("Mesh").rotate(0, FastMath.PI, 0);
        vehicle.addWheel(wheel1, new Vector3f(-xOff, yOff, zOff),
                wheelDirection, wheelAxle, restLength, radius, true);

        Node wheel2 = Utils.createWheel(assetManager);
        vehicle.addWheel(wheel2, new Vector3f(xOff, yOff, zOff),
                wheelDirection, wheelAxle, restLength, radius, true);

        final Node wheel3 = Utils.createWheel(assetManager);
        wheel3.getChild("Mesh").rotate(0, -FastMath.PI, 0);
        vehicle.addWheel(wheel3, new Vector3f(-xOff, yOff, -zOff),
                wheelDirection, wheelAxle, restLength, radius, false);

        final Node wheel4 = Utils.createWheel(assetManager);
        vehicle.addWheel(wheel4, new Vector3f(xOff, yOff, -zOff),
                wheelDirection, wheelAxle, restLength, radius, false);

        vehicleNode.attachChild(wheel1);
        vehicleNode.attachChild(wheel2);
        vehicleNode.attachChild(wheel3);
        vehicleNode.attachChild(wheel4);
        rootNode.attachChild(vehicleNode);

        Utils.setWheelFrictionSlip(vehicle, 20f);

        getPhysicsSpace().add(vehicle);
        DirectionalLight directionalLight = new DirectionalLight(new Vector3f(2, 2, 2).mult(50).normalize());
        directionalLight.setColor(ColorRGBA.White);
        vehicleNode.addLight(directionalLight);
    }

    @Override
    public void simpleUpdate(float tpf) {
        // update camera
        cam.setRotation(vehicleNode.getChild("camera").getWorldRotation());
        cam.setLocation(vehicleNode.getChild("camera").getWorldTranslation());
    }

    @Override
    public void onEncodingCompleted(String encoded) {

    }

    @Override
    public void onDecodingCompleted(JoystickRegistry decoded) {
        final int x = decoded.x();
        final int y = decoded.y();
        final int b = decoded.b();

        joystickValue.setText(decoded + "\n" + "Action = " + action + "\n");

        if (x > 1023f / 1.5f) {
            accelerationForce = accelerationPower * (x / 1023f);
            vehicle.accelerate(accelerationForce);
            action = "Accelerate";
        } else if (x < 1023f / 2.5f && x > 0) {
            accelerationForce = -accelerationPower * ((1023f - x) / 1023f);
            vehicle.accelerate(accelerationForce);
            action = "Decelerate";
        } else {
            accelerationForce -= (x);
            if (accelerationForce < 0f) {
                accelerationForce = 0f;
            }
            vehicle.accelerate(accelerationForce);
            action = "Inertia";
        }

        if (y > 1023f / 1.5f) {
            vehicle.steer(-y / 1023f);
            action = "Steer Right";
        } else if (y < 1023f / 2.5f && y > 0) {
            vehicle.steer((1023f - y) / 1023f);
            action = "Steer Left";
        } else {
            vehicle.steer(0);
        }

        if (b == 0) {
            vehicle.applyCentralForce(jumpForce);
        } else {
            vehicle.clearForces();
        }
    }

    @Override
    public void requestClose(boolean esc) {
        super.requestClose(esc);
        isTerminated = true;
        dataFrameDevice.close();
    }

    public static final class Utils {
        private Utils() {
        }

        public static Node createWheel(final AssetManager assetManager) {
            final Node node = new Node("Wheel");
            final Spatial mesh = assetManager.loadModel("RocketLeauge/assets/Models/camaro-tyre.gltf");
            mesh.setName("Mesh");
            mesh.setMaterial(createMat(assetManager, ColorRGBA.White, "RocketLeauge/assets/Textures/bronzeCopperTex.jpg"));
            node.attachChild(mesh);
            node.scale(1.15f);
            return node;
        }

        public static void setWheelFrictionSlip(final VehicleControl vehicle, float frictionSlip) {
            for (int nOfWheel = 0; nOfWheel < vehicle.getNumWheels(); nOfWheel++) {
                vehicle.getWheel(nOfWheel).setFrictionSlip(frictionSlip);
            }
        }

        public static Material createMat(final AssetManager assetManager, ColorRGBA colorRGBA, String texture) {
            Material material = new Material(assetManager, "Common/MatDefs/Light/PBRLighting.j3md");
            /*metalness , max is 1*/
            material.setFloat("Metallic", 0.5f);
            /*Roughness , 1 is the max roughnesss*/
            material.setFloat("Roughness", 0.5f);
            material.setFloat("EmissivePower", 1.0f);
            material.setFloat("EmissiveIntensity", 2.0f);
            material.setBoolean("HorizonFade", true);
            material.setVector3("LightDir", new Vector3f(-0.5f, -0.5f, -0.5f).normalize());
            material.setBoolean("BackfaceShadows", true);

            if (colorRGBA != null) {
                /*Diffuse Color*/
                material.setColor("BaseColor", colorRGBA);
                /*Reflection color*/
                material.setColor("Specular", colorRGBA.mult(20f));
            }
            if (texture.length() > 1) {
                material.setTexture("BaseColorMap", assetManager.loadTexture(texture));
            }
            material.setReceivesShadows(true);
            return material;
        }
    }
}