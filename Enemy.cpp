#include "Enemy.h"
#include <numbers>
using namespace KamataEngine;
using namespace MathUtility;

void Enemy::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& position) {
	assert(model);
	model_ = model;
	camera_ = camera;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.rotation_.y = - std::numbers::pi_v<float> / 2.0f;
	//速度設定
	velocity_ = {kWalkSpeed, 0.0f, 0.0f};
	walkTimer_ = 0.0f;

}

void Enemy::Update() {
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();
	// 敵の移動
	worldTransform_.translation_ -= velocity_;
	//タイマー加算
	walkTimer_ += 1.0f/60.0f;
	//回転アニメーション
	worldTransform_.rotation_.x = std::sin(walkTimer_*5.0f);
}

void Enemy::Draw() {
	if (camera_ && model_) {
		model_->Draw(worldTransform_, *camera_);
	}
}
KamataEngine::Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

AABB Enemy::GetAABB() {
	Vector3 worldPos = GetWorldPosition();
	AABB aabb;
	aabb.min = {worldPos.x - 0.8f / 2.0f, worldPos.y - 0.8f / 2.0f, worldPos.z - 0.8f / 2.0f};
	aabb.max = {worldPos.x + 0.8f / 2.0f, worldPos.y + 0.8f / 2.0f, worldPos.z + 0.8f / 2.0f};
	return aabb;
}

void Enemy::OnCollision(const Player* player) { (void)player; }
