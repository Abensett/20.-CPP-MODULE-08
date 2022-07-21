/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 16:25:41 by abensett          #+#    #+#             */
/*   Updated: 2022/07/21 15:54:03 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Span.hpp"

/*
**		CANNONICAL FORM
*/

Span::Span(void) : _N(0), _stored(0)
{
	return ;
}

Span::Span(const unsigned int N) : _N(N), _stored(0)
{
	return ;
}

Span::Span(const Span &span)
{
	*this = span;
}

Span::~Span()
{
	_data.clear();
}

/*
**		OVERLOAD OPERATORS
*/

Span	&Span::operator=(const Span &span)
{
	if (this != &span)
	{
		this->_data.clear();
		this->_N = span._N;
		this->_stored = span._stored;
		this->_data = span._data;
	}
	return (*this);
}

std::ostream	&operator<<(std::ostream &o, const Span &span)
{
	span.printData(o);
	return (o);
};

/*
**		MEMBER FUNCTIONS
*/

void	Span::addNumber(const int n)
{
	if (_stored >= _N)
		throw Span::AlreadyFull();
	_data.push_back(n);
	_stored++;
}

int		Span::longestSpan(void) const
{
	if (_stored <= 1)
		throw Span::NotFilledEnough();

	vectIt	minIt = std::min_element(_data.begin(), _data.end());
	vectIt	maxIt = std::max_element(_data.begin(), _data.end());

	return (*maxIt - *minIt);
}

int		Span::shortestSpan(void) const
{
	std::vector<int>	copy = _data;
	long				minSpan = std::numeric_limits<long>::max();

	if (_stored <= 1)
		throw Span::notEnoughNumbers();
	
	sort(copy.begin(), copy.end());
	for (size_t i = 0; i + 1 < _data.size(); i++)
		minSpan = std::min(minSpan, static_cast<long>(copy[i + 1] - copy[i]));
	return (minSpan);
}

void	Span::printData(std::ostream &o, const unsigned int max) const
{
	o << "[ ";
	for (unsigned int i = 0; i < max && i < _stored; i++)
		o << _data[i] << " ";
	if (_stored > max)
		o << "... " << _data[_stored - 1] << " ";
	o << "] (" << _stored << "/" << _N << ")";
}