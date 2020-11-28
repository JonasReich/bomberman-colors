#pragma once

#include <cstdint>
#include <vector>

// Deklaration
template<typename Type>
class TCArray2d
{
public:
	TCArray2d(); // Default-Konstruktor
	TCArray2d(uint32_t Width, uint32_t Height); // Konstruktor
	TCArray2d(uint32_t Width, uint32_t Height, const Type& _Val); // Konstruktor

	void Resize(uint32_t Width, uint32_t Height);

	void Set(uint32_t x, uint32_t y, Type Value);
	Type Get(uint32_t x, uint32_t y) const;

	uint32_t Width() const; // const: Methode, die keine Membervariablen ver�ndert
	uint32_t Height() const; // const: Methode, die keine Membervariablen ver�ndert

private:
	uint32_t Linearize(uint32_t x, uint32_t y) const;

	uint32_t m_Width; // Membervariable
	uint32_t m_Height; // Membervariable
	std::vector<Type> m_Data; // Membervariable
};

// Definition
template<typename Type>
TCArray2d<Type>::TCArray2d()
	: m_Width(0), m_Height(0)
{
}

template<typename Type>
TCArray2d<Type>::TCArray2d(uint32_t Width, uint32_t Height)
	: m_Width(Width), m_Height(Height), m_Data(Width * Height) // Basis-Initialisierer
{
}

template<typename Type>
TCArray2d<Type>::TCArray2d(uint32_t Width, uint32_t Height, const Type& _Val)
	: m_Width(Width), m_Height(Height), m_Data(Width * Height, _Val) // Basis-Initialisierer
{
}


template<typename Type>
void TCArray2d<Type>::Resize(uint32_t Width, uint32_t Height)
{
	if (m_Width != Width || m_Height != Height)
	{
		m_Width = Width;
		m_Height = Height;
		m_Data.resize(Width * Height);
	}
}

template<typename Type>
void TCArray2d<Type>::Set(uint32_t x, uint32_t y, Type Value)
{
	if (x < m_Width && y < m_Height)
	{
		m_Data[Linearize(x, y)] = Value;
	}
}

template<typename Type>
Type TCArray2d<Type>::Get(uint32_t x, uint32_t y) const
{
	if (x < m_Width && y < m_Height)
	{
		return m_Data[Linearize(x, y)];
	}

	return Type();
}

template<typename Type>
uint32_t TCArray2d<Type>::Width() const
{
	return m_Width;
}

template<typename Type>
uint32_t TCArray2d<Type>::Height() const
{
	return m_Height;
}

template<typename Type>
uint32_t TCArray2d<Type>::Linearize(uint32_t x, uint32_t y) const
{
	return x + y * m_Width;
}
