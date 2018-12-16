#pragma once
#include <ostream>

using namespace std;
// Template für zwei Vektoren
template<typename Left, typename Op, typename Right>
class Expression {
	const Left& m_left;
	const Right& m_right;
public:
	typedef typename Left::value_type value_type;

	Expression(const Left& l, const Right& r) : m_left{ l }, m_right{ r } {}

	size_t size() const { return m_left.size(); }

	value_type operator[](int i) const {
		return Op::apply<value_type>(m_left[i], m_right[i]);
	}
};

// Template für Skalar + Vektor
template<typename Op, typename Right>
class Expression<double, Op, Right> {
	const double& m_left;
	const Right& m_right;
public:
	typedef typename Right::value_type value_type;

	Expression(const double& l, const Right& r) : m_left{ l }, m_right{ r } {}

	size_t size() const { return m_right.size(); }

	value_type operator[](int i) const {
		return Op::apply<value_type>(m_left, m_right[i]);
	}
};

// Template für Vektor + Skalar
template<typename Left, typename Op>
class Expression<Left, Op, double> {
	const Left& m_left;
	const double& m_right;
public:
	typedef typename Left::value_type value_type;

	Expression(const Left& l, const double& r) : m_left{ l }, m_right{ r } {}

	size_t size() const { return m_left.size(); }

	value_type operator[](int i) const {
		return Op::apply<value_type>(m_left[i], m_right);
	}
};



// Template für Vergleichsoperator
template<typename Left, typename Right>
bool operator==(const Left& left, const Right& right) {
	if (left.size() != right.size()) return false;
	for (int i = 0; i < left.size(); i++) {
		if (left[i] != right[i]) {
			return false;
		}
	}
	return true;
}

// Operation für Addition
struct Addition {
	template<typename T> static T apply(T l, T r) {
		return l + r;
	}
};

// Operation für Subktration (Links minus Rechts)
struct Subtraktion {
	template<typename T> static T apply(T l, T r) {
		return l - r;
	}
};

// Operation für Multiplikation
struct Multiplikation {
	template<typename T> static T apply(T l, T r) {
		return l * r;
	}
};

// Operation für Division (Links durch Rechts)
struct Division {
	template<typename T> static T apply(T l, T r) {
		return l / r;
	}
};



// Template für Addition
template<typename Left, typename Right>
Expression<Left, Addition, Right> operator+(const Left& l, const Right& r) {
	return Expression<Left, Addition, Right>(l, r);
}

// Template für Subtraktion
template<typename Left, typename Right>
Expression<Left, Subtraktion, Right> operator-(const Left& l, const Right& r) {
	return Expression<Left, Subtraktion, Right>(l, r);
}

// Template für Multiplikation
template<typename Left, typename Right>
Expression<Left, Multiplikation, Right> operator*(const Left& l, const Right& r) {
	return Expression<Left, Multiplikation, Right>(l, r);
}

// Template für Division
template<typename Left, typename Right>
Expression<Left, Division, Right> operator/(const Left& l, const Right& r) {
	return Expression<Left, Division, Right>(l, r);
}

// Template für ostream Console output
template<typename Left, typename Op, typename Right>
ostream& operator<<(ostream &os, const Expression<Left, Op, Right> v) {
	os << "[";
	for (int i = 0; i < v.size(); i++) {
		os << v[i] << ",";
	}
	os << "]";
	return os;
}
