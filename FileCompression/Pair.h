#pragma once

//有序对
//提供广义有序对
template<typename T1, typename T2>
class Pair {
public:
	T1 first;
	T2 second;
	Pair(T1& first, T2& second) :first(first), second(second) {}
	Pair() {}
};