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
		Vector subtraktion = new Vector(b.m_capacity);
		
		if (this.m_capacity == b.m_capacity) {
			for (size_t i = 0; i < this.m_capacity; i++) {
				subtraktion.m_array[i] = this.m_array[i] - b.m_array[i];
			}
		}
		else
		{
			throw "Die Vektoren haben unterschiedliche Dimensionen!";
		}
		return subtraktion;
	}

	//Multiplikation Operator
	Vector operator* (const Vector& b) {
		Vector produkt = new Vector(b.m_capacity);

		if (this.m_capacity == b.m_capacity) {
			for (size_t i = 0; i < this.m_capacity; i++) {
				produkt.m_array[i] = this.m_array[i] * b.m_array[i];
			}
		}
		else
		{
			throw "Die Vektoren haben unterschiedliche Dimensionen!";
		}
		return produkt;
	}

	//Divison Operator
	Vector operator/(const Vector& b) {
		Vector division = new Vector(b.m_capacity);

		if (this.m_capacity == b.m_capacity) {
			for (size_t i = 0; i < this.m_capacity; i++) {
				if(b.m_array[i] != 0){
					division.m_array[i] = this.m_array[i] * b.m_array[i];
				}
				else{
					throw "Division nicht möglich, da man nicht durch 0 teilen kann";
				}
			}
		}
		else
		{
			throw "Die Vektoren haben unterschiedliche Dimensionen!";
		}
		return division;
	}

	//Index Operator (nur Lesezugriff)
	const T& operator[] (size_t i) const {
		if (i >= m_capacity) throw out_of_range("index is too large");
		return m_array[i];
	}

	//Addition mit Skalar
	Vector SkalarAddition(T skalar) {
		
		//abfragen nach dem Typ des Arrays
		auto ArrayType = remove_all_extents<decltype(this.m_array)>::type;


		for (size_t i = 0; i < this.m_capacity; i++) {
			this.m_array[i] = this.m_array[i] + skalar;
		}
		return this;
	}

	//Subtraktion mit Skalar als Subtrahend
	Vector SkalarSubtraktionLinks(T skalar) {

		//abfragen nach dem Typ des Arrays
		auto ArrayType = remove_all_extents<decltype(this.m_array)>::type;


		for (size_t i = 0; i < this.m_capacity; i++) {
			this.m_array[i] = this.m_array[i] - skalar;
		}
		return this;
	}

	//Subtraktion mit Skalar als Minuend
	Vector SkalarSubtraktionRechts(T skalar) {

		//abfragen nach dem Typ des Arrays
		auto ArrayType = remove_all_extents<decltype(this.m_array)>::type;


		for (size_t i = 0; i < this.m_capacity; i++) {
			this.m_array[i] = skalar - this.m_array[i];
		}
		return this;
	}

	//Multiplikation mit Skalar
	Vector SkalarMultiplikation(T skalar) {

		//abfragen nach dem Typ des Arrays
		auto ArrayType = remove_all_extents<decltype(this.m_array)>::type;


		for (size_t i = 0; i < this.m_capacity; i++) {
			this.m_array[i] = this.m_array[i] * skalar;
		}
		return this;
	}

	//Division mit Skalar als Divisor
	Vector SkalarDivisionRechts(T skalar) {

		//abfragen nach dem Typ des Arrays
		auto ArrayType = remove_all_extents<decltype(this.m_array)>::type;

		if(skalar != 0){
			for (size_t i = 0; i < this.m_capacity; i++) {
				this.m_array[i] = this.m_array[i] / skalar;
			}
		}
		return this;
	}

	//Divison mit Skalar als Dividend
	Vector SkalarDivisonLinks(T skalar) {

		//abfragen nach dem Typ des Arrays
		auto ArrayType = remove_all_extents<decltype(this.m_array)>::type;


		for (size_t i = 0; i < this.m_capacity; i++) {
			if(this.m_array[i] != 0) this.m_array[i] = skalar / this.m_array[i];
		}
		return this;
	}
	
	//Skalarprodukt zweier Vektoren
	T Skalarprodukt(const Vector& b) {
		T skalarprodukt = new Vector(b.m_capacity);

		for (size_t i = 0; i < this.m_capacity; i++) {
			skalarprodukt.m_array[i] = this.m_array[i] * b.m_array[i];
		}
		return skalarprodukt;
	}

	friend ostream& operator<<(ostream& os, const Vector& v) {
		os << '[';
		if (v.m_capacity > 0) os << v[0];
		for (size_t i = 1; i < v.m_capacity; i++) {
			os << ',' << v[i];
		}

		return os << ']';
	}

	
};