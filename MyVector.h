#pragma once

#pragma warning(disable : 4018)


template<typename _T>
class MyVector
{
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
		capacity(size_),
		array(new _T[size_])
	{} catch (...) { delete[] this->array; throw; }

	MyVector(const MyVector& vector) 
		try : 
		size(vector.size),
		capacity(vector.capacity),
		array(new _T[vector.capacity]) 
	{
		for (unsigned int i = 0; i < this->size; ++i)
		{
			this->array[i] = vector.array[i];
		}
	
	} catch (...) { delete[] this->array; throw; }

	MyVector(MyVector&& other) 
	{
		this->size = other.size;
		this->capacity = other.capacity;
		delete[] this->array;
		this->array = other.array;
		other.array = nullptr;
	}

	MyVector& operator=(const MyVector& other) 
	{
		if (this == &other)
			return *this;
		MyVector temp(other.size);
		temp.capacity = other.capacity;
		std::copy(other.array, other.array + other.size, temp.array);

		delete[] this->array;
		this->capacity = temp.capacity;
		this->size = temp.size;
		this->array = temp.array;
		temp.array = nullptr;
		return *this;
	}

	MyVector operator=(const MyVector&& other) 
	{
		if (this == &other)
			return *this;
		delete[] this->array;
		this->array = other.array;
		this->size = other.size;
		this->capacity = other.capacity;
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
		if (index >= this->size || index < 0)
			throw std::out_of_range("out of range"); 
		return array[index];
	}
	bool operator==(const MyVector& vector) const
	{
		if (this == &vector)
			return true;
		if (this->size != vector.size)
			return false;
		for (unsigned int i = 0; i < this->size; ++i)
		{
			if (this->array[i] != vector.array[i])
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
		return this->size;
	}
	size_t get_capacity() const
	{
		return this->capacity;
	}
	void push_back(const _T& element) // крч, нужно массив заполнить залупой всякой, тогда всё ок будет.
	{
		if (this->size + 1 <= this->capacity)
		{
			this->array[this->size++] = element;
			return;
		}
		MyVector<_T> new_vector(this->capacity + 50); 
		new_vector.size = this->size + 1;
		for (unsigned int i = 0; i < this->size; ++i)
		{
			new_vector[i] = this->array[i];
		}
		new_vector.array[this->size] = element; 
		delete[] this->array;
		this->array = new_vector.array;
		this->size = new_vector.size++;
		this->capacity = new_vector.capacity;
		new_vector.array = nullptr;
	}
	void pop_back()
	{
		if (this->size > 0)
			this->size--;
		else
			throw std::out_of_range("out of range");
	}
	void erase(const int& index)
	{
		if (index > size || index < 0)
			throw std::out_of_range("out of range");
		for (int i = index; i < this->size - 1; ++i) 
		{
			std::swap(this->array[i], this->array[i + 1]);
		}
		this->size--;
	}
	void erase(const MyVectorIterator& iterator)
	{
		for (unsigned int i = 0; i < this->size - 1; ++i)
		{
			if (&(this->array[i]) == &iterator)
			{
				std::swap(this->array[i], this->array[i + 1]);
			}
		}
		this->size--;
	}
	void clear()
	{
		this->size = 0;
	}

	MyVectorIterator begin() const
	{
		return MyVectorIterator(this->array);
	}

	MyVectorIterator end() const
	{
		return MyVectorIterator(this->array + this->size);
	}
	/*
	void insert(const _T& value, const int& index)
	{
		if (index < 0 || index > this->size)
			throw std::out_of_range("out of range");

		if (this->size + 1 <= this->capacity)
		{
			for (int i = this->size - 1; i != 0; --i)
			{
				if (i == index)
				{
					this->array[i] = value;
					this->size++;
					break;
				}
				else
				{
					this->array[i] = this->array[i - 1];
				}
			}
		}
		else
		{
			MyVector new_vector(this->size + 1);
			for (unsigned int i = 0, j = 0; i < this->size + 1; ++i)
			{
				if (i != index)
				{
					new_vector.array[j] = this->array[i];
				}
				else
				{
					new_vector.array[j] = value;
					j++;
					new_vector.array[j] = this->array[i];
				}
				j++;
			}
		}
	}
	*/
	void shrink_to_fit()
	{
		if (this->size == this->capacity)
			return;
		MyVector<_T> new_vector (this->size);
		try {
			for (unsigned int i = 0; i < this->size; ++i)
			{
				new_vector.array[i] = this->array[i];
			}
		}
		catch (...)
		{
			delete[] new_vector.array;
			throw;
		}
		this->capacity = this->size;
		delete[] this->array;
		this->array = new_vector.array;
		new_vector.array = nullptr;
	}
	void resize(const int& _value)
	{
		if (_value <= this->size)
		{
			this->size = _value;
			return;
		}
		MyVector<_T> new_vector(_value);
		try {
			for (unsigned int i = 0; i < this->size; ++i)
			{
				new_vector[i] = this->array[i];
			}
		}
		catch (...)
		{
			delete[] new_vector.array;
			throw;
		}
		this->size = _value;
		this->capacity = _value;
		delete[] this->array;
		this->array = new_vector.array;
		new_vector.array = nullptr;
	}


	class MyVectorIterator
	{
	private:
		_T* current;
	public:
		MyVectorIterator()
			:
			current(nullptr)
		{}
		MyVectorIterator(_T* _pointer)
			:
			current(_pointer) {}
	public:
		_T& operator*() const
		{
			return *(this->current);
		}
		_T* operator&() const
		{
			return this->current;
		}
		MyVectorIterator operator++() // prefix
		{
			this->current++;
			return *this;
		}
		MyVectorIterator operator++(int) // postfix
		{
			MyVectorIterator temp = *this;
			this->current++;
			return temp;
		}
		MyVectorIterator operator--() // prefix
		{
			this->current--;
			return *this;
		}
		MyVectorIterator operator--(int) // postfix
		{
			MyVectorIterator temp = *this;
			this->current--;
			return temp;
		}
	};
};

