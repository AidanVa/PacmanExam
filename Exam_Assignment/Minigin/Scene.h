#pragma once
#include "SceneManager.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#include "GameObject.h"
#include "Enums.h"
#pragma warning(pop)


enum class Direction;

namespace dae
{
	class SceneObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(const std::shared_ptr<SceneObject>& object);

		void DeleteObject(const std::shared_ptr<SceneObject>& object);

		void Update(float deltaTime);
		void Render() const;

		void LoadLevel(int levelIndex);
		void EndLevel(bool win);
		void StartLevel();
		void AddPlayer2(bool asGhost);

		//level tools
		glm::vec3 SnapPosition(glm::vec3 input,Direction direction);
		bool CheckCollision(glm::vec3 position, Direction direction);
		TileType CheckPickups(glm::vec3 position);

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		int GetTileAtPos(glm::vec3 position);
		void ClearLevel();
		void SpawnPlayer(int playerType);
		void SpawnGhost(int ghostNr, float x, float y);
		void SpawnAllGhosts();


		std::string mName{};
		std::vector < std::shared_ptr<SceneObject>> mObjects{};

		static unsigned int idCounter;

		bool m_IsGameRunning = false;
		float m_TransitionTimer = 0;

		std::vector<int> m_levelMap;
		std::vector < std::shared_ptr<GameObject>>  m_pickupsArr;
		std::vector < std::shared_ptr<GameObject>>  m_SpecialPickupsArr;
		std::vector < std::shared_ptr<GameObject>>  m_PowerupsArr;

		std::vector < std::shared_ptr<GameObject>>  m_Ghosts;



		int m_GridSize = 27;
		float m_TileSize = 18;


		int m_LevelIndex = 1;
		int m_LevelCount = 3;

		//debug
		std::shared_ptr<GameObject> m_DebugSprite;


	};

}
