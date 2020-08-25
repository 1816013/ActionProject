#pragma once
#include<type_traits>
/// <summary>
/// 割り切れるかどうかを返す
/// </summary>
/// <returns>true:割り切れる</returns>
template<typename T>
inline bool IsDivisible(const T& v, const T& div) {
	static_assert(std::is_integral<T>());
	return v % div == 0;
}
/// <summary>
/// 剰余インクリメント
/// </summary>
/// <typeparam name="T">整数型に限る</typeparam>
/// <param name="value">現在の値</param>
/// <param name="modulo">モジュロ値</param>
/// <returns>剰余加算を行った値</returns>
template<typename T>
inline T ModuloIncrement(const T& value, const T& modulo) {
	static_assert(std::is_integral<T>());
	return (value + 1) % modulo;
}

/// <summary>
/// 剰余デクリメント
/// -値にならないように大きさを足したのち剰余
/// </summary>
/// <typeparam name="T">整数型に限る</typeparam>
/// <param name="value">現在の値</param>
/// <param name="modulo">モジュロ値</param>
/// <returns>剰余減算を行った値</returns>
template<typename T>
inline T ModuloDecrement(const T& value, const T& modulo) {
	static_assert(std::is_integral<T>());
	return (value - 1 + modulo) % modulo;
}
/// <summary>
/// 符号を返す
/// </summary>
template<typename T>
inline T Sign(const T& A)
{
	return static_cast<T>((A > 0) - (A < 0));
}
