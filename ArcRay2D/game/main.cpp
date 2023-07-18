#include "arcpch.h"
#include <iostream>
#include "src/Scene/Map.h"
#include "src/Scene/Entity.h"
#include "src/Scene/Components.h"

int main()
{
	//	if (SteamAPI_Init() == false)
	//	{
	//		std::cout << "STEAM FAILED TO INIT" << std::endl;
	//		return 0;
	//	}

	//	ISteamFriends* pSteamFriends = SteamFriends();
	//	const char* username = pSteamFriends->GetPersonaName();

		// set up the window
	InitWindow(1280, 800, "ArcRay2D");
	InitAudioDevice();
	SetTargetFPS(144);

//	rp3d::PhysicsCommon* physicsCommon = AssetManagerInstance->GetPhysicsCommon();

	std::list<Map*> maps = {};

	UUID cupModelID;
	UUID medalSpriteID;
	std::shared_ptr<Model> cupModel = CreateRef<Model>(LoadModel("assets/models/teamugobj.obj"));
	std::shared_ptr<Texture2D> medalSprites = CreateRef<Texture2D>(LoadTexture("assets/textures/medalsCondensed.png"));
	AssetManagerInstance->AddModel(cupModelID, cupModel);
	AssetManagerInstance->AddTexture(medalSpriteID, medalSprites);

	AssetManagerInstance->TestIDs();

#pragma region first map
	Map startMap = Map();
	startMap.m_IsDrawingEnabled = true;
	startMap.m_IsPhysicsEnabled = true;

	startMap.CreateCamera();

	// CREATE ENTITIES
	Entity circle = startMap.CreateEntity("test circle");
	circle.GetComponent<TransformComponent>().SetTranslation(Vector2{ 5.0f, 100.0f }, -100.0f);
	circle.AddComponent<ModelComponent>(cupModelID);
	circle.AddComponent<SpriteComponent>(medalSpriteID);
	circle.GetComponent<SpriteComponent>().SetSourceVec(Vector4{ 0, 0, 48, 48 });
	circle.GetComponent<SpriteComponent>().SetDestVec(Vector4{ 0, 0, 48, 48 });
	b2BodyDef* def = new b2BodyDef();
	def->position = circle.GetComponent<TransformComponent>().GetTranslation();
	def->type = b2BodyType::b2_dynamicBody;
//	def->angularVelocity = 20.0f;
	b2CircleShape* shape = new b2CircleShape();
	shape->m_radius = circle.GetComponent<TransformComponent>().GetScale().x;
	circle.AddComponent<Box2DBodyComponent>(def);
	circle.GetComponent<Box2DBodyComponent>().SetShape(shape, 0.0f);

#pragma endregion

//	startMap.GetWorld()->setIsGravityEnabled(false);
//	startMap.GetWorld()->setIsDebugRenderingEnabled(true);
	startMap.m_IsDebugRendering = true;
	maps.push_back(&startMap);

//	startMap.SerializeMap("assets/maps/mapTest.map");

	// game loop
	while (!WindowShouldClose())
	{
		Timestep ts;
//		std::cout << ts << std::endl;
//		std::cout << ts.GetFramerate() << std::endl;
		
//		Vector3 pTransform = playerCam.GetComponent<TransformComponent>().Translation;
//		pTransform.x -= ts;
//		playerCam.GetComponent<TransformComponent>().Translation = pTransform;
//		playerCam.GetComponent<TransformComponent>().LookAt(one.GetComponent<TransformComponent>().Translation);

		// drawing
		BeginDrawing();
		ClearBackground(DARKGRAY);
		if (ts != 0.0)
		{
			for (auto const &map : maps)
			{
				map->OnUpdateRuntime(ts);
			}
		}
		DrawFPS(0, 0);
		EndDrawing();
	}

	// cleanup
//	SteamAPI_Shutdown();
	CloseAudioDevice();
	CloseWindow();
	AssetManagerInstance->ReleaseMemory();
	return 0;
}