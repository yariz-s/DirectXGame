#pragma once
#include "KamataEngine.h"
#include "vector"
#include "MapChipField.h"

class MapChipField;
class Player {
public:
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& position);
	void Update();
	void Draw();

	const KamataEngine::WorldTransform& GetWorldTransform() const { return worldTransform_; }
	const KamataEngine::Vector3& GetVelocity() const { return velocity_; }
	void SetMapField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }

private:
	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;

	MapChipField* mapChipField_ = nullptr;
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Model* model_ = nullptr;
	/*uint32_t textureHandle_ = 0u;*/
	KamataEngine::Camera* camera_ = nullptr;

	KamataEngine::Vector3 velocity_{};
	static inline const float kAcceleration = 0.1f;
	static inline const float kAttenuation = 0.1f;
	static inline const float kLimitRunSpeed = 2.0f;

	enum class LRDirection {
		kRight,
		kLeft,
	};

	LRDirection lrDirection_ = LRDirection::kRight;

	float turnFirstRotationY_ = 0.0f;
	float turnTimer_ = 0.0f;

	static inline const float kTimeTurn = 0.5f;

	bool onGround_ = true;

	static inline const float kGravityAcceleration = 0.1f;
	static inline const float kLimitFallSpeed = 1.0f;
	static inline const float kJumpAcceleration = 1.0f;

	struct CollisionMapInfo {
		bool ceiling = false;
		bool landing = false;
		bool hitWall = false;
		KamataEngine::Vector3 move;
	};
    //1
	void InputMove();
	//2
	void CheckMapCollision(CollisionMapInfo& info);
	void CheckMapCollisionUp(CollisionMapInfo& info);
	void CheckMapCollisionDown(CollisionMapInfo& info);
	void CheckMapCollisionRight(CollisionMapInfo& info);
	void CheckMapCollisionLeft(CollisionMapInfo& info);
	//3
	void CheckMapMove(const CollisionMapInfo& info);
	
	
	void AnimateTurn();

	//4
	void CheckMapCeiling(const CollisionMapInfo& info);
	//5
	void CheckMapWall(const CollisionMapInfo& info);
	//6接触状態の切り替え
	void CheckMapLanding(const CollisionMapInfo& info);
	//角
	enum Corner {
		
		kRightBottom,
		kLeftBottom,
		kRightTop,
		kLeftTop,

		kNumCorner
	};
	

	KamataEngine::Vector3 CornerPosition(const KamataEngine::Vector3& center,Corner corner);

	static inline const float kBlank = 0.1f;
	static inline const float kAttenuationLanding = 0.1f;
	static inline const float kGroundSearchHeight = 0.1f;
	static inline const float kAttenuationWall = 0.1f;
};