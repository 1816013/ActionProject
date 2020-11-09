#pragma once
#include <cmath>
#include <cassert>

template<typename T>
struct Vector2D
{
	T x;
	T y;
	Vector2D() : x(0), y(0) {};
	Vector2D(T inx, T iny) : x(inx), y(iny){};
	Vector2D operator+(const Vector2D& val)const
	{
		return Vector2D(x + val.x, y + val.y);
	}

	Vector2D operator-(const Vector2D& val)const
	{
		return Vector2D(x - val.x, y - val.y);
	}

	Vector2D operator*(const float scale)const
	{
		return Vector2D(x * scale, y * scale);
	}

	Vector2D operator/(const float scale)const
	{
		return Vector2D(x / scale, y / scale);
	}

	void operator+=(const Vector2D& val)
	{
		x += val.x;
		y += val.y;
	}

	void operator-=(const Vector2D& val)
	{
		x -= val.x;
		y -= val.y;
	}

	void operator*=(const float& scale)
	{
		x *= scale;
		y *= scale;
	}

	bool operator==(const Vector2D& v)
	{
		//assert(!(isnan(v.x) && isnan(v.y)));
		return x == v.x && y == v.y;
	}

	bool operator!=(const Vector2D& v)
	{
		//assert(!(isnan(v.x) && isnan(v.y)));
		return !(x == v.x && y == v.y);
	}

	float Magnitude()const
	{
		return hypot(x, y);
	}

	/// <summary>
	///  �x�N�g���̒�����2���Ԃ�
	/// </summary>
	/// <returns> �x�N�g���̒�����2��</returns>
	float SQMagnitude()const
	{
		return x * x + y * y;
	}

	void Nomarize()
	{
		Vector2D vec(x, y);
		auto mag = vec.Magnitude();
		assert(mag != 0.0f);
		x /= mag;
		y /= mag;
	}

	const Vector2D Nomarized() const
	{
		Vector2D vec(x, y);		
		auto mag = vec.Magnitude();
		//assert(mag != 0.0f);
		return Vector2D(x / mag, y / mag);
	}

	bool IsNil()const
	{
		return isnan(x) || isnan(y);
	}

	static const Vector2D<float>ZERO;
	static const Vector2D<float>NIL;
	static const Vector2D<float>UP;
	static const Vector2D<float>DOWN;
	static const Vector2D<float>RIGHT;
	static const Vector2D<float>LEFT;
};


using Vector2 = Vector2D<int>;
using Vector2f = Vector2D<float>;
using Position2 = Vector2;
using Position2f = Vector2f;

float Dot(const Vector2f& va, const Vector2f& vb);

float Closs(const Vector2f& va, const Vector2f& vb);

float Clamp(float val, float minVal = 0.0f, float maxVal = 1);

struct Size
{
	int w, h;
	Size() : w(0), h(0) {};
	Size(int vw, int vh) :w(vw), h(vh) {};
};

struct Rect 
{
	Position2f pos;	// ���S���W
	Size size;		// �傫��
	Rect() : pos({ 0, 0 }), size({ 0, 0 }) {};
	Rect(const Position2f& vpos, const Size& vsize) : pos(vpos),size(vsize){};
	float Left()const
	{
		return pos.x - size.w / 2.0f;
	}
	float Right()const
	{
		return pos.x + size.w / 2.0f;
	}
	float Top()const
	{
		return pos.y - size.h / 2.0f;
	}
	float Bottom()const
	{
		return pos.y + size.h / 2;
	}
};

/// <summary>
/// �~
/// </summary>
struct Circle
{
	Position2f center;	// ���S
	float radius;		// ���a
	Circle() :center({ 0, 0 }), radius(0.0f) {}
	Circle(const Position2f& c, const float r) :center(c), radius(r) {}
};
/// <summary>
/// ����
/// </summary>
struct Segment
{
	Position2f start;
	Vector2f vec;

	Segment() :start({ 0, 0 }), vec({ 0, 0 }) {};
	Segment(Position2f s, Vector2f v) : start(s), vec(v) {};
	Segment(float x, float y, float vx, float vy) : start(x, y), vec(vx, vy) {};

	static const Segment ZERO;
	static const Segment NIL;
	bool IsNil();
	Position2f End();
};

/// <summary>
/// �J�v�Z��
/// </summary>
struct Capsule
{
	Segment seg;	// ����
	//Position2f start;	// �N�_
	//Vector2f vecEnd;	// �N�_����[�_�̃x�N�g��
	float radius;	// ���a

	Capsule() : seg({ {0, 0}, { 0, 0 } })/*,start({ 0, 0 }), vecEnd({ 0, 0 })*/, radius(0.0f) {};
	//Capsule(const Position2f& s, const Vector2f& v, const float r) : start(s), vecEnd(v), radius(r) {};
	Capsule(const Segment& s, const float r) :seg(s), radius(r) {};
};

