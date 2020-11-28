#pragma once

#include <vector>

// Deklaration
template<typename Type>
class TCArray2d
{
public:
	TCArray2d(); // Default-Konstruktor
	TCArray2d(unsigned int Width, unsigned int Height); // Konstruktor
	TCArray2d(unsigned int Width, unsigned int Height, const Type& _Val); // Konstruktor

	void Resize(unsigned int Width, unsigned int Height);

	void Set(unsigned int x, unsigned int y, Type Value);
	Type Get(unsigned int x, unsigned int y) const;

	unsigned int Width() const; // const: Methode, die keine Membervariablen ver�ndert
	unsigned int Height() const; // const: Methode, die keine Membervariablen ver�ndert

private:
	unsigned int Linearize(unsigned int x, unsigned int y) const;

	unsigned int m_Width; // Membervariable
	unsigned int m_Height; // Membervariable
	std::vector<Type> m_Data; // Membervariable
};

// Definition
template<typename Type>
TCArray2d<Type>::TCArray2d()
	: m_Width(0), m_Height(0)
{
}

template<typename Type>
TCArray2d<Type>::TCArray2d(unsigned int Width, unsigned int Height)
	: m_Width(Width), m_Height(Height), m_Data(Width * Height) // Basis-Initialisierer
{
}

template<typename Type>
TCArray2d<Type>::TCArray2d(unsigned int Width, unsigned int Height, const Type& _Val)
	: m_Width(Width), m_Height(Height), m_Data(Width * Height, _Val) // Basis-Initialisierer
{
}


template<typename Type>
void TCArray2d<Type>::Resize(unsigned int Width, unsigned int Height)
{
	if (m_Width != Width || m_Height != Height)
	{
		m_Width = Width;
		m_Height = Height;
		m_Data.resize(Width * Height);
	}
}

template<typename Type>
void TCArray2d<Type>::Set(unsigned int x, unsigned int y, Type Value)
{
	if (x < m_Width && y < m_Height)
	{
		m_Data[Linearize(x, y)] = Value;
	}
}

template<typename Type>
Type TCArray2d<Type>::Get(unsigned int x, unsigned int y) const
{
	if (x < m_Width && y < m_Height)
	{
		return m_Data[Linearize(x, y)];
	}

	return Type();
}

template<typename Type>
unsigned int TCArray2d<Type>::Width() const
{
	return m_Width;
}

template<typename Type>
unsigned int TCArray2d<Type>::Height() const
{
	return m_Height;
}

template<typename Type>
unsigned int TCArray2d<Type>::Linearize(unsigned int x, unsigned int y) const
{
	return x + y * m_Width;
}
