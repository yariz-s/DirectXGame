#pragma once
#include "KamataEngine.h"
#include "player.h"
#include "Skydome.h"
#include "vector"
    class GameScene {
public:
	~GameScene();
	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Draw();

private:
	// スプライト
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Model* modelskydome_ = nullptr;
	KamataEngine::Model* modelplayer_ = nullptr;
	KamataEngine::Camera camera_;
	Player* player_ = nullptr;
	Skydome* skydome_ = nullptr;
	bool isDebugCameraActive_ = false;
	KamataEngine::DebugCamera* debugCamera_ = nullptr;
	std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformBlocks_;

};