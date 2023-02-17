/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <jaeyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:46:37 by jaeyjeon          #+#    #+#             */
/*   Updated: 2023/02/17 18:57:10 by jaeyjeon         ###   ########.fr       */
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
		typedef	Alloc			allocator_type; // Alloc를 allocator_type으로 사용
		typedef std::size_t		size_type;

		typedef typename	allocator_type::reference			reference;
		typedef typename	allocator_type::const_reference	const_reference;
		typedef typename	allocator_type::pointer			pointer;
		typedef typename	allocator_type::const_pointer		const_pointer;

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

		template<class input_iter>
		vector(input_iter first, input_iter last, const allocator_type& alloc = allocator_type())
		{
			container_ = NULL;
			alloc_ = alloc;
			size_ = 0;
			capacity_ = 0;
			// fisrt ~ last까지 값 insert 해주기
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

		T* data(); // C++11??
		const T* data() const;// C++11??


		private:
		value_type			*container_; // 저장공간의 타입
		allocator_type		alloc_; // 저장공간
		size_type			size_; // 벡터가 가지고있는 요소의 개수
		size_type			capacity_; // 벡터에 현재 할당되어있는 저장공간의 크기
	};

}

#endif
