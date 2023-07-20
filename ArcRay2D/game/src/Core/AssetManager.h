#pragma once
#include <unordered_map>
#include "raylib.h"
#include "box2d/b2_world.h"


struct AnimationData {
	float framesPerSecond = 24;
	float totalAnimLength = 0.1f;
	std::map<int, Vector2> atlasKeyframes = {};

	// FPS, number of total frames, total time of animation
	// List of all individual textures used + how many frames they are repeated for to cut on redundancy

	AnimationData() = default;

	void SetFPS(int fps) { framesPerSecond = fps; };
	void SetAnimLength(int frames) { totalAnimLength = frames * (1 / framesPerSecond); };
	void AddFrames(std::map<int, Vector2> newKeyframes)
	{
		atlasKeyframes.merge(newKeyframes);
		std::cout << "Per frame: " << 1 / framesPerSecond << std::endl;
		std::cout << "Frame count: " << atlasKeyframes.size() << std::endl;
		std::cout << "Total length: " << totalAnimLength << std::endl;
		std::cout << std::endl;
	};

	Vector2 GetFrame(float &animTime)
	{
		// If there are no frames in animation, return {0, 0}
		if (atlasKeyframes.size() == 0)
			return Vector2{ 0, 0 };

		// Wraps animTime around the total animation length to get a nice loop
		while (animTime > totalAnimLength)
		{
			std::cout << "Old Input: " << animTime << std::endl;
			std::cout << "Anim Length: " << totalAnimLength << std::endl;
			animTime -= totalAnimLength;
			std::cout << "New Input: " << animTime << std::endl;
		}

		// Reverse iterate through the animations; if time is greater than current frame then return frame
		// If time is less than current frame then its not passed frame yet, continue iteration
		std::cout << "Anim time: " << animTime << std::endl;
		for (auto& iter = atlasKeyframes.rbegin(); iter != atlasKeyframes.rend(); ++iter)
		{
			std::cout << "Frame time: " << iter->first * (1 / framesPerSecond) << std::endl;
			if (iter->first * (1 / framesPerSecond) <= animTime)
				return iter->second;
		}
		// If all other frames fail, this is the first frame
		std::cout << "First frame" << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		return atlasKeyframes.begin()->second;
	};
};


class AssetManager
{
public:
	static AssetManager* Instance();
	void ReleaseMemory();

private:
	AssetManager() {};
	static AssetManager* m_Instance;

public:
	void TestIDs();
	b2World* GetPhysicsWorld() { return world; };

	std::shared_ptr<Model> GetModel(UUID id);
	bool AddModel(UUID id, std::shared_ptr<Model> model);

	std::shared_ptr<Texture2D> GetTexture(UUID id);
	bool AddTexture(UUID id, std::shared_ptr<Texture2D> texture);

	std::shared_ptr<AnimationData> GetAnimation(UUID id);
	bool AddAnimation(UUID id, std::shared_ptr<AnimationData> texture);

private:
	b2World* world = new b2World(b2Vec2(0.0f, 0.0f));
	std::unordered_map<UUID, std::shared_ptr<Model>> m_models;
	std::unordered_map<UUID, std::shared_ptr<Texture2D>> m_Textures;
	std::unordered_map<UUID, std::shared_ptr<AnimationData>> m_SpriteAnimations;
};

extern AssetManager* AssetManagerInstance; // declaration