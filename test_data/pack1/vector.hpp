#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "ft_templates.hpp"

namespace ft
{
	template<class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
			typedef T									value_type;
			typedef Allocator							allocator_type;
			typedef value_type&							reference;
			typedef const value_type&					const_reference;
			typedef typename Allocator::pointer			pointer;
			typedef typename Allocator::const_pointer	const_pointer;
			class										iterator;
			class										const_iterator;
			typedef std::size_t							size_type;
			typedef std::ptrdiff_t						difference_type;
			typedef	ft::reverse_iterator<iterator>			reverse_iterator;
			typedef	ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			// Member functions
			vector();
			explicit vector( const Allocator& alloc );
			explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator());
			template< class InputIt > vector( typename enable_if<is_iterator<InputIt>::value,
				InputIt>::type first, InputIt last, const Allocator& alloc = Allocator() );
			vector( const vector& other );
			~vector();
			vector& operator=( const vector& other );
			void assign( size_type count, const T& value );
			template<class InputIterator>
				typename enable_if<!is_integral<InputIterator>::value, void>::type assign(InputIterator first, InputIterator last);
			// Element access
			reference	at( size_type pos );
			const_reference	at( size_type pos ) const;
			reference	operator[]( size_type pos );
			const_reference	operator[]( size_type pos ) const;
			reference	front();
			const_reference	front() const;
			reference	back();
			const_reference	back() const;
			// Iterators
			iterator	begin();
			const_iterator	begin() const;
			iterator	end();
			const_iterator	end() const;
			reverse_iterator	rbegin();
			const_reverse_iterator	rbegin() const;
			reverse_iterator	rend();
			const_reverse_iterator	rend() const;
			// Capacity
			bool 		empty() const;
			size_type	size() const;
			size_type	max_size() const;
			void		reserve( size_type new_cap );
			size_type	capacity() const;
			// Modifiers
			void		clear();
			iterator	insert( iterator pos, const T& value );
			void		insert( iterator pos, size_type count, const T& value );
			template< class InputIt > void	insert( iterator pos, 
				typename enable_if<is_iterator<InputIt>::value, InputIt>::type first, InputIt last );
			iterator 	erase( iterator pos );
			iterator 	erase( iterator first, iterator last );
			void		push_back( const T& value );
			void		pop_back();
			void		resize( size_type count, T value = T() );
			void		swap( vector& other );
			T* 			data();
			const T*	data() const;
			allocator_type	get_allocator() const;

		private:
			size_type		_size;
			size_type		_capacity;
			allocator_type	_alloc;
			pointer			_data;
	};

	// Member functions
	template<class T, class Allocator>
	vector<T, Allocator>::vector() : _size(0), _capacity(0), _alloc(), _data(_alloc.allocate(0)) {}

	template<class T, class Allocator>
	vector<T, Allocator>::vector( const Allocator& alloc ) :
		_size(0), _capacity(0), _alloc(alloc), _data(_alloc.allocate(0)) {}

	template<class T, class Allocator>
	vector<T, Allocator>::vector( vector<T, Allocator>::size_type count, const T& value, 
		const Allocator& alloc) : _size(count), _capacity(count), _alloc(alloc)
	{
		size_type i;
		_data = _alloc.allocate(count);
		try {
			for ( i = 0; i< count; ++i)
				_alloc.construct(_data + i, value);
		} catch (...) {
			for (; i > 0; --i)
				_alloc.destroy(_data + i - 1);
			_alloc.deallocate(_data, count);
			throw ;
		}
	}

	template<class T, class Allocator>
	template<class InputIt>
	vector<T, Allocator>::vector(typename enable_if<is_iterator<InputIt>::value, InputIt>::type first, 
		InputIt last, const Allocator& alloc) : _size(0), _capacity(0), _alloc(alloc)
	{
		difference_type dist = last - first;
		_data = _alloc.allocate(dist);
		difference_type i;
		try {
			for (i = 0; i< dist; ++i, ++first)
				_alloc.construct(_data + i, *first);
		} catch (...) {
			for (; i > 0; --i)
				_alloc.destroy(_data + i - 1);
			_alloc.deallocate(_data, dist);
			throw ;
		}
		_size = dist;
		_capacity = dist;
	}

	template<class T, class Allocator>
	vector<T, Allocator>::vector( const vector& other )
	{
		size_type	i;

		_data = _alloc.allocate(other._capacity);
		try {
			for (i = 0; i< other._size; i++)
				_alloc.construct(_data + i, other._data[i]);
		} catch (...) {
			for(; i > 0; --i)
				_alloc.destroy(_data + i - 1);
			_alloc.deallocate(_data, other._capacity);
			throw ;
		}
		_alloc = other._alloc;
		_size = other._size;
		_capacity = other._capacity;
	}

	template<class T, class Allocator>
	vector<T, Allocator>::~vector()
	{
		for (size_type i = 0; i< _size; ++i)
			_alloc.destroy(_data + i);
		_alloc.deallocate(_data, _capacity);
	}

	template<class T, class Allocator>
	vector<T, Allocator> & vector<T, Allocator>::operator= (const vector& x)
	{
		T * data = _alloc.allocate(x._capacity);
		size_type	i;
		try {
			for (i = 0; i< x._size; ++i)
				_alloc.construct(data + i, x._data[i]);
		}
		catch ( ... ) {
			for (; i > 0; --i)
				_alloc.destroy(data + i - 1);
			_alloc.deallocate(data, x._capacity);
			throw ;
		}
		for (i = 0; i< _size; ++i)
			_alloc.destroy(_data + i);
		_alloc.deallocate(_data, _capacity);
		_data = data;
		_capacity = x._capacity;
		_size = x._size;
		return *this;
	}

	// Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
	template<class T, class Allocator>
	void	vector<T, Allocator>::assign( size_type count, const T& value )
	{
		size_type	i;
		if (count < _capacity)
		{
			for (i = 0; i< _size; i++)
				_alloc.destroy(_data + i);
			for (i = 0; i< count; i++)
				_alloc.construct(_data + i, value);
			_size = count;
			return ;
		}
		T * data = _alloc.allocate(count);
		try {
			for (i = 0; i< count; ++i)
				_alloc.construct(data + i, value);
		} catch ( ... ) {
			for (; i > 0; --i)
				_alloc.destroy(data + i - 1);
			_alloc.deallocate(data, count);
			throw ;
		}
		for (i = 0; i< _size; ++i)
			_alloc.destroy(_data + i);
		_alloc.deallocate(_data, _capacity);
		_data = data;
		_capacity = count;
		_size = count;
	}

	// the first member function replaces the sequence controlled by *this with the sequence [first, last), 
	// which must not overlap the initial controlled sequence. 
	// The second member function replaces the sequence controlled by *this with a repetition of n elements of value x.
	// https://www.ibm.com/docs/en/xl-c-and-cpp-aix/13.1.0?topic=functions-vectorassign
	template<class T, class Allocator>
	template<class InputIterator>
	typename enable_if<!is_integral<InputIterator>::value, void>::type vector<T, Allocator>::assign(InputIterator first, InputIterator last)
	{
		int dist = last - first;
		if (dist< 0)
			throw std::length_error("Vector");
		this->clear();
		this->reserve(dist);
		for (; first != last; ++first)
		{
			this->push_back(*first);
		}
	}

	// Element access
	// https://www.ibm.com/docs/en/xl-c-and-cpp-aix/13.1.0?topic=functions-vectorat
	template<class T, class Allocator>
	typename vector<T, Allocator>::reference vector<T, Allocator>::at( size_type pos )
	{
		if (pos >= _size)
			throw std::out_of_range("vector");
		return (*this)[pos];
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::const_reference vector<T, Allocator>::at( size_type pos ) const
	{
		if (pos >= _size)
			throw std::out_of_range("vector");
		return (*this)[pos];
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::reference vector<T, Allocator>::operator[]( size_type pos )
	{
		return _data[pos];
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::const_reference vector<T, Allocator>::operator[]( size_type pos ) const
	{
		return _data[pos];
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::reference vector<T, Allocator>::front()
	{
		return _data[0];
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::const_reference vector<T, Allocator>::front() const
	{
		return _data[0];
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::reference vector<T, Allocator>::back()
	{
		return _data[_size - 1];
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::const_reference vector<T, Allocator>::back() const
	{
		return _data[_size - 1];
	}

	// Iterators
	template<class T, class Allocator>
	typename vector<T, Allocator>::iterator		vector<T, Allocator>::begin()
	{
		return _data;
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::const_iterator		vector<T, Allocator>::begin() const
	{
		return _data;
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::iterator		vector<T, Allocator>::end()
	{
		return _data + _size;
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::const_iterator		vector<T, Allocator>::end() const
	{
		return _data + _size;
	}

	// https://en.cppreference.com/w/cpp/container/vector/rend
	template<class T, class Allocator>
	typename vector<T, Allocator>::reverse_iterator		vector<T, Allocator>::rbegin()
	{
		return reverse_iterator(iterator(_data + _size - 1));
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::const_reverse_iterator		vector<T, Allocator>::rbegin() const
	{
		return const_reverse_iterator(const_iterator(_data + _size - 1));
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::reverse_iterator		vector<T, Allocator>::rend()
	{
		return reverse_iterator(begin());
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::const_reverse_iterator		vector<T, Allocator>::rend() const
	{
		return const_reverse_iterator(begin());
	}

	// Capacity
	template<class T, class Allocator>
	bool	vector<T, Allocator>::empty() const
	{
		return this->begin() == this->end();
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::size_type	vector<T, Allocator>::size() const
	{
		return _size;
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::size_type	vector<T, Allocator>::max_size() const
	{
		return size_type(-1) / sizeof(T);
	}

	template<class T, class Allocator>
	void	vector<T, Allocator>::reserve( size_type new_cap )
	{
		if (_capacity < new_cap)
		{
			size_type i;
			T * data = _alloc.allocate(new_cap);
			try {
				for (i = 0; i < _size; ++i)
					_alloc.construct(data + i, _data[i]);
			} catch (...) {
				for (; i > 0; --i)
					_alloc.destroy(data + i - 1);
				_alloc.deallocate(data, new_cap);
				throw ;
			}
			for (i = 0; i < _size; ++i)
				_alloc.destroy(_data + i);
			_alloc.deallocate(_data, _capacity);
			_data = data;
			_capacity = new_cap;
		}
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::size_type	vector<T, Allocator>::capacity() const
	{
		return _capacity;
	}

	// Modifiers
	template<class T, class Allocator>
	void vector<T, Allocator>::clear()
	{
		for (size_type i = 0; i < _size; ++i)
			_alloc.destroy(_data + i);
		_size = 0;
	}

	template<class T, class Allocator>
	class vector<T, Allocator>::iterator : public ft::iterator<std::random_access_iterator_tag, T>
	{
		private:
			T	* _ptr;

		public:
			typedef T * iterator_type;

			iterator() {}

			iterator(T * ptr) : _ptr(ptr) {}

			iterator(const iterator & other) : _ptr(other._ptr) {}

			T *	base() const
			{
				return _ptr;
			}

			iterator &	operator=(const iterator & other)
			{
				_ptr = other._ptr;
				return *this;
			}

			T &	operator*()
			{
				return *_ptr;
			}

			T *	operator->()
			{
				return _ptr;
			}

			iterator &	operator++()
			{
				_ptr++;
				return *this;
			}

			iterator	operator++(int)
			{
				iterator tmp(*this);
				++(*this);
				return tmp;
			}

			iterator &	operator--()
			{
				_ptr--;
				return *this;
			}

			iterator	operator--(int)
			{
				iterator tmp(*this);
				--(*this);
				return tmp;
			}

			iterator &	operator+=(difference_type n)
			{
				_ptr += n;
				return *this;
			}

			iterator &	operator-=(difference_type n)
			{
				_ptr -= n;
				return *this;
			}

			iterator	operator+(difference_type n) const
			{
				iterator	tmp(*this);;
				tmp += n;
				return tmp;
			}

			iterator	operator-(difference_type n) const
			{
				iterator	tmp(*this);
				tmp -= n;
				return tmp;
			}

			difference_type	operator-(iterator other) const
			{
				return _ptr - other._ptr;
			}

			T &		operator[](difference_type n)
			{
				return *(_ptr + n);
			}

			operator vector<T, Allocator>::const_iterator() const
			{
				return vector<T, Allocator>::const_iterator(_ptr);
			}
			
			friend bool operator==(typename vector<T, Allocator>::iterator lhs,
				typename  vector<T, Allocator>::iterator rhs)
			{
				return lhs.base() == rhs.base();
			}

			friend bool operator<=(typename vector<T, Allocator>::iterator lhs,
				typename  vector<T, Allocator>::iterator rhs)
			{
				return lhs.base()<= rhs.base();
			}

			friend bool operator>=(typename vector<T, Allocator>::iterator lhs,
				typename  vector<T, Allocator>::iterator rhs)
			{
				return lhs.base() >= rhs.base();
			}

			friend bool operator!=(typename vector<T, Allocator>::iterator lhs,
				typename  vector<T, Allocator>::iterator rhs)
			{
				return lhs.base() != rhs.base();
			}

			friend bool operator<(typename vector<T, Allocator>::iterator lhs,
				typename  vector<T, Allocator>::iterator rhs)
			{
				return lhs.base()< rhs.base();
			}

			friend bool operator>(typename vector<T, Allocator>::iterator lhs,
				typename  vector<T, Allocator>::iterator rhs)
			{
				return lhs.base() > rhs.base();
			}
	};

	template<class T, class Allocator>
	class vector<T, Allocator>::const_iterator : 
		public ft::iterator<std::random_access_iterator_tag, T, std::ptrdiff_t, const T*, const T&>
	{
		private:
			const T	* _ptr;

		public:
			typedef const T * iterator_type;

			const_iterator() {}

			const_iterator(const T * ptr) : _ptr(ptr) {}

			const_iterator(const const_iterator & other) : _ptr(other._ptr) {}

			const T *	base() const
			{
				return _ptr;
			}

			const_iterator &	operator=(const const_iterator & other)
			{
				_ptr = other._ptr;
				return *this;
			}

			const T &	operator*() const
			{
				return *_ptr;
			}

			const T *	operator->() const
			{
				return _ptr;
			}

			const_iterator &	operator++()
			{
				_ptr++;
				return *this;
			}

			const_iterator	operator++(int)
			{
				const_iterator tmp(*this);
				++(*this);
				return tmp;
			}

			const_iterator &	operator--()
			{
				_ptr--;
				return *this;
			}

			const_iterator	operator--(int)
			{
				const_iterator tmp(*this);
				--(*this);
				return tmp;
			}

			const_iterator &	operator+=(difference_type n)
			{
				_ptr += n;
				return *this;
			}

			const_iterator &	operator-=(difference_type n)
			{
				_ptr -= n;
				return *this;
			}

			const_iterator	operator+(difference_type n) const
			{
				const_iterator	tmp(*this);
				tmp += n;
				return tmp;
			}

			const_iterator	operator-(difference_type n) const
			{
				const_iterator	tmp(*this);
				tmp -= n;
				return tmp;
			}

			difference_type	operator-(const_iterator other) const
			{
				return _ptr - other._ptr;
			}

			const T &		operator[](difference_type n)
			{
				return *(_ptr + n);
			}
			
			friend bool operator==(typename vector<T, Allocator>::const_iterator lhs,
				typename  vector<T, Allocator>::const_iterator rhs)
			{
				return lhs.base() == rhs.base();
			}

			friend bool operator<=(typename vector<T, Allocator>::const_iterator lhs,
				typename  vector<T, Allocator>::const_iterator rhs)
			{
				return lhs.base()<= rhs.base();
			}

			friend bool operator>=(typename vector<T, Allocator>::const_iterator lhs,
				typename  vector<T, Allocator>::const_iterator rhs)
			{
				return lhs.base() >= rhs.base();
			}

			friend bool operator!=(typename vector<T, Allocator>::const_iterator lhs,
				typename  vector<T, Allocator>::const_iterator rhs)
			{
				return lhs.base() != rhs.base();
			}

			friend bool operator<(typename vector<T, Allocator>::const_iterator lhs,
				typename  vector<T, Allocator>::const_iterator rhs)
			{
				return lhs.base()< rhs.base();
			}

			friend bool operator>(typename vector<T, Allocator>::const_iterator lhs,
				typename  vector<T, Allocator>::const_iterator rhs)
			{
				return lhs.base() > rhs.base();
			}
	};

	template<class T, class Allocator>
	template<class InputIt>
	void	vector<T, Allocator>::insert(typename vector<T, Allocator>::iterator pos,
		typename enable_if<is_iterator<InputIt>::value, InputIt>::type first, InputIt last)
	{
		size_type count = 0;
		InputIt it_tmp = first;
		while (it_tmp++ != last)
			++count;
		size_type i;
		size_type pos_relative = pos - begin();
		if (_size + count > _capacity)
		{
			size_type	capacity_n = (_capacity * 2 > _size + count) ? 2 * _capacity : _size + count;
			T * data = _alloc.allocate(capacity_n);
			try 
			{
				for (i = 0; i < pos_relative; ++i)
					_alloc.construct(data + i, _data[i]);
				for (; i < pos_relative + count; ++i, ++first)
					_alloc.construct(data + i, *first);
				for (; i < _size + count; ++i)
					_alloc.construct(data + i, _data[i - count]);
			}
			catch (...)
			{
				for ( ; i > 0; --i)
					_alloc.destroy(data + i - 1);
				_alloc.deallocate(data, capacity_n);
				throw ;
			}

			for (i = 0; i < _size; ++i)
				_alloc.destroy(_data + i);
			_alloc.deallocate(_data, _capacity);
			_capacity = capacity_n;
			_size += count;
			_data = data;
			return ;
		}
		if (_size != 0)
		{
			for (i = _size - 1; i >= pos_relative; --i)
			{
				_alloc.construct(_data + i + count, *(_data + i));
				_alloc.destroy(_data + i);
			}
		}
		for (i = 0; i < count; ++i)
			_alloc.construct(_data + pos_relative + i, *(first + i));
		_size += count;
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::iterator	vector<T, Allocator>::insert
		(typename vector<T, Allocator>::iterator pos, const T& value)
	{	
		size_type pos_relative = pos - begin();
		size_type i;
		if (_size == _capacity)
		{
			size_type	capacity_n = _size != 0 ? 2 * _size : 1;
			T * data = _alloc.allocate(capacity_n);
				try {
				for (i = 0; i< pos_relative; ++i)
					_alloc.construct(data + pos_relative, *(_data + i));
				for (i = pos_relative; i< _size; ++i)
					_alloc.construct(data + i + 1, *(_data + i));
				_alloc.construct(data + pos_relative, value);
			} catch (...) {
				for (; i > 0; --i)
					_alloc.destroy(data + i - 1);
				_alloc.deallocate(data, capacity_n);
				throw ;
			}
			for (i = 0; i< _size; ++i)
				_alloc.destroy(_data + i);
			_alloc.deallocate(_data, _capacity);
			_data = data;
			_capacity = capacity_n;
			_size++;
			return begin() + pos_relative;
		}
		if (_size != 0)
		{
			_alloc.construct(_data + _size, _data[_size - 1]);
			for (i = _size - 1; i > pos_relative; --i)
			{
				_alloc.destroy(_data + i);
				_alloc.construct(_data + i, _data[i - 1]);
			}
		}
		_alloc.destroy(_data + pos_relative);
		_alloc.construct(_data + pos_relative, value);
		_size++;
		return begin() + pos_relative;
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::insert( typename vector<T, Allocator>::iterator pos,
		size_type count, const T& value )
	{
		size_type pos_relative = pos - begin();
		size_type i;
		if (_size + count > _capacity)
		{
			size_type	capacity_n = 2 * _capacity > (_size + count) ? 2 * _capacity : _size + count;
			T * data = _alloc.allocate(capacity_n);
			try {
				for (i = 0; i< pos_relative; ++i)
					_alloc.construct(data + i, *(_data + i));
				for (; i< pos_relative + count; ++i)
					_alloc.construct(data + i, value);
				for (; i< _size + count; ++i)
					_alloc.construct(data + i, *(_data + i - count));
			} catch (...) {
				for (; i > 0; --i)
					_alloc.destroy(data + i - 1);
				_alloc.deallocate(data, capacity_n);
				throw ;
			}
			for (i = 0; i< _size; ++i)
				_alloc.destroy(_data + i);
			_alloc.deallocate(_data, _capacity);
			_capacity = capacity_n;
			_size += count;
			_data = data;
			return ;
		}
		if (_size != 0)
		{
			for (i = _size - 1; i >= pos_relative; --i)
			{
				_alloc.construct(_data + i + count, *(_data + i));
				_alloc.destroy(_data + i);
			}
		}
		for (i = 0; i< count; ++i)
			_alloc.construct(_data + pos_relative + i, value);
		_size += count;
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::erase
		(typename vector<T, Allocator>::iterator pos)
	{
		if (pos + 1 != end())
		{
			size_type pos_relative = pos - begin();
			for (size_type i = pos_relative; i < _size - 1; ++i)
				_data[i] = _data[i + 1];
		}
		_size--;
		_alloc.destroy(_data + _size - 1);
		return pos;
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::erase
		(typename vector<T, Allocator>::iterator first, typename vector<T, Allocator>::iterator last)
	{
		size_type i;
		size_type pos_relative_first = first - begin();
		size_type pos_relative_last = last - begin();
		size_type pos_dist = last - first;
		for (i = 0; i < pos_dist; ++i)
			_alloc.destroy(_data + pos_relative_first + i);
		for (i = pos_relative_last; i < _size; ++i)
		{
			_alloc.construct(_data + i - pos_dist, _data[i]);
			_alloc.destroy(_data + i);
		}
		_size -= (last - first);
		return first;
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::push_back( const T& value )
	{
		if (_size == _capacity)
		{
			size_type	capacity_n = _size != 0 ? 2 * _size : 1;
			T * data = _alloc.allocate(capacity_n);
			size_type	i;
			try {
				for (i = 0; i < _size; ++i)
					_alloc.construct(data + i, _data[i]);
			} catch ( ... ) {
				for (; i > 0; --i)
					_alloc.destroy(data + i - 1);
				_alloc.deallocate(data, capacity_n);
				throw ;
			}
			for (i = 0; i < _size; ++i)
				_alloc.destroy(_data + i);
			_alloc.deallocate(_data, _capacity);
			_capacity = capacity_n;
			_data = data;
		}
		_alloc.construct(_data + _size, value);
		_size++;
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::pop_back()
	{
		_alloc.destroy(_data + _size);
		_size--;
	}

	template<class T, class Allocator>
	void	vector<T, Allocator>::resize(size_type count, T value)
	{
		size_type	i;
		if (count < _size)
		{
			for (i = count; i < _size; ++i)
				_alloc.destroy(_data + i);
		}
		if (count > _size)
		{
			for (i = _size; i < count; ++i)
				this->push_back(value);
		}
		_size = count;
	}

	template<class T, class Allocator>
	void	vector<T, Allocator>::swap( vector& other )
	{
		std::swap(_data, other._data);
		std::swap(_capacity, other._capacity);
		std::swap(_size, other._size);
	}

	template<class T, class Allocator>
	T*	vector<T, Allocator>::data()
	{
		return _data;
	}

	template<class T, class Allocator>
	const T*	vector<T, Allocator>::data() const
	{
		return _data;
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::allocator_type vector<T, Allocator>::get_allocator() const
	{
		return _alloc;
	}

	// Non-member functions https://en.cppreference.com/w/cpp/container/vector
	template<class T, class Allocator>
	bool operator==(const vector<T, Allocator> & lhs, const vector<T, Allocator> & rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		for (size_t i = 0; i < lhs.size(); ++i)
		{
			if (lhs[i] != rhs[i])
				return false;
		}
		return true;
	}

	template<class T, class Allocator>
	bool operator!=(const vector<T, Allocator> & lhs, const vector<T, Allocator> & rhs)
	{
		return !(lhs == rhs);
	}

	template<class T, class Allocator>
	bool operator<(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{
		return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template<class T, class Allocator>
	bool operator<=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{
		return (!(rhs < lhs));
	}

	template<class T, class Allocator>
	bool operator>(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{
		return (rhs < lhs);
	}

	template<class T, class Allocator>
	bool operator>=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{
		return (!(lhs < rhs));
	}

} // namespace ft

namespace std
{
	template<class T, class Allocator>
	void swap(ft::vector<T, Allocator> & lhs, ft::vector<T, Allocator> & rhs)
	{
		lhs.swap(rhs);
	}
}

#endif
