/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:46:37 by jaeyjeon          #+#    #+#             */
/*   Updated: 2023/02/16 22:13:07 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory> // allocator

namespace ft
{
	template < class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
		typedef	T				value_t; // T를 value_type으로 사용
		typedef	Allocator		allocator_t; // Alloc를 allocator_type으로 사용
		typedef std::size_t		size_type;

		typedef typename	allocator_t::reference			reference;
		typedef typename	allocator_t::const_reference	const_reference;
		typedef typename	allocator_t::pointer			pointer;
		typedef typename	allocator_t::const_pointer		const_pointer;

		explicit vector(const allocator_t& alloc = allocator_t()) // default 생성자
		{
			container_ = NULL;
			alloc_ = alloc;
			size_ = 0;
			capacity_ = 0;
		};

		explicit vector(size_type count, const value_t& value = value_t(), const allocator_t& alloc = allocator_t()) // value_t타입을 count개만큼 만들어주는 생성자
		{
			container_ = NULL;
			alloc_ = alloc;
			size_ = 0;
			capacity_ = 0;
			insert(begin(), count, value)
		};

		template<class input_iter>
		vector(input_iter first, input_iter last, const allocator_t& alloc = allocator_t())
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
			//전부 삭제해주는 함수 clear()
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

		void resize(size_type n, value_t val = value_type())
		{
			if (n > capacity_)
			{
				if (capacity_ == 0)
					reserve(n);
				else
				{
					if ()
				}
			}
			while (size_ < n)
				push_back(val);
			while (size_ > n)
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

		private:
		value_t			*container_; // 저장공간의 타입
		allocator_t		alloc_; // 저장공간
		size_type		size_; // 벡터가 가지고있는 요소의 개수
		size_type		capacity_; // 요소의 수로 표현된 벡터에 현재 할당되어있는 저장공간의 크기
	};

}

#endif
