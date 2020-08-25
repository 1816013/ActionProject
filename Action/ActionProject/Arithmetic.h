#pragma once
#include<type_traits>
/// <summary>
/// ����؂�邩�ǂ�����Ԃ�
/// </summary>
/// <returns>true:����؂��</returns>
template<typename T>
inline bool IsDivisible(const T& v, const T& div) {
	static_assert(std::is_integral<T>());
	return v % div == 0;
}
/// <summary>
/// ��]�C���N�������g
/// </summary>
/// <typeparam name="T">�����^�Ɍ���</typeparam>
/// <param name="value">���݂̒l</param>
/// <param name="modulo">���W�����l</param>
/// <returns>��]���Z���s�����l</returns>
template<typename T>
inline T ModuloIncrement(const T& value, const T& modulo) {
	static_assert(std::is_integral<T>());
	return (value + 1) % modulo;
}

/// <summary>
/// ��]�f�N�������g
/// -�l�ɂȂ�Ȃ��悤�ɑ傫���𑫂����̂���]
/// </summary>
/// <typeparam name="T">�����^�Ɍ���</typeparam>
/// <param name="value">���݂̒l</param>
/// <param name="modulo">���W�����l</param>
/// <returns>��]���Z���s�����l</returns>
template<typename T>
inline T ModuloDecrement(const T& value, const T& modulo) {
	static_assert(std::is_integral<T>());
	return (value - 1 + modulo) % modulo;
}
/// <summary>
/// ������Ԃ�
/// </summary>
template<typename T>
inline T Sign(const T& A)
{
	return static_cast<T>((A > 0) - (A < 0));
}
