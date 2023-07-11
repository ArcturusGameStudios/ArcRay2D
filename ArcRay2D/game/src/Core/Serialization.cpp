#include "arcpch.h"
#include "Serialization.h"

EntityData MapSerializer::SerializeEntity(Entity* entity)
{
	EntityData entityData;

	if (entity->HasComponent<IDComponent>()) {
		std::cout << "ID: " << entity->GetComponent<IDComponent>().ID << std::endl;
		entityData.uuid = entity->GetComponent<IDComponent>().ID;
	}

	if (entity->HasComponent<TagComponent>()) {
	}

	if (entity->HasComponent<TransformComponent>()) {
		entityData.translation[0] = entity->GetComponent<TransformComponent>().GetTranslation().x;
		entityData.translation[1] = entity->GetComponent<TransformComponent>().GetTranslation().y;
		entityData.translation[2] = entity->GetComponent<TransformComponent>().GetDepth();
		entityData.rotation[0] = entity->GetComponent<TransformComponent>().GetRotationRad();
		entityData.scale[0] = entity->GetComponent<TransformComponent>().GetScale().x;
		entityData.scale[1] = entity->GetComponent<TransformComponent>().GetScale().y;
	}

	/*
	if (entity->HasComponent<RigidBodyComponent>()) {
	}

	if (entity->HasComponent<CollisionBodyComponent>()) {
	}
	*/

	if (entity->HasComponent<ModelComponent>()) {
		entityData.modelUuid = entity->GetComponent<ModelComponent>().refID;
	}

	if (entity->HasComponent<ProjectileComponent>()) {
	}
	return entityData;
}

Entity* MapSerializer::DeserializeEntity(EntityData data)
{
//	std::ifstream b(_filepath, std::ios::binary);
//	cereal::PortableBinaryInputArchive iar(b);

	uint64_t uuid = NULL;
//	std::string tag = {};
	float translation[3] = {};
	float rotation[3] = {};
	float scale[3] = {};
	float camFovy = NULL;
	int camType = {};
	uint64_t modelUuid = NULL;


//	iar(uuid, translation, rotation, scale, camFovy, camType, modelUuid);
	std::cout << (camType) << std::endl;

	Entity entity;
	return &entity;

	/*
	uint64_t _id;
//	iar(_id, _trans, _rot, _sca);
	iar(_id);
	std::cout << "INPUT ID: " << _id << std::endl;
	std::remove(_filepath);
	*/
}

void MapSerializer::SerializeMap(char* _filepath)
{
	/*
	std::list<EntityData> entityDatas = {};

	std::ofstream filepath(_filepath, (std::ios::binary));
	cereal::PortableBinaryOutputArchive oar(filepath);
	std::cout << _filepath << std::endl;


	for (Entity entity : *m_Map->GetEntityList())
	{
		entityDatas.push_back(SerializeEntity(&entity));
	}

	for (EntityData const entity : entityDatas)
	{
		std::cout << "UUID: " << entity.uuid << std::endl;
		std::cout << "Translation: (" << entity.translation[0] << ", " << entity.translation[1] << ", " << entity.translation[2] << ")" << std::endl;
		std::cout << "Rotation: (" << entity.rotation[0] << ", " << entity.rotation[1] << ", " << entity.rotation[2] << ")" << std::endl;
		std::cout << "Scale: (" << entity.scale[0] << ", " << entity.scale[1] << ", " << entity.scale[2] << ")" << std::endl;
		std::cout << "Camera FOV: " << entity.camFovy << std::endl;
		std::cout << "Camera Type: " << entity.camType << std::endl;
		std::cout << "Model UUID: " << entity.modelUuid << std::endl;
	}

	while (entityDatas.size() >= 1)
	{
		std::cout << "SIZE: " << entityDatas.size() << std::endl;
		
//		std::cout << "ID: " << (entityDatas.front().uuid) << std::endl;
//		std::cout << "Translation: " << (entityDatas.front().translation) << std::endl;
//		std::cout << "Rotation: " << (entityDatas.front().rotation) << std::endl;
//		std::cout << "Scale: " << (entityDatas.front().scale) << std::endl;
//		std::cout << "FOV: " << (entityDatas.front().camFovy) << std::endl;
//		std::cout << "Camera Type: " << (entityDatas.front().camType) << std::endl;
//		std::cout << "Model ID: " << (entityDatas.front().modelUuid) << std::endl;
		
		oar((
			entityDatas.front().uuid,
			entityDatas.front().translation,
			entityDatas.front().rotation,
			entityDatas.front().scale,
			entityDatas.front().camFovy,
			entityDatas.front().camType,
			entityDatas.front().modelUuid
			)
			, sizeof(EntityData));
		entityDatas.pop_front();
	}
	*/
}

void MapSerializer::DeserializeMap(char* _filepath)
{
}
