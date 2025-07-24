/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:24:07 by bgoulard          #+#    #+#             */
/*   Updated: 2025/07/17 12:24:07 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <iostream>
#include <list>
#include <ostream>
#include <string>

class composite {
  public:
	composite(std::string s, int i = 42) {
		_s = s;
		_i = i;
	}
	~composite() {
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}

	bool operator==(const composite &other) {
		return (other._i == this->_i && other._s == this->_s);
	}

	friend std::ostream &operator<<(std::ostream &os, const composite &c) {
		return (os << "s:'" << c._s << "' i:" << c._i << std::endl);
	}

  private:
	std::string _s;
	int			_i;
};

class holder {
  public:
	std::list< composite > ls;
};

int main() {
	std::list< composite >	tmp;
	std::list< composite > *l2 = &tmp;
	tmp.push_back(composite("test", 21));
	{
		holder	  h;
		composite a(composite("tata", 42));

		h.ls.push_back(a);
		l2 = &h.ls;
		std::for_each(h.ls.begin(), h.ls.end(),
					  [](composite &e) { std::cout << e << std::endl; });
		h.ls.push_back(composite("toto", 42));
		std::for_each(h.ls.begin(), h.ls.end(),
					  [](composite &e) { std::cout << e << std::endl; });
		h.ls.remove(a);
		std::for_each(h.ls.begin(), h.ls.end(),
					  [](composite &e) { std::cout << e << std::endl; });

		h.ls.push_back(composite("titi", 53));
		std::for_each(h.ls.begin(), h.ls.end(),
					  [](composite &e) { std::cout << e << std::endl; });
		std::cout << "h.ls + l2" << std::endl;
		std::cout << h.ls.front() << std::endl;
		std::cout << l2->front() << std::endl;
		std::cout << "h.ls" << std::endl;
		std::for_each(h.ls.begin(), h.ls.end(),
					  [](composite &e) { std::cout << e << std::endl; });
		std::cout << "l2" << std::endl;
		std::for_each(l2->begin(), l2->end(),
					  [](composite &e) { std::cout << e << std::endl; });
	}
	l2 = &tmp;
	std::cout << "l2" << std::endl;
	std::for_each(l2->begin(), l2->end(),
				  [](composite &e) { std::cout << e << std::endl; });

	return 0;
}
