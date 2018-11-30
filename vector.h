#pragma once

#include <memory>
#include <iostream>


using namespace std;

template<class T> class Vector {
	unique_ptr<T[]> m_array;

	//Anzahl der Elemente im Array m_array
	size_t m_size;
	//Die Länge des Arrays m_array
	size_t m_capacity:


public:

	//Konstruktor mit Dimensionsgrösse und -werte
	Vector(size_t size, const T& val)
		:m_array(new T[size]), m_capacity(size), m_size(size){
		for (size_t i = 0; i < m_size; i++) m_array[i] = val;
	}

	//Konstruktur mit Dimensionsgrösse
	Vector(size_t capacity = 20) : m_array(new T[capacity]), m_capacity(capacity), m_size(0) {};

	//Konstruktur mit Iniitialisierungsliste (Dimensionswerte)
	Vector(const initializer_list<T>& data){
		size_t s = __min(data.size(), m_capacity);


		auto it = data.begin();
		for (size_t i = 0; i < m_capacity; i++) {
			this->at(i) = *it;
		}
	}
	
	//Addition Operator
	Vector operator+(const Vector& b) {
		Vector sum = new Vector(b.m_size);
		if (this->m_size == b.m_size) {
			for (size_t i = 0; i < this->m_size; i++) {
				sum.m_array[i] = this->m_array[i]+ b.m_array[i]
			}
		}
		else
		{
			throw "Die Vektoren haben unterschiedliche Dimensionen!" 
		}

		return sum;
	}


	//Subtraktion Operator
	Vector operator-(const Vector& b) {
		Vector subtraktion = new Vector(b.m_size);
		
		if (this->m_size == b.m_size) {
			for (size_t i = 0; i < this->m_size; i++) {
				sum.m_array[i] = this->m_array[i] - b.m_array[i]
			}
		}
		else
		{
			throw "Die Vektoren haben unterschiedliche Dimensionen!"
		}
		return subtraktion;
	}

	//Multiplikation Operator
	Vector operator*(const Vector& b) {
		Vector produkt = new Vector(b.m_size);

		if (this->m_size == b.m_size) {
			for (size_t i = 0; i < this->m_size; i++) {
				sum.m_array[i] = this->m_array[i] * b.m_array[i]
			}
		}
		else
		{
			throw "Die Vektoren haben unterschiedliche Dimensionen!"
		}
		return produkt;
	}

	//Divison Operator
	Vector operator/(const Vector& b) {
		Vector division = new Vector(b.m_size);

		if (this->m_size == b.m_size) {
			for (size_t i = 0; i < this->m_size; i++) {
				if(b.m_array[i] != 0){
				sum.m_array[i] = this->m_array[i] * b.m_array[i]
				}else{ throw "Division nicht möglich, da man nicht durch 0 teilen kann" }
			}
		}
		else
		{
			throw "Die Vektoren haben unterschiedliche Dimensionen!"
		}
		return produkt;
	}

	//Addition mit Skalar
	Vector SkalarAddition(T skalar) {
		
		//abfragen nach dem Typ des Arrays
		auto ArrayType = remove_all_extents<decltype(this->m_array)>::type;


		for (size_t i = 0; i < this->m_size; i++) {
			this->m_array[i] = this->m_array[i] + (ArrayType)skalar;
		}
		return this;
	}

	//Subtraktion mit Skalar als Subtrahend
	Vector SkalarSubtraktionLinks(T skalar) {

		//abfragen nach dem Typ des Arrays
		auto ArrayType = remove_all_extents<decltype(this->m_array)>::type;


		for (size_t i = 0; i < this->m_size; i++) {
			this->m_array[i] = this->m_array[i] - (ArrayType)skalar;
		}
		return this;
	}

	//Subtraktion mit Skalar als Minuend
	Vector SkalarSubtraktionRechts(T skalar) {

		//abfragen nach dem Typ des Arrays
		auto ArrayType = remove_all_extents<decltype(this->m_array)>::type;


		for (size_t i = 0; i < this->m_size; i++) {
			this->m_array[i] = (ArrayType)skalar - this->m_array[i];
		}
		return this;
	}

	//Multiplikation mit Skalar
	Vector SkalarAddition(T skalar) {

		//abfragen nach dem Typ des Arrays
		auto ArrayType = remove_all_extents<decltype(this->m_array)>::type;


		for (size_t i = 0; i < this->m_size; i++) {
			this->m_array[i] = this->m_array[i] * (ArrayType)skalar;
		}
		return this;
	}

	//Division mit Skalar als Divisor
	Vector SkalarDivisionRechts(T skalar) {

		//abfragen nach dem Typ des Arrays
		auto ArrayType = remove_all_extents<decltype(this->m_array)>::type;

		if((ArrayType) skalar != 0){
			for (size_t i = 0; i < this->m_size; i++) {
				this->m_array[i] = this->m_array[i] / (ArrayType)skalar;
			}
		}
		return this;
	}

	//Divison mit Skalar als Dividend
	Vector SkalarAddition(T skalar) {

		//abfragen nach dem Typ des Arrays
		auto ArrayType = remove_all_extents<decltype(this->m_array)>::type;


		for (size_t i = 0; i < this->m_size; i++) {
			if(this->m_array[i] != 0) this->m_array[i] = (ArrayType)skalar / this->m_array[i];
		}
		return this;
	}
	
	//Skalarprodukt zweier Vektoren
	T Skalarprodukt(const Vector& b) {
		T skalarprodukt = new Vector(b.m_size);

		for (size_t i = 0; i < this->m_size; i++) {
			skalarprodukt.m_array[i] = this->m_array[i] * b.m_array[i];
		}
		return skalarprodukt;
	}

};