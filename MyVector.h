#pragma once
#include <stdexcept>
#include <cstring>
#pragma warning(disable : 4018)
#pragma warning(disable : 6386)

template<typename _T>
class MyVector
{
public:
	class MyVectorIterator;
private:
	size_t size;
	size_t capacity;
	_T* array;
public: 
	MyVector() 
		:
		size(0),
		capacity(0),
		array(nullptr)
	{}

	MyVector(const size_t& size_) 
		try :
		size(size_),
		capacity(size_ + 10),
		array(new _T[capacity])
	{} catch (...) { delete[] array; throw; }

	MyVector(const MyVector& vector) 
		try : 
		size(vector.size),
		capacity(vector.capacity),
		array(new _T[vector.capacity]) 
	{
		for (unsigned int i = 0; i < this->size; ++i)
		{
			array[i] = vector.array[i];
		}
	
	} catch (...) { delete[] array; throw; }

	MyVector(MyVector&& other) 
	{
		size = other.size;
		capacity = other.capacity;
		delete[] array;
		array = other.array;
		other.array = nullptr;
	}

	MyVector& operator=(const MyVector& other) 
	{
		if (this == &other)
			return *this;
		MyVector temp(other.size);
		temp.capacity = other.capacity;
		
		for (unsigned int i = 0; i < other.size; ++i)
		{
			temp.array[i] = other.array[i];
		}

		delete[] array;
		capacity = temp.capacity;
		size = temp.size;
		array = temp.array;
		temp.array = nullptr;
		return *this;
	}

	MyVector operator=(const MyVector&& other) 
	{
		if (this == &other)
			return *this;
		delete[] array;
		array = other.array;
		size = other.size;
		capacity = other.capacity;
		other.array = nullptr;
	}

	
public: 
	~MyVector()
	{
		delete[] array;
	}
public: 
	_T& operator[] (const int& index) const
	{
		if (index >= size || index < 0)
			throw std::out_of_range("out of range"); 
		return array[index];
	}
	bool operator==(const MyVector& vector) const
	{
		if (this == &vector)
			return true;
		if (size != vector.size)
			return false;
		for (unsigned int i = 0; i < size; ++i)
		{
			if (array[i] != vector.array[i])
				return false;
		}
		return true;
	}
	bool operator!=(const MyVector& vector) const
	{
		return !(*this == vector);
	}
public: 
	size_t get_size() const
	{
		return size;
	}
	size_t get_capacity() const
	{
		return capacity;
	}
	void push_back(const _T& element)
	{
		if (size + 1 <= capacity)
		{
			size++;
			array[size - 1] = element;
			return;
		}
		MyVector<_T> new_vector(size * 2); 
    new_vector.size = size + 1;
		for (unsigned int i = 0; i < size; ++i)
		{
			new_vector[i] = array[i];
		}
		new_vector[size] = element;
		delete[] array;
		array = new_vector.array;
		size = new_vector.size;
		capacity = new_vector.capacity;
		new_vector.array = nullptr;
	}
	void pop_back()
	{
		if (size > 0)
			size--;
		else
			throw std::out_of_range("out of range");
	}
	void erase(const int& index)
	{
		if (index >= size || index < 0)
			throw std::out_of_range("out of range");

		for (int i = index; i < size - 1; ++i) 
		{
			std::swap(array[i], array[i + 1]);
		}
		size--;
	}
	void erase(const MyVectorIterator& iterator)
	{
		if (&iterator > &(array[size]) || &iterator < array)
		{
			throw std::out_of_range("out of range");
		}
		for (unsigned int i = 0; i < size - 1; ++i)
		{
			if (&iterator == &(array[i]))
			{
				for (unsigned int j = i; j < size - 1; ++j)
				{
					std::swap(array[j], array[j + 1]);
				}
				size--;
				return;
			}
		}
		size--;
	}
	void clear()
	{
		size = 0;
	}

	MyVectorIterator begin() const
	{
		return MyVectorIterator(array);
	}

	MyVectorIterator end() const
	{
		return --MyVectorIterator(array + size);
	}

	void insert(const _T& value, const int& index)
	{
		if (index < 0 || index >= size)
			throw std::out_of_range("out of range");

		if (size + 1 <= capacity)
		{
      std::memmove(array + index + 1, array + index, (size - index) * sizeof(_T));
      array[index] = value;
      size++;
		}
		else
		{
			MyVector new_vector(size + 1);
			for (unsigned int i = 0, j = 0; i < size + 1; ++i)
			{
				if (i == index)
				{
					new_vector.array[j] = value;
					j++;
					new_vector.array[j] = array[i];
				}
				else
				{
					new_vector.array[j] = array[i];
				}
				j++;
			}
			delete[] array;
			array = new_vector.array;
			size = new_vector.size;
			capacity = new_vector.capacity;
			new_vector.array = nullptr;
		}
	}

	void shrink_to_fit()
	{
		if (size == capacity)
			return;
		MyVector<_T> new_vector (size);
		try {
			for (unsigned int i = 0; i < size; ++i)
			{
				new_vector.array[i] = array[i];
			}
		}
		catch (...)
		{
			delete[] new_vector.array;
			throw;
		}
		capacity = size;
		delete[] array;
		array = new_vector.array;
		new_vector.array = nullptr;
	}
	void resize(const int& _value)
	{
		if (_value <= capacity)
		{
			size = _value;
			return;
		}
		MyVector<_T> new_vector(_value);
		try {
			for (unsigned int i = 0; i < size; ++i)
			{
				new_vector.array[i] = array[i];
			}
		}
		catch (...)
		{
			delete[] new_vector.array;
			throw;
		}
		size = new_vector.array;
		capacity = new_vector.capacity;
		delete[] array;
		array = new_vector.array;
		new_vector.array = nullptr;
	}

	class MyVectorIterator
	{
	private:
		_T* current;
	public:
		MyVectorIterator()
			: current(nullptr) {}

		MyVectorIterator(_T* _pointer)
      : current(_pointer) {}

	public:
		_T& operator*() const { return *(current); }
		_T* operator&() const{ return current; }

		MyVectorIterator operator++() 
		{
			current++;
			return *this;
		}

		MyVectorIterator operator++(int) 
		{
			MyVectorIterator temp = *this;
			current++;
			return temp;
		}
		MyVectorIterator operator--() 
		{
			current--;
			return *this;
		}
		MyVectorIterator operator--(int) 
		{
			MyVectorIterator temp = *this;
			current--;
			return temp;
		}
	};
};

