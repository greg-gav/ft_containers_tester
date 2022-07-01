#ifndef vector_hpp
#define vector_hpp
#include <memory>
#include "utils.hpp"
#include "iterator.hpp"

namespace ft
{
	template<typename T, typename A = std::allocator<T> >
	class vector
	{
	public:
		typedef A										allocator_type;
		typedef typename A::pointer						pointer;
		typedef typename A::const_pointer				const_pointer;
		typedef typename A::reference					reference;
		typedef typename A::const_reference				const_reference;
		typedef typename A::value_type					value_type;
		typedef std::size_t								size_type;
		typedef std::ptrdiff_t							difference_type;
		typedef	Iterator<pointer>						iterator;
		typedef	Iterator<const_pointer>					const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		
		explicit vector(const allocator_type& alloc = allocator_type())
		:_alloc(alloc),
		_size(0),
		_capacity(0),
		_data(_alloc.allocate(0)) {}
			
		explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
		:_alloc(alloc),
		_size(n),
		_capacity(n),
		_data(_alloc.allocate(n))
		{
			for (size_type i = 0 ; i < n ; ++i)
				_alloc.construct(_data + i, val);
		}

		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
		typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
		{
			size_type		n = 0;
			for (InputIterator it = first ; it != last && n <= max_size() ; ++it)
				++n;

			_alloc = alloc;
			_size = n;
			_capacity = n;
			_data = _alloc.allocate(n);

			for (size_type i = 0 ; i < n ; ++i)
				_alloc.construct(_data + i, *first++);
		}

		vector(const vector& x)
		{
			_alloc = x._alloc;
			_size = x._size;
			_capacity = x._capacity;
			_data = _alloc.allocate(_capacity);

			for (size_type i = 0 ; i < _size ; ++i)
				_alloc.construct(_data + i, x[i]);
		}

		~vector()
		{
			for (size_type i = 0 ; i < _size ; ++i)
				_alloc.destroy(_data + i);
			_alloc.deallocate(_data, _capacity);
		}


		vector& operator=(const vector& x)
		{
			if (this == &x)
				return *this;

			for (size_type i = 0 ; i < _size ; ++i)
				_alloc.destroy(_data + i);

			if (x._size > _capacity)
			{
				_alloc.deallocate(_data, _capacity);
				_capacity = x._size;
				_data = _alloc.allocate(_capacity);
			}

			_size = x._size;
			for (size_type i = 0 ; i < _size ; ++i)
				_alloc.construct(_data + i, x[i]);

			return *this;
		}

		/* Iterators */

		iterator				begin()				{ return iterator(_data);						}
		const_iterator			begin() const		{ return const_iterator(_data);					}
		iterator				end()				{ return iterator(_data + _size);				}
		const_iterator			end() const			{ return const_iterator(_data + _size);			}
		reverse_iterator 		rbegin()			{ return reverse_iterator(_data + _size);		}
		const_reverse_iterator	rbegin() const		{ return const_reverse_iterator(_data + _size); }
		reverse_iterator		rend() 				{ return reverse_iterator(_data);				}
		const_reverse_iterator	rend() const		{ return const_reverse_iterator(_data);			}

		/* Capacity */

		size_type				size() const		{ return _size;									}
		size_type				max_size() const	{ return _alloc.max_size();						}
		size_type				capacity() const	{ return _capacity; 							}
		bool					empty() const		{ return (_size == 0);							}

		void resize(size_type n, value_type val = value_type())
		{
			if (n > _size)
			{
				if (n > _capacity)
				{
					if (n > _capacity * 2)
						reserve(n);
					else if (_capacity > 0)
						reserve(_capacity * 2);
					else
						reserve(1);
				}

				for (size_type i = _size ; i < n ; i++)
					_alloc.construct(_data + i, val);
			}
			else
			{
				for (size_type i = n ; i < _size ; ++i)
					_alloc.destroy(_data + i);
			}
			_size = n;
		}

		void reserve(size_type n)
		{
			if (n > _alloc.max_size())
				throw std::length_error("vector");

			if (n > _capacity) {
				T*		new_data = _alloc.allocate(n);
				
				for (size_type i = 0 ; i < _size ; ++i)	{
					_alloc.construct(new_data + i, _data[i]);
					_alloc.destroy(_data + i);
				}
				_alloc.deallocate(_data, _capacity);
				_capacity = n;
				_data = new_data;
			}
		}

		/* Element access */

		reference		operator[](size_type n)			{ return *(_data + n); }
		const_reference	operator[](size_type n) const	{ return *(_data + n); }
		reference 		at(size_type n)					{ if (n >= _size) throw std::out_of_range("vector"); return _data[n]; }
		const_reference at(size_type n) const			{ if (n >= _size) throw std::out_of_range("vector"); return _data[n]; }
		reference		front()							{ return _data[0]; }
		const_reference front() const					{ return _data[0]; }
		reference		back()							{ return _data[_size - 1]; }
		const_reference back() const					{ return _data[_size - 1]; }


