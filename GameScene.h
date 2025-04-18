#pragma once
#include "KamataEngine.h"
class GameScene {
    uint32_t textureHandle_ = 0;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Camera camera_;

	public:
	//初期化
	void Initialize();
	//更新
	void Update();
	//描画
	void Draw();
};
