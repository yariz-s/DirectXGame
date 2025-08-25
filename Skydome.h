#pragma once
#include "KamataEngine.h"


class Skydome {

public:
	void Initialize(KamataEngine::Model* model, uint32_t textureHandle, KamataEngine::Camera* camera);

	void Update();

	void Draw();

private:
	// スプライト
	KamataEngine::Model* model_ = nullptr;

	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::Camera* camera_ = nullptr;

	uint32_t textureHandle_ = 0;
};