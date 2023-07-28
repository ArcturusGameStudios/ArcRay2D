#include "arcpch.h"
#include <iostream>
#include "src/Scene/Map.h"
#include "src/Scene/Entity.h"
#include "src/Scene/Components.h"


int main()
{
	float timeScale = 1.0f;

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
	UUID medalAnimationID;
	std::shared_ptr<Model> cupModel = CreateRef<Model>(LoadModel("assets/models/teamugobj.obj"));
	std::shared_ptr<Texture2D> medalSprites = CreateRef<Texture2D>(LoadTexture("assets/textures/medalsCondensed.png"));
	AssetManagerInstance->AddModel(cupModelID, cupModel);
	AssetManagerInstance->AddTexture(medalSpriteID, medalSprites);

	std::shared_ptr<AnimationData> animData = CreateRef<AnimationData>();
	animData->SetFPS(8);
	animData->SetAnimLength(64);
//	animData->AddFrame(std::make_pair(Vector2{ 0, 0 }, 1));
//	animData->AddFrame(std::make_pair(Vector2{ 48, 0 }, 1));
//	animData->AddFrame(std::make_pair(Vector2{ 96, 0 }, 1));
//	animData->AddFrame(std::make_pair(Vector2{ 144, 0 }, 1));

	std::map<int, Vector2> _map;
	_map.emplace(0, Vector2{ 0, 0 });
	_map.emplace(1, Vector2{ 48, 0 });
	_map.emplace(2, Vector2{ 96, 0 });
	_map.emplace(3, Vector2{ 144, 0 });

	_map.emplace(4, Vector2{ 0, 48 });
	_map.emplace(5, Vector2{ 48, 48 });
	_map.emplace(6, Vector2{ 96, 48 });
	_map.emplace(7, Vector2{ 144, 48 });

	_map.emplace(8, Vector2{ 0, 96 });
	_map.emplace(9, Vector2{ 48, 96 });
	_map.emplace(10, Vector2{ 96, 96 });
	_map.emplace(11, Vector2{ 144, 96 });

	_map.emplace(12, Vector2{ 0, 144 });
	_map.emplace(13, Vector2{ 48, 144 });
	_map.emplace(14, Vector2{ 96, 144 });
	_map.emplace(15, Vector2{ 144, 144 });

	_map.emplace(12, Vector2{ 0, 192 });
	_map.emplace(13, Vector2{ 48, 192 });
	_map.emplace(14, Vector2{ 96, 192 });
	_map.emplace(15, Vector2{ 144, 192 });

	_map.emplace(16, Vector2{ 0, 240 });
	_map.emplace(17, Vector2{ 48, 240 });
	_map.emplace(18, Vector2{ 96, 240 });
	_map.emplace(19, Vector2{ 144, 240 });

	_map.emplace(20, Vector2{ 0, 288 });
	_map.emplace(21, Vector2{ 48, 288 });
	_map.emplace(22, Vector2{ 96, 288 });
	_map.emplace(23, Vector2{ 144, 288 });

	_map.emplace(24, Vector2{ 0, 336 });
	_map.emplace(25, Vector2{ 48, 336 });
	_map.emplace(26, Vector2{ 96, 336 });
	_map.emplace(27, Vector2{ 144, 336 });

	_map.emplace(28, Vector2{ 0, 384 });
	_map.emplace(29, Vector2{ 48, 384 });
	_map.emplace(30, Vector2{ 96, 384 });
	_map.emplace(31, Vector2{ 144, 384 });

	_map.emplace(32, Vector2{ 192, 0 });
	_map.emplace(33, Vector2{ 240, 0 });
	_map.emplace(34, Vector2{ 288, 0 });
	_map.emplace(35, Vector2{ 336, 0 });

	_map.emplace(36, Vector2{ 192, 48 });
	_map.emplace(37, Vector2{ 240, 48 });
	_map.emplace(38, Vector2{ 288, 48 });
	_map.emplace(39, Vector2{ 336, 48 });

	_map.emplace(40, Vector2{ 192, 96 });
	_map.emplace(41, Vector2{ 240, 96 });
	_map.emplace(42, Vector2{ 288, 96 });
	_map.emplace(43, Vector2{ 336, 96 });

	_map.emplace(44, Vector2{ 192, 144 });
	_map.emplace(45, Vector2{ 240, 144 });
	_map.emplace(46, Vector2{ 288, 144 });
	_map.emplace(47, Vector2{ 336, 144 });
	
	_map.emplace(48, Vector2{ 192, 192 });
	_map.emplace(49, Vector2{ 240, 192 });
	_map.emplace(50, Vector2{288, 192});
	_map.emplace(51, Vector2{ 336, 192 });

	_map.emplace(52, Vector2{ 192, 240 });
	_map.emplace(53, Vector2{ 240, 240 });
	_map.emplace(54, Vector2{ 288, 240 });
	_map.emplace(55, Vector2{ 336, 240 });

	_map.emplace(56, Vector2{ 192, 288 });
	_map.emplace(57, Vector2{ 240, 288 });
	_map.emplace(58, Vector2{ 288, 288 });
	_map.emplace(59, Vector2{ 336, 288 });

	_map.emplace(60, Vector2{ 192, 336 });
	_map.emplace(61, Vector2{ 240, 336 });
	_map.emplace(62, Vector2{ 288, 336 });
	_map.emplace(63, Vector2{ 336, 336 });

	animData->AddFrames(_map);
	AssetManagerInstance->AddAnimation(medalAnimationID, animData);

//	UUID testGenUUID;
//	Image testGeneratedImage = GenImagePerlinNoise(64, 64, 0, 0, 1.0f);
//	std::shared_ptr<Texture2D> testGeneratedTex = CreateRef<Texture2D>(LoadTextureFromImage(testGeneratedImage));
//	AssetManagerInstance->AddTexture(testGenUUID, testGeneratedTex);

	AssetManagerInstance->TestIDs();

#pragma region first map
	Map startMap = Map();
	startMap.m_IsDrawingEnabled = true;
	startMap.m_IsPhysicsEnabled = true;

	startMap.CreateCamera();

	// CREATE ENTITIES
	Entity circle = startMap.CreateEntity("test circle");
//	circle.GetComponent<TransformComponent>().SetTranslation(Vector2{ 5.0f, 100.0f }, -100.0f);
	circle.GetComponent<TransformComponent>().SetTranslation(Vector2{ 0.0f, 0.0f }, -100.0f);
	circle.AddComponent<ModelComponent>(cupModelID);
	circle.AddComponent<SpriteComponent>(medalSpriteID);
	circle.GetComponent<SpriteComponent>().SetSourceVec(Vector4{ 0, 0, 48, 48 });
	b2BodyDef* def = new b2BodyDef();
	def->position = circle.GetComponent<TransformComponent>().GetTranslation();
	def->type = b2BodyType::b2_dynamicBody;
//	def->angularVelocity = 20.0f;
	b2CircleShape* shape = new b2CircleShape();
	shape->m_radius = circle.GetComponent<TransformComponent>().GetScale().x;
	circle.AddComponent<Box2DBodyComponent>(def);
	circle.GetComponent<Box2DBodyComponent>().SetShape(shape, 1.0f);
	circle.AddComponent<AnimationComponent>();
	circle.GetComponent<AnimationComponent>().AddAnimation(medalAnimationID);
	circle.GetComponent<AnimationComponent>().SetAnimation(medalAnimationID);
	circle.GetComponent<AnimationComponent>().bIsPlaying = false;

#pragma endregion

//	startMap.GetWorld()->setIsGravityEnabled(false);
//	startMap.GetWorld()->setIsDebugRenderingEnabled(true);
	startMap.GetPhysicsWorld()->SetGravity(b2Vec2(0.0f, 9.81f));
	std::cout << "Gravity: (" << (startMap.GetPhysicsWorld()->GetGravity()).x << ", " << (startMap.GetPhysicsWorld()->GetGravity()).y << ")" << std::endl;;
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
				map->OnUpdateRuntime(ts, timeScale);
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