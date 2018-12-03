#pragma once

#include <memory>
#include <iostream>


using namespace std;

template<class T, size_t S> class Vector {

	unique_ptr<T[]> m_array;

	size_t m_capacity = S; //die Länge des Arrays m_array
	

public:

	Vector(): m_array(new T[S]) {};

	//Konstruktor mit Vektor als Parameter
	Vector(const Vector& v)
		: m_array(new T[v.m_capacity]), m_capacity(v.m_capacity){
		for (size_t i = 0; i < m_capacity; i++) {
			m_array[i] = v[i];
		}
	}

	//TODO
	Vector(Vector&& v) : m_array(move(v.m_array)) {
	}

	//Konstruktor mit Dimensionsgrösse und jeder Dimensionswert denselben Wert
	Vector(const T& val)
		: m_array(new T[S]){
		for (size_t i = 0; i < m_capacity; i++) m_array[i] = val;
	}



	//Konstruktur mit Iniitialisierungsliste (Dimensionswerte)
	Vector(const initializer_list<T>& data): m_array(new T[S]){
		//if (data.size() > S) { throw "Die Liste ist länger als die Länge des Vektors"; }
		size_t s = __min(data.size(), S);
				
		auto it = data.begin();
		for (size_t i = 0; i < s; i++) {
			this->m_array[i] = *it++;
		}
	}
	
	//Addition Operator
	Vector operator+(const Vector& b) {
		
		Vector<T, S> sum;
		
		for (size_t i = 0; i < this->m_capacity; i++) {
			sum.m_array[i] = this->m_array[i] + b.m_array[i];
			}
		return sum;
	}


	//Subtraktion Operator
	Vector operator-(const Vector& b) {
		Vector<T, S> subtraktion;
		
		for (size_t i = 0; i < this->m_capacity; i++) {
			subtraktion.m_array[i] = this->m_array[i] - b.m_array[i];
			}
		return subtraktion;
	}

	//Multiplikation Operator
	Vector operator* (const Vector& b) {
		Vector<T, S> produkt;

		for (size_t i = 0; i < this->m_capacity; i++) {
			produkt.m_array[i] = this->m_array[i] * b.m_array[i];
		}
		return produkt;
	}

	//Divison Operator
	Vector operator/(const Vector& b) {
		Vector<T,S> division;

		for (size_t i = 0; i < this->m_capacity; i++) {
			if(b.m_array[i] != 0){
				division.m_array[i] = this->m_array[i] / b.m_array[i];
			}
			else{
				throw "Division nicht möglich, da man nicht durch 0 teilen kann";
			}
		}
		return division;
	}

	//Index Operator (nur Lesezugriff)
	T& operator[] (size_t i) const {
		if (i >= m_capacity) throw out_of_range("index is too large");
		return m_array[i];
	}

	// Operator =
	void operator= (const Vector b) {
		if(this->m_capacity == b.m_capacity){
			for (size_t i = 0; i < this->m_capacity; i++) {
				this->m_array[i] = b.m_array[i];
			}
		}
	}
	//Vergleichsoperator 
	bool operator==(const Vector& b) {
		bool checker = true;
		for (size_t i = 0; i < this->m_capacity; i++) {
			if (!(this->m_array[i] == b.m_array[i])) {
				checker = false;				
			}
		}
		return checker;
	}

	//Addition Vektor + Skalar
	Vector operator+(T skalar) {
		Vector<T, S> sum;

		for (size_t i = 0; i < this->m_capacity; i++) {
			sum.m_array[i] = this->m_array[i] + skalar;
		}
		return sum;
	}

	//Addition Skalar + Vektor
	friend Vector operator+(const T &skalar, const Vector& b) {
		Vector<T, S> sum;

		for (size_t i = 0; i < b.m_capacity; i++) {
			sum.m_array[i] = b.m_array[i] + skalar;
		}
		return sum;
	}

	//Subktration Vektor - Skalar
	Vector operator-(T skalar) {
		Vector<T, S> subtration;

		for (size_t i = 0; i < this->m_capacity; i++) {
			subtration.m_array[i] = this->m_array[i] - skalar;
		}
		return subtration;
	}

	//Subktration Skalar - Vektor
	friend Vector operator-(const T &skalar, const Vector& b) {
		Vector<T, S> subtration;

		for (size_t i = 0; i < b.m_capacity; i++) {
			subtration.m_array[i] = skalar - b.m_array[i];
		}
		return subtration;
	}

	//Multiplikation Vektor * Skalar
	Vector operator*(T skalar) {
		Vector<T, S> produkt;

		for (size_t i = 0; i < this->m_capacity; i++) {
			produkt.m_array[i] = this->m_array[i] * skalar;
		}
		return produkt;
	}

	//Multiplikation Skalar * Vektor
	friend Vector operator*(const T &skalar, const Vector& b) {
		Vector<T, S> produkt;

		for (size_t i = 0; i < b.m_capacity; i++) {
			produkt.m_array[i] = skalar * b.m_array[i];
		}
		return produkt;
	}

	//Division Vektor / Skalar
	Vector operator/(T skalar) {
		Vector<T, S> division;

		for (size_t i = 0; i < this->m_capacity; i++) {
			division.m_array[i] = this->m_array[i] / skalar;
		}
		return division;
	}

	//Division Skalar / Vektor
	friend Vector operator/(const T &skalar, const Vector& b) {
		Vector<T, S> division;

		for (size_t i = 0; i < b.m_capacity; i++) {
			division.m_array[i] = skalar / b.m_array[i];
		}
		return division;
	}


	friend ostream& operator<<(ostream& os, const Vector& v) {
		os << '[';
		if (v.m_capacity > 0) os << v[0];
		for (size_t i = 1; i < v.m_capacity; i++) {
			os << ',' << v[i];
		}

		return os << ']';
	}

	//Skalarprodukt
	/*template<typename skalarproduct>
	skalarproduct operator**(const Vector& a, const Vector& b) {
		T sum = 0;

		for (size_t i = 0; i < a.m_capacity; i++) {
			sum += a.m_array[i] * b.m_array[i];
		}
		return sum;
	}*/
	
};