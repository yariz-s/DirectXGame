#pragma once
#include "CameraController.h"
#include "KamataEngine.h"
#include "MapChipField.h"
#include "Player.h"
#include "Skydome.h"
#include <vector>
#include "Enemy.h"

class GameScene {
public:
	void Initialize();
	void Update();
	void Draw();
	bool isDebugCameraActive_ = false;
	KamataEngine::Model* modelSkydome_ = nullptr;
	MapChipField* mapChipField_ = nullptr;
	void GenerateBlocks();
	//全ての当たり判定
	void CheckMapCollision();

private:
	uint32_t textureHandle_ = 0;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Model* modelEnemy_ = nullptr;
	KamataEngine::Model* modelBlock_ = nullptr;
	KamataEngine::Camera camera_;
	Player* player_ = nullptr;
	
	std::list<Enemy*> enemies_;
	std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformBlocks_;
	KamataEngine::DebugCamera* debugCamera_ = nullptr;
	Skydome* skydome_ = nullptr;
	CameraController* cameraController_ = nullptr;
};