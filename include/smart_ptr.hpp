/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_ptr.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:47:04 by bgoulard          #+#    #+#             */
/*   Updated: 2025/07/07 17:47:04 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>
#include <iostream>
#include <list>
#include <ostream>

#include "ansi.h"
#include <list>
#ifdef nullptr
#	define NULLPTR nullptr
#else
#	define NULLPTR NULL
#endif

#define LOG_COLOR REDHB

template < typename T > class ShrdSmartPtr {
  private:
	class data {
	  public:
		data(T *t) {
			ptr = t;
			strong_count = 1;
			weak_count = 0;
		}
		data &operator=(const data &other) {
			ptr = other.ptr;
			strong_count = other.strong_count;
			weak_count = other.weak_count;
		}
		~data() {
			delete ptr;
		}
		T	  *ptr;
		size_t strong_count;
		size_t weak_count;
	};

  public:
	ShrdSmartPtr(T *ptr = NULLPTR) {
		this->_data = NULLPTR;
		this->type_ptr = ShrdSmartPtr::NONE;
		if (ptr) {
			this->_data = new data(ptr);
			this->type_ptr = ShrdSmartPtr::STRONG;
		}
	}

	ShrdSmartPtr(const ShrdSmartPtr &other) {
		this->type_ptr = other.type_ptr;
		this->_data = other._data;
		if (this->_data) {
			if (this->type_ptr == ShrdSmartPtr::STRONG)
				this->_data->strong_count++;
			else
				this->_data->weak_count++;
		}
	}
	ShrdSmartPtr< T > &operator=(const ShrdSmartPtr< T > &other) {
		if (this != &other) {
			if (this->_data)
				delete _data;
			this->type_ptr = other.type_ptr;
			this->_data = other._data;
			if (this->_data) {
				if (this->type_ptr == ShrdSmartPtr::STRONG)
					this->_data->strong_count++;
				else
					this->_data->weak_count++;
			}
		}
		return (*this);
	}

	~ShrdSmartPtr() {
		if (this->type_ptr == NONE)
			return;
		if (this->type_ptr == ShrdSmartPtr::WEAK)
			this->_data->weak_count--;
		if (this->type_ptr == ShrdSmartPtr::STRONG)
			this->_data->strong_count--;
		if (!this->_data->strong_count && !this->_data->weak_count) {
			delete this->_data;
			this->_data = NULL;
		}
	}

	T *get(void) const {
		if (this->type_ptr == ShrdSmartPtr::NONE)
			throw std::runtime_error("no data in ShrdSmartPtr");
		if (this->_data)
			return (this->_data->ptr);
		return (NULLPTR);
	}

	void set(T *t) {
		if (this->_data)
			delete _data;
		this->_data = new data(t);
	}

  private:
	data *_data;
	enum ptr_strength { NONE, WEAK, STRONG } type_ptr;
};