/// <summary>
/// ��`�\����
/// </summary>
/// <attention>
///  ���� : v1��v2�͎��v���
///		  : v1��v2�͓����傫��
/// </attention>
struct FanShape
{
	Position2f center;	//���S���W
	Vector2f v1;		// ��`�̒[�_�܂ł̃x�N�g��1
	Vector2f v2;		// ��`�̒[�_�܂ł̃x�N�g��2
	Vector2f initV_;	// ��`�̒[�_�x�N�g���̏����l
	FanShape() :center(0, 0), v1(0, 0), v2(0, 0) {};
	FanShape(const Position2f& p, const Vector2f& inv1, const Vector2f& inv2);
	FanShape(const Position2f& p, const Vector2f& inv1, float angle);

	void SetFanShape(const Position2f& p, const Vector2f& inv1, const Vector2f& inv2);

	/// <summary>
	/// ��`��`�悷��
	/// </summary>
	/// <param name="amp">�o���Ƃ���̍��W</param>
	/// <param name="amp">�c�݂̌W��</param>
	/// <param name="graphH">�摜�n���h��</param>
	/// <param name="cOffset">�J�����I�t�Z�b�g</param>
	/// <param name="sOffset">���g�I�t�Z�b�g</param>
	void Draw(Position2f pos, float amp = 0.0f, int graphH = -1, const Vector2f cOffset = Vector2f::ZERO, const Vector2f sOffset = Vector2f::ZERO);

	/// <summary>
	/// ���a��Ԃ�
	/// </summary>
	/// <returns>���a</returns>
	float Radius()const;
	void AddAngle1(float angle);
	void AddAngle2(float angle);
	/// <summary>
	/// v1��v2�̊p�x��Ԃ�
	/// </summary>
	/// <returns>�p�x</returns>
	float GetAngle()const;
};
/// <summary>
/// v1��v2�̋����𑪂�
/// </summary>
/// <param name="v1">�[�_�܂ł̃x�N�g��1</param>
/// <param name="v2">�[�_�܂ł̃x�N�g��2</param>
float GetAngle2Vector(const Vector2f& v1, const Vector2f& v2);

struct Matrix {
	float m[3][3];
};

/// <summary>
/// �P�ʍs���Ԃ�
/// </summary>
Matrix IdentityMat();

/// <summary>
/// ���s�ړ��s���Ԃ�
/// </summary>
/// <param name="x">X�������s�ړ���</param>
/// <param name="y">Y�������s�ړ���</param>
Matrix TranslateMat(float x, float y);

/// <summary>
/// ��]�s���Ԃ�
/// </summary>
/// <param name="angle">��]�p�x</param>
Matrix RotateMat(float angle);

/// <summary>
/// �Q�̍s��̏�Z��Ԃ�
/// </summary>
/// <param name="lmat">���Ӓl(�s��)</param>
/// <param name="rmat">�E�Ӓl(�s��)</param>
Matrix MultipleMat(const Matrix& lmat, const Matrix& rmat);

///�x�N�g���ɑ΂��čs���Z��K�p���A���ʂ̃x�N�g����Ԃ�
///@param mat �s��
///@param vec �x�N�g��
Vector2f MultipleVec(const Matrix& mat, const Vector2f& vec);

Vector2f operator*(const Matrix& mat, const Vector2f& vec);

/// <summary>
/// ��`�\����
/// </summary>
/// <attention>
///  ���� : v1��v2�͎��v���
///		  : v1��v2�͓����傫��
/// </attention>
struct SlashShape
{
	Position2f center;	//���S���W
	Vector2f v1;		// �a���̒[�_�܂ł̃x�N�g��1
	Vector2f v2;		// �a���̒[�_�܂ł̃x�N�g��2
	Vector2f initV_;	// �a���̒[�_�x�N�g���̏����l
	SlashShape() :center(0, 0), v1(0, 0), v2(0, 0) {};
	SlashShape(const Position2f& p, const Vector2f& inv1, const Vector2f& inv2);
	SlashShape(const Position2f& p, const Vector2f& inv1, float angle);

	/// <summary>
	/// �a����`�悷��
	/// </summary>
	/// <param name="graphH">�摜�n���h��</param>
	/// <param name="amp">�c�݂̌W��</param>
	/// <param name="psH">�s�N�Z���V�F�[�_�n���h��</param>
	/// <param name="normalH">�m�[�}���f�[�^�n���h��</param>
	/// <param name="turnF">���]�t���O</param>
	/// <param name="cOffset">�J�����̃I�t�Z�b�g</param>
	/// <param name="sOffset">���g�̃I�t�Z�b�g</param>
	void Draw(int graphH, const float amp, const int psH, const int normalH,bool turnF, const Vector2f cOffset = Vector2f::ZERO, const Vector2f sOffset = Vector2f::ZERO);
	
	/// <summary>
	/// ���a��Ԃ�
	/// </summary>
	/// <returns>���a</returns>
	float Radius()const;
	/// <summary>
	/// V1�̊p�x�����Z
	/// �n�[
	/// </summary>
	/// <param name="angle">���Z�p�x</param>
	void AddAngle1(float angle);
	/// <summary>
	/// V2�̊p�x�����Z
	/// �I�[
	/// </summary>
	/// <param name="angle">���Z�p�x</param>
	void AddAngle2(float angle);
	void SetAngle1(float angle);
	void SetAngle2(float angle);
	/// <summary>
	/// v1��v2�̊p�x��Ԃ�
	/// </summary>
	/// <returns>�p�x</returns>
	float GetAngle()const;
};