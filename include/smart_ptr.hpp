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
#include <list>
#ifdef nullptr
#	define NULLPTR nullptr
#else
#	define NULLPTR NULL
#endif

// template < typename T > class ShrdSmartPtr {
//   public:
// 	ShrdSmartPtr(T *ptr = NULLPTR) : data(ptr), others(0) {}
// 	ShrdSmartPtr(const ShrdSmartPtr &other) : data(other.get()) {
// 		other.others.push_back(this);
// 		this->others = other.getOthers();
// 		this->others.push_back(other);
// 	}
//
// 	ShrdSmartPtr &operator=(const ShrdSmartPtr< T * > other) {
// 		if (*this != other) {
// 			data = other.get();
// 			this->others = other.others;
// 		}
// 		return (*this);
// 	}
//
// 	~ShrdSmartPtr() {
// 		if (others.empty()) {
// 			delete data;
// 			return;
// 		}
// 		for (typename std::list< ShrdSmartPtr< T * > * >::iterator itl =
// 				 others.begin();
// 			 itl != others.end(); itl++)
// 			(*itl)->getOthers().remove(this);
// 		return;
// 	};
// 	T *get(void) const {
// 		return (data);
// 	};
// 	void set(T *t) {
// 		for (typename std::list< ShrdSmartPtr< T * > >::iterator itl =
// 				 others.begin();
// 			 itl != others.end(); itl++)
// 			itl.setData(t);
// 	};
// 	std::list< ShrdSmartPtr< T * > > getOthers(void) const {
// 		return (others);
// 	};
//
//   private:
// 	void setData(T *t) {
// 		data = t;
// 	};
//
// 	T								  *data;
// 	std::list< ShrdSmartPtr< T * > * > others;
// };