		template <class InputIterator>
		void assign(InputIterator first, InputIterator last,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
		{
			size_type		n = last - first;
			
			if (n > _capacity)
				reserve(n);
			for (size_type i = 0 ; i < _size ; ++i)
				_alloc.destroy(_data + i);
			for (size_type i = 0 ; i < n ; i++)
				_alloc.construct(_data + i, *first++);
			_size = n;
		}

		void assign(size_type n, const value_type& val)
		{
			if (n > _capacity)
				reserve(n);
			for (size_type i = 0 ; i < _size ; ++i)
				_alloc.destroy(_data + i);
			for (size_type i = 0 ; i < n ; ++i)
				_alloc.construct(_data + i, val);
			_size = n;
		}

		iterator insert(iterator position, const value_type& val)
		{
			size_type		off = position - begin();
			insert(position, 1, val);
			return (iterator(_data + off));
		}

		void insert(iterator position, size_type n, const value_type& val)
		{
			size_type		off = position - begin();

			if (_size + n > _capacity) {
				if (_size + n > _capacity * 2)
					reserve(_size + n);
				else if (_capacity > 0)
					reserve(_capacity * 2);
				else
					reserve(1);
			}
			if (n != 0) {
				if (_size != 0)
					for (long i = (long)_size - 1 ; i >= (long)off ; --i) {
						_alloc.construct(_data + i + n, _data[i]);
					}
				for (size_type i = off ; i < n + off ; ++i) {
					_alloc.destroy(_data + i);
					_alloc.construct(_data + i, val);
				}
			}
			_size += n;
		}

		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
		{
			size_type		off = position - begin();
			size_type		n = 0;

			if (typeid(typename iterator::value_type) != typeid(typename InputIterator::value_type)) {
				throw std::runtime_error("different types");
			}
			
			for (InputIterator it = first ; it != last && n <= max_size() ; ++it)
				++n;
			if (_size + n > _capacity) {
				if (_size + n > _capacity * 2)
					reserve(_size + n);
				else if (_capacity > 0)
					reserve(_capacity * 2);
				else
					reserve(1);
			}
            if (n != 0) {
                if (_size != 0) {
                    for (long i = (long) _size - 1; i >= (long) off; --i) {
                        if (i + n < _size)
                            _alloc.destroy(_data + i + n);
                        _alloc.construct(_data + i + n, _data[i]);
						_alloc.destroy(_data + i);
                    }
                }
                for (size_type i = off; i < off + n; ++i) {
                    _alloc.construct(_data + i, *first++);
                }
                _size += n;
            }
		}

		iterator erase(iterator position)
		{
			iterator ret(position);
			
			for (size_type i = position - begin() ; i < _size - 1 ; ++i)
				_data[i] = _data[i + 1];
			_alloc.destroy(_data + --_size);
			return ret;
		}

		iterator erase(iterator first, iterator last)
		{
			iterator e(last);
			for (iterator it = first; it < end(); ++it) {
				if (e < end()) {
					pointer p = (it.getPtr());
					_alloc.destroy(p);
					_alloc.construct(p, *e);
					_alloc.destroy(e.getPtr());
					++e;
				} else {
					_alloc.destroy(it.getPtr());
				}
			}
			_size -= last - first;
			return first;
		}

		void push_back(const value_type& val)
		{
			if (_size + 1 > _capacity)
			{
				if (_capacity > 0)
					reserve(_capacity * 2);
				else
					reserve(1);
			}

			_alloc.construct(_data + _size++, val);
		}

		void pop_back(void)
		{
			if (_size)
				_alloc.destroy(_data + _size-- - 1);
		}

		void swap(vector& x)
		{
			ft::swap(_data, x._data);
			ft::swap(_size, x._size);
			ft::swap(_capacity, x._capacity);
		}

		void clear(void)
		{
			for (size_type i = 0 ; i < _size ; i++)
				_alloc.destroy(_data + i);
			_size = 0;
		}

		allocator_type get_allocator(void) const
		{
			return (allocator_type());
		}

		private:
			allocator_type		_alloc;
			size_type			_size;
			size_type			_capacity;
			pointer				_data;
	};


	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc> & lhs, const vector<T,Alloc> & rhs)
	{
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (!(lhs == rhs)); }

	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (!(rhs < lhs)); }

	template <class T, class Alloc>
	bool operator> (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (rhs < lhs); }

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (!(lhs < rhs)); }

	template <class T, class Alloc>
	void swap(vector<T,Alloc>& x, vector<T,Alloc>& y) { x.swap(y); }
}

namespace std {
	template <class T, class Alloc>
	void swap(ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y) { x.swap(y); }
}

#endif
