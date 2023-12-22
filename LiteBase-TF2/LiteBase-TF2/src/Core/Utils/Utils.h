#pragma once
#include "Color/Color.h"
#include "Hook/Hook.h"
#include "Interface/Interface.h"
#include "Pattern/Pattern.h"
#include "UtlVector/UtlVector.h"
#include "Vector/Vector.h"

#include <algorithm>
#include <stdint.h>
#include <map>
#include <unordered_map>
#include <memory>
#include <string>
#include <fstream>

#undef min
#undef max

#define PI 3.14159265358979323846
#define M_RADPI 57.295779513082
#define DEG2RAD(x) ((float)(x) * (float)((float)(PI) / 180.0f))
#define RAD2DEG(x) ((float)(x) * (float)(180.0f / (float)(PI)))

//unscoped enum
#pragma warning (disable : 26812)

using matrix3x4_t = float[3][4];
using QAngle = Vec3;

class VMatrix
{
private:
	Vector m[4][4];

public:
	inline const matrix3x4_t &As3x4() const {
		return *((const matrix3x4_t *)this);
	}
};

namespace Utils
{
	inline std::wstring ConvertUtf8ToWide(const std::string_view &str)
	{
		int count = MultiByteToWideChar(CP_UTF8, 0, str.data(), str.length(), NULL, 0);
		std::wstring wstr(count, 0);
		MultiByteToWideChar(CP_UTF8, 0, str.data(), str.length(), &wstr[0], count);
		return wstr;
	}

	inline float CLR2FLT(unsigned char x) {
		return (static_cast<float>(x) / 255.0f);
	}

	inline Vec3 CLR2VEC(Color_t x) {
		return Vec3(CLR2FLT(x.r), CLR2FLT(x.g), CLR2FLT(x.b));
	}

	inline unsigned long CLR2UL(Color_t x) {
		return (static_cast<unsigned long>(((x.r & 0xFF) << 24) | ((x.g & 0xFF) << 16) | ((x.b & 0xFF) << 8) | (x.a & 0xFF)));
	}

	inline void *GetVFuncPtr(void *pBaseClass, unsigned int nIndex) {
		return reinterpret_cast<void *>((*static_cast<int **>(pBaseClass))[nIndex]);
	}

	//============math==================

#pragma warning (push)
#pragma warning (disable : 26451)
#pragma warning (disable : 4244)

	inline double __declspec (naked) __fastcall FastSqrt(double n) {
		_asm fld qword ptr[esp + 4]
			_asm fsqrt
		_asm ret 8
	}

	inline float NormalizeAngle(float ang) {
		return (!std::isfinite(ang) ? 0.0f : std::remainder(ang, 360.0f));
	}

	inline void SinCos(float radians, float *sine, float *cosine)
	{
		_asm
		{
			fld		DWORD PTR[radians]
			fsincos

			mov edx, DWORD PTR[cosine]
			mov eax, DWORD PTR[sine]

			fstp DWORD PTR[edx]
			fstp DWORD PTR[eax]
		}
	}

	inline void ClampAngles(Vec3 &v) {
		v.x = std::max(-89.0f, std::min(89.0f, NormalizeAngle(v.x)));
		v.y = NormalizeAngle(v.y);
		v.z = 0.0f;
	}

	inline void VectorAngles(const Vec3 &forward, Vec3 &angles)
	{
		float tmp, yaw, pitch;

		if (forward.y == 0 && forward.x == 0)
		{
			yaw = 0;

			if (forward.z > 0)
				pitch = 270;
			else
				pitch = 90;
		}

		else
		{
			yaw = RAD2DEG(atan2f(forward.y, forward.x));

			if (yaw < 0)
				yaw += 360;

			tmp = forward.Lenght2D();
			pitch = RAD2DEG(atan2f(-forward.z, tmp));

			if (pitch < 0)
				pitch += 360;
		}

		angles[0] = pitch;
		angles[1] = yaw;
		angles[2] = 0;
	}

	inline void AngleVectors(const Vec3 &angles, Vec3 *forward)
	{
		float sp, sy, cp, cy;

		SinCos(DEG2RAD(angles.x), &sp, &cp);
		SinCos(DEG2RAD(angles.y), &sy, &cy);

		if (forward)
		{
			forward->x = cp * cy;
			forward->y = cp * sy;
			forward->z = -sp;
		}
	}

	inline void AngleVectors(const Vec3 &angles, Vec3 *forward, Vec3 *right, Vec3 *up)
	{
		float sr, sp, sy, cr, cp, cy;
		SinCos(DEG2RAD(angles.x), &sp, &cp);
		SinCos(DEG2RAD(angles.y), &sy, &cy);
		SinCos(DEG2RAD(angles.z), &sr, &cr);

		if (forward)
		{
			forward->x = cp * cy;
			forward->y = cp * sy;
			forward->z = -sp;
		}

		if (right)
		{
			right->x = (-1 * sr * sp * cy + -1 * cr * -sy);
			right->y = (-1 * sr * sp * sy + -1 * cr * cy);
			right->z = -1 * sr * cp;
		}

		if (up)
		{
			up->x = (cr * sp * cy + -sr * -sy);
			up->y = (cr * sp * sy + -sr * cy);
			up->z = cr * cp;
		}
	}

	inline Vec3 CalcAngle(const Vec3 &source, const Vec3 &destination, bool clamp = true)
	{
		Vec3 angles = Vec3(0.0f, 0.0f, 0.0f);
		Vec3 delta = (source - destination);
		float fHyp = FastSqrt((delta.x * delta.x) + (delta.y * delta.y));

		angles.x = (atanf(delta.z / fHyp) * M_RADPI);
		angles.y = (atanf(delta.y / delta.x) * M_RADPI);
		angles.z = 0.0f;

		if (delta.x >= 0.0f)
			angles.y += 180.0f;

		if (clamp)
			ClampAngles(angles);

		return angles;
	}

	inline float CalcFov(const Vec3 &src, const Vec3 &dst)
	{
		Vec3 v_src = Vec3();
		AngleVectors(src, &v_src);

		Vec3 v_dst = Vec3();
		AngleVectors(dst, &v_dst);

		float result = RAD2DEG(acos(v_dst.Dot(v_src) / v_dst.LenghtSqr()));

		if (!isfinite(result) || isinf(result) || isnan(result))
			result = 0.0f;

		return result;
	}

	inline void VectorTransform(const Vec3 &input, const matrix3x4_t &matrix, Vec3 &output)
	{
		for (auto i = 0; i < 3; i++)
			output[i] = input.Dot((Vec3 &)matrix[i]) + matrix[i][3];
	}

#pragma warning (pop)
}