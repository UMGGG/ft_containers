/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   container_utils.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:46:01 by jaeyjeon          #+#    #+#             */
/*   Updated: 2023/03/07 18:27:57 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINER_UTILS_HPP
# define CONTAINER_UTILS_HPP

# include <memory>
# include <limits>

template<bool B, class T = void>
struct enable_if
{};

template<class T>
struct enable_if<true, T>
{
	typedef T type;
};

template <typename T>
struct is_integral
{
	static const bool value = false;
};

template <> // 템플릿 전문화로 특정 상황에서 다르게 작동하려할 때 사용
struct is_integral<bool>
{
	static const bool value = true;
};

template <>
struct is_integral<char>
{
	static const bool value = true;
};

template <>
struct is_integral<unsigned char>
{
	static const bool value = true;
};

template <>
struct is_integral<signed char>
{
	static const bool value = true;
};

template <>
struct is_integral<wchar_t>
{
	static const bool value = true;
};

template <>
struct is_integral<short>
{
	static const bool value = true;
};

template <>
struct is_integral<unsigned short>
{
	static const bool value = true;
};

template <>
struct is_integral<int>
{
	static const bool value = true;
};

template <>
struct is_integral<unsigned int>
{
	static const bool value = true;
};

template <>
struct is_integral<long>
{
	static const bool value = true;
};

template <>
struct is_integral<unsigned long>
{
	static const bool value = true;
};

template <>
struct is_integral<long long>
{
	static const bool value = true;
};

template <>
struct is_integral<unsigned long long>
{
	static const bool value = true;
};

#endif
