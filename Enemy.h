#pragma once
#include "KamataEngine.h"
#include "MyMath.h"
class Player;

class Enemy {
public:
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& position);
	void Update();
	void Draw();
	KamataEngine::Vector3 GetWorldPosition();
	// AABBを取得
	AABB GetAABB();
	//衝突応答
	void OnCollision(const Player* player);

private:
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Camera* camera_ = nullptr;
	//歩行の速さ
	static inline const float kWalkSpeed = 0.1f;
	//速さ
	KamataEngine::Vector3 velocity_ = {};
	//経過時間
	float walkTimer_ = 0.0f;
};
