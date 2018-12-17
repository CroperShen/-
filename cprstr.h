//=====================================================================
//croperstr.h
//Created by Croper
//last modifierd in Dec.17.2018;
//解决windows那蛋疼又臭又长又不好用的TCHAR问题，目标是代替TCHAR[]的所有功能
//===============================================================

#pragma once
#define _CRPRSTR_

#include <iostream>
#include <strstream>
#include "linkedlist.h"

int cprstr_segmentlength = 128;

class cprstr
{
friend std::ostream & operator<<(std::ostream& os, cprstr s);
friend cprstr operator+(std::ostream& os, cprstr s);

private:
	linkedlist<wchar_t*> list;
public:
	cprstr();
	cprstr(const wchar_t*);
	cprstr(long i);
	cprstr(int i);
	cprstr(float r);
	cprstr(double r);
	cprstr(bool b);

	operator wchar_t*() const;
	operator char*() const;
	wchar_t& operator[](int);
	const wchar_t& operator[](int) const;
	int size() const;
};

cprstr::cprstr()
{}

cprstr::cprstr(const wchar_t* str1)
{
	int i=0;
	int j;
	do
	{
		j = i / cprstr_segmentlength;
		if (i + 1 > list.size()*cprstr_segmentlength)
		{
			list.Append();
			list[j] = new wchar_t[cprstr_segmentlength];
		}
		this[i] = str1[i];
	}while (str1[i] != (char)0);
}

wchar_t& cprstr::operator[](int i)
{
	if (i + 1 > list.size()*cprstr_segmentlength) throw "下标超限";
	int j = i / cprstr_segmentlength;
	i=i% cprstr_segmentlength;
	return list[j][i];
}

const wchar_t& cprstr::operator[](int i) const
{
	return const_cast<cprstr*>(this)->operator[](i);
}

cprstr::operator wchar_t*() const
{
	static wchar_t *p;
	int l = size();
	p = new wchar_t[l];
	for (int i = 0; i <= l; i++) p[i] = (*this)[i];
	return p;
}
cprstr::operator char*() const
{
	static char *p;
	int l = size();
	p = new char[l];
	for (int i = 0; i <= l; i++) p[i] = (*this)[i];
	return p;
}

int cprstr::size() const
{
	int i;
	for (i = 0; i < list.size()*cprstr_segmentlength; i++)
	{
		if ((*this)[i] == (char)'0') break;
	}
	return i;
}

#ifdef _OSTREAM_
std::ostream & operator<<(std::ostream& os, cprstr sz);
#endif
