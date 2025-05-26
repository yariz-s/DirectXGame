#pragma once
#include "KamataEngine.h"
using namespace KamataEngine;
using namespace MathUtility;

KamataEngine::Matrix4x4 MakeAffineMatrix(KamataEngine::Vector3& scale, KamataEngine::Vector3& rotation, KamataEngine::Vector3& translation);
