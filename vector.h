#pragma once
#include <stdlib.h>
#include <initializer_list>
#include <ostream>
#include <array>
#include "Expression.h"

using namespace std;

template<class T, int S>

class Vector : public array<T, S> {


public:

	Vector(const initializer_list<T>& data) {

		size_t s = __min(data.size(), S);

		auto it = data.begin();

		for (size_t i = 0; i < s; i++) {
			this->at(i) = *it++;
		}
	}


	Vector() {}

	template<typename AnyType>
	Vector<T, S> operator=(const AnyType e) {

		for (int i = 0; i < S; i++) this->at(i) = e[i];

		return *this;

	}


	friend std::ostream& operator<<(std::ostream &os, const Vector& v) {

		os << "[";
		for (int i = 0; i < S; i++) {
			os << v[i] << ",";
		}
		os << "]";
		return os;

	}


	template<typename AnyType>
	bool operator==(AnyType& arg) {
		for (int i = 0; i < arg.size(); i++) {
			if (this->at(i) != arg[i]) {
				return false;
			}
		}
		return true;
	}


	
	struct ScalarStruct
	{
	public:
		Vector m_v;
		ScalarStruct(const Vector& v) :m_v(v) {}

		Vector& operator*() const {
			return m_v;
		}
	};

	ScalarStruct operator*() const {
		return ScalarStruct((*this));
	}
	/**Berechnet das Skalarprodukt */
	friend T operator*(const Vector<T, S>& lhs, const ScalarStruct& rhs)
	{
		Vector& result = rhs.m_v * lhs;
		result.print();
		T value;
		for (size_t i = 0; i < result.size(); i++)
		{
			if (i == 0)
			{
				value = result[i];
			}
			else
			{
				value += result[i];
			}
		}
		return value;
	}

};
