/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:46:37 by jaeyjeon          #+#    #+#             */
/*   Updated: 2023/03/06 16:59:20 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory> // allocator

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
		typedef	T				value_type; // T를 value_type으로 사용
		typedef	Alloc			allocator_type; // Alloc를 allocator_type으로 사용, 저장공간을 할당하거나 할당 취소해주는 객체
		typedef std::size_t		size_type;

		typedef typename	allocator_type::reference		reference;
		typedef typename	allocator_type::const_reference	const_reference;
		typedef typename	allocator_type::pointer			pointer;
		typedef typename	allocator_type::const_pointer	const_pointer;

		typedef ft::random_access_iterator<value_type>			iterator;
		typedef ft::random_access_iterator<const value_type>	const_iterator;
		typedef ft::reverse_iterator<iterator>					reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

		explicit vector(const allocator_type& alloc = allocator_type()) // default 생성자
		{
			container_ = NULL;
			alloc_ = alloc;
			size_ = 0;
			capacity_ = 0;
		};

		explicit vector(size_type count, const value_type& value = value_type(), const allocator_type& alloc = allocator_type()) // value_t타입을 count개만큼 만들어주는 생성자
		{
			container_ = NULL;
			alloc_ = alloc;
			size_ = 0;
			capacity_ = 0;
			insert(begin(), count, value)
		};

		template<class InputIt>
		vector(InputIt first, InputIt last, const allocator_type& alloc = allocator_type(),
		 typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0)
		{
			container_ = NULL;
			alloc_ = alloc;
			size_ = 0;
			capacity_ = 0;
			insert(begin(), first, last);
		};

		vector (const vector &other) //복사생성자
		{
			container_ = NULL;
			alloc_ = other.alloc_;
			size_ = 0;
			capacity_ = 0;
			assign(other.begin(), other.end());
		};

		vector& operator= (const vector &other) //대입연산자
		{
			if (&other == NULL)
				return (*this);
			assign(other.begin(), other.end());
			return (*this);
		};

		~vector()
		{
			clear();
			alloc_.deallocate(container_, capacity_);
		};

		size_type size() const
		{
			return (size_);
		};

		size_type max_size() const
		{
			return (alloc_.max_size());
		};

		void resize(size_type n, value_type val = value_type())
		{
			if (n > max_size())
				throw (std::length_error("vector::resize"));
			else if (n > capacity())
				reserve(n);
			while (size() < n)
				push_back(val);
			while (size() > n)
				pop_back();
		}

		size_type capacity() const
		{
			return (capacity_);
		}

		bool empty() const
		{
			return (size_ == 0);
		}

		void reserve (size_type n)
		{
			if (n > max_size())
				throw (std::length_error("vector::reserve"));
			else if (n > capacity())
			{
				value_type *new_alloc;
				new_alloc = alloc_.allocate(n);
				for (size_type i = 0 ; i < size() ; i++)
				{
					alloc_.construct(new_alloc + i, container_[i]);
					alloc_.destroy(container[i]);
				}
				alloc_.deallocate(container_, capacity_);
				capacity_ = n;
				container_ = new_alloc;
			}
		}

		reference operator[] (size_type n)
		{
			return (*(container_ + n));
		}

		const_reference operator[] (size_type n) const
		{
			return (*(container_ + n));
		}

		reference at(size_type pos)
		{
			if (n > size())
				throw (std::out_of_range("vector"));
			return (container_[n]);
		}

		const_reference at(size_type pos) const
		{
			if (n > size())
				throw (std::out_of_range("vector"));
			return (container_[n]);
		}

		reference front();
		{
			return (container_[0]);
		}

		const_reference front() const;
		{
			return (container_[0]);
		}

		reference back()
		{
			return (container_[size() - 1]);
		}

		const_reference back() const
		{
			return (container_[size() - 1]);
		}

		T* data()
		{
			return (container_);
		}
		const T* data() const
		{
			return (container_);
		}

		void clear()
		{
			while (size() > 0)
				pop_back();
		}

		iterator begin()
		{
			return (iterator(container_));
		}

		const_iterator begin() const
		{
			return (const_iterator(container_));
		}

		iterator end()
		{
			return (iterator(container_ + size()));
		}

		const_iterator end() const
		{
			return (const_iterator(container_ + size()));
		}

		reverse_iterator rbegin()
		{
			return (reverse_iterator(end()));
		}
		const_reverse_iterator rbegin() const
		{
			return (const_reverse_iterator(end()));
		}
		reverse_iterator rend()
		{
			return (reverse_iterator(begin()));
		}
		const_reverse_iterator rend() const
		{
			return (const_reverse_iterator(begin()));
		}

		template <class InputIt>
		void assign (InputIt first, InputIt last,
		typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0)
		{
			InputIt	size_check = first;
			int		size;
			clear();
			while (size_check != last)
			{
				size_check++;
				size++;
			}
			reserve(size);
			insert(begin(), first, last);
		}

		void assign (size_type n, const value_type& val)
		{
			clear();
			reserve(n);
			insert(begin(), n, val);
		}

		void push_back (const value_type& val)
		{
			if (capacity_ < size_ + 1)
			{
				if (capacity() == 0)
					reserve(1);
				else
					reserve(capacity_ * 2);
			}
			alloc_.construct(&container_[size_], val);
			size_++;
		}

		void pop_back()
		{
			if (size() != 0)
			{
				alloc_.destroy(&container_[size_ - 1]);
				size_--;
			}
		}

		iterator insert (iterator position, const value_type& val)
		{
			size_type	idx = position - begin();
			if (size_ + 1 > capacity_)
			{
				if (capacity_ == 0)
					reserve(1);
				else
					reserve(capacity_ * 2);
			}
			size_++;
			if (idx < size_)
			{
				for(size_type i = size_ - 1 ; i > idx ; i--)
				{
					alloc_.construct(&container_[i], container_[i - 1]);
					alloc_.destroy(&container_[i - 1]);
				}
			}
			alloc_.construct(&container_[idx], val);
			return (iterator(&container[idx]));
		}

		void insert (iterator position, size_type n, const value_type& val)
		{
			size_type	idx = position - begin();
			if (size_ + n > capacity_)
			{
				if (capacity_ == 0)
					reserve(n);
				else
				{
					if (size_ * 2 < size_ + n)
						reserve(capacity_ + n);
					else
						reserve(capacity_ * 2);
				}
			}
			for(size_type i = n + size_ - 1 ; i > n + idx - 1; i--)
			{
				alloc_.construct(&container_[i], container_[i - n]);
				alloc_.destroy(&container_[i - n]);
			}
			for(size_type i = idx ; i < idx + n ; i++)
			{
				alloc_.construct(&container_[i], val);
				size_++;
			}
		}

		template <class InputIt>
		void insert (iterator position, InputIt first, InputIt last,
		typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0)
		{
			size_type	idx = position - begin();
			size_type	n = 0;
			InputIt		tmp = first;
			while (tmp != last)
			{
				n++;
				tmp++;
			}
			if (size_ + n > capacity_)
			{
				if (capacity_ == 0)
					reserve(n);
				else
				{
					if (size_ * 2 < size_ + n)
						reserve(capacity_ + n);
					else
						reserve(capacity_ * 2);
				}
			}
			for(size_type i = n + size_ - 1 ; i > n + idx - 1; i--)
			{
				alloc_.construct(&container_[i], container_[i - n]);
				alloc_.destroy(&container_[i - n]);
			}
			for(size_type i = idx ; i < idx + n ; i++)
			{
				alloc_.construct(&container_[i], *first);
				first++;
				size_++;
			}
		}

		iterator erase (iterator position)
		{
			size_type	idx = position - begin();
			alloc_.destroy(&container_[0]);
			size_--;
			if (idx < size_)
			{
				for (size_type i = idx ; i < size_ ; i++)
				{
					alloc_.construct(&container_[i], container_[i + 1]);
					alloc_.destroy(container_[i + 1]);
				}
			}
			return (iterator(&container_[idx]));
		}

		iterator erase (iterator first, iterator last)
		{
			size_type	start = first - begin();
			size_type	erase_size = 0;
			if (fisrt == last)
				return (iterator(first));
			for (iterator iter = first ; iter != last ; iter++)
			{
				alloc_destroy(&(*iter));
				size_--;
				erase_size++;
			}
			if (start < size_)
			{
				for (size_type i = start ; i < size ; i++)
				{
					alloc_construct(&container_[i], container_[i + size]);
					alloc_destroy(&container[i + size]);
				}
			}
			return (iterator(container_[start]));
		}

		void swap(vector& other)
		{
			value_type *temp_con = other.container_;
			size_type temp_size = other.size_;
			size_type temp_capa = other.capacity_;

			other.container_ = container_;
			container_ = temp_con;

			other.size = size_;
			size_ = temp_size;

			other.capacity_ = capacity_;
			capacity_ = temp_capa;
		}

		allocator_type get_allocator() const
		{
			return (alloc_);
		}

		private:
		value_type			*container_; // 저장공간의 타입
		allocator_type		alloc_; // 저장공간
		size_type			size_; // 벡터가 가지고있는 요소의 개수
		size_type			capacity_; // 벡터에 현재 할당되어있는 저장공간의 크기
	};

	template< class T, class Alloc >
	bool operator==( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs )
	{
		if (lhs.size() != rhs.size())
			return (false);
		for (size_t i = 0 ; i < lhs.size() ; i++)
		{
			if (lhs[i] != rhs[i])
				return (false);
		}
		return (true);
	}

	template< class T, class Alloc >
	bool operator!=( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs )
	{
		if (lhs.size() != rhs.size())
			return (true);
		for (size_t i = 0 ; i < lhs.size() ; i++)
		{
			if (lhs[i] != rhs[i])
				return (true);
		}
		return (false);
	}

	template< class T, class Alloc >
	bool operator<( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs )
	{
		typename vector<T>::const_iterator	lhs_it = lhs.begin();
		typename vector<T>::const_iterator	rhs_it = rhs.begin();

		while(lhs_it != lhs.end() && rhs_it != rhs.end())
		{
			if (*lhs_it < *rhs_it)
				return (true);
			else if (*lhs_it > *rhs_it)
				return (false);
			lhs_it++;
			rhs_it++;
		}
		return (rhs_it != rhs.end());
	}

	template< class T, class Alloc >
	bool operator<=( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs )
	{
		return (!(rhs < lhs));
	}

	template< class T, class Alloc >
	bool operator>( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs )
	{
		return (rhs < lhs);
	}

	template< class T, class Alloc >
	bool operator>=( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs )
	{
		return (!(lhs < rhs));
	}

	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	}
}

#endif
