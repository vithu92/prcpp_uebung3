#pragma once

#include <memory>
#include <iostream>


using namespace std;

template<class T> class Vector {

	unique_ptr<T[]> m_array;

	size_t m_capacity; //die Länge des Arrays m_array
	size_t m_size; //die Anzahl Elemente im Array m_array

public:

	Vector(size_t capacity = 10)
		: m_array(new T[capacity]), m_capacity(capacity), m_size(0) {};

	//Konstruktor mit Vektor als Parameter
	Vector(const Vector& v)
		: m_array(new T[v.m_capacity]), m_capacity(v.m_capacity), m_size(v.m_size) {
		for (size_t i = 0; i < m_size; i++) {
			m_array[i] = v[i];
		}
	}

	//TODO
	Vector(Vector&& v) : m_array(move(v.m_array)), m_capacity(v.m_capacity), m_size(v.m_size) {
		v.m_size = v.m_capacity = 0;
	}

	//Konstruktor mit Dimensionsgrösse und jeder Dimensionswert denselben Wert
	Vector(size_t size, const T& val)
		: m_array(new T[size]), m_capacity(size), m_size(size) {
		for (size_t i = 0; i < m_size; i++) m_array[i] = val;
	}



	//Konstruktur mit Iniitialisierungsliste (Dimensionswerte)
	Vector(const initializer_list<T>& data): m_array(new T[data.size()]), m_capacity(data.size()), m_size(data.size()){
				
		auto it = data.begin();
		for (size_t i = 0; i < m_capacity; i++) {
			m_array[i] = *it;
			it++;
		}
	}
	
	//Addition Operator
	Vector operator+(const Vector& b) {
		Vector sum = new Vector(b.m_size);
		if (this.m_size == b.m_size) {
			for (size_t i = 0; i < this.m_size; i++) {
				sum.m_array[i] = this.m_array[i] + b.m_array[i];
			}
		}
		else
		{
			throw "Die Vektoren haben unterschiedliche Dimensionen!";
		}

		return sum;
	}


	//Subtraktion Operator
	Vector operator-(const Vector& b) {
		Vector subtraktion = new Vector(b.m_size);
		
		if (this.m_size == b.m_size) {
			for (size_t i = 0; i < this.m_size; i++) {
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
		Vector produkt = new Vector(b.m_size);

		if (this.m_size == b.m_size) {
			for (size_t i = 0; i < this.m_size; i++) {
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
		Vector division = new Vector(b.m_size);

		if (this.m_size == b.m_size) {
			for (size_t i = 0; i < this.m_size; i++) {
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
		if (i >= m_size) throw out_of_range("index is too large");
		return m_array[i];
	}

	//Addition mit Skalar
	Vector SkalarAddition(T skalar) {
		
		//abfragen nach dem Typ des Arrays
		auto ArrayType = remove_all_extents<decltype(this.m_array)>::type;


		for (size_t i = 0; i < this.m_size; i++) {
			this.m_array[i] = this.m_array[i] + skalar;
		}
		return this;
	}

	//Subtraktion mit Skalar als Subtrahend
	Vector SkalarSubtraktionLinks(T skalar) {

		//abfragen nach dem Typ des Arrays
		auto ArrayType = remove_all_extents<decltype(this.m_array)>::type;


		for (size_t i = 0; i < this.m_size; i++) {
			this.m_array[i] = this.m_array[i] - skalar;
		}
		return this;
	}

	//Subtraktion mit Skalar als Minuend
	Vector SkalarSubtraktionRechts(T skalar) {

		//abfragen nach dem Typ des Arrays
		auto ArrayType = remove_all_extents<decltype(this.m_array)>::type;


		for (size_t i = 0; i < this.m_size; i++) {
			this.m_array[i] = skalar - this.m_array[i];
		}
		return this;
	}

	//Multiplikation mit Skalar
	Vector SkalarMultiplikation(T skalar) {

		//abfragen nach dem Typ des Arrays
		auto ArrayType = remove_all_extents<decltype(this.m_array)>::type;


		for (size_t i = 0; i < this.m_size; i++) {
			this.m_array[i] = this.m_array[i] * skalar;
		}
		return this;
	}

	//Division mit Skalar als Divisor
	Vector SkalarDivisionRechts(T skalar) {

		//abfragen nach dem Typ des Arrays
		auto ArrayType = remove_all_extents<decltype(this.m_array)>::type;

		if(skalar != 0){
			for (size_t i = 0; i < this.m_size; i++) {
				this.m_array[i] = this.m_array[i] / skalar;
			}
		}
		return this;
	}

	//Divison mit Skalar als Dividend
	Vector SkalarDivisonLinks(T skalar) {

		//abfragen nach dem Typ des Arrays
		auto ArrayType = remove_all_extents<decltype(this.m_array)>::type;


		for (size_t i = 0; i < this.m_size; i++) {
			if(this.m_array[i] != 0) this.m_array[i] = skalar / this.m_array[i];
		}
		return this;
	}
	
	//Skalarprodukt zweier Vektoren
	T Skalarprodukt(const Vector& b) {
		T skalarprodukt = new Vector(b.m_size);

		for (size_t i = 0; i < this.m_size; i++) {
			skalarprodukt.m_array[i] = this.m_array[i] * b.m_array[i];
		}
		return skalarprodukt;
	}

	friend ostream& operator<<(ostream& os, const Vector& v) {
		os << '[';
		if (v.m_size > 0) os << v[0];
		for (size_t i = 1; i < v.m_size; i++) {
			os << ',' << v[i];
		}

		return os << ']';
	}

	
};