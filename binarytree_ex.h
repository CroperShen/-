#pragma once
#define _BINARYTREE_EX_H
#include<iostream>
#include<Windows.h>
#include "binarytree.h"
#include "crect.h"

template <typename T> std::ostream & operator<<(std::ostream & os, BinaryTree<T> tree)
{
	os << "{";
	for (int i = 0; i < tree.size(); i++)
	{
		os << tree[i];
		if (i + 1 < tree.size()) os << ",";
	}
	os << "}";
	return os;
}

#ifdef _WINDOWS_
#include <Windows.h>
#include <sstream>
#include <string>


template <typename T> const crect_int& PrintTreeNode(HDC hdc,int x,int y,const BinaryTreeNode<T>& node)
{
	static float xMul = 1.2;
	static float yMul = 1.5;
	static int xAdd = 0;
	static int yAdd = -5;
	std::stringstream ss;
	static crect_int cr;
	SIZE strsize;
	std::string sz;

	ss.clear();
	ss << node.value()<<(char)0;
	sz = ss.str();
	int i = sz.size();

	SetTextAlign(hdc, TA_BASELINE | TA_CENTER | TA_NOUPDATECP);
	GetTextExtentPoint32(hdc, sz.c_str(), 4, &strsize);
	

	cr.SetHeight(strsize.cy*yMul);
	cr.SetWidth(strsize.cx*xMul);
	cr.SetCentreX(x+xAdd);
	cr.SetCentreY(y+yAdd);
	cr.draw(hdc);
	TextOut(hdc, x, y, sz.c_str(), sz.size()-1);
	return cr;
}
template <typename T> void PrintTree(HDC hdc, int x, int y,int w,int h,BinaryTree<T>& tree)
{
	int m;
	int *a;
	crect_int *cr;

	tree.SetTreeOrder(order_level);

	a = new int[tree.height() + 1];
	for (int i = 0; i <= tree.height(); i++) a[i] = 0;
	for (int i = 0; i < tree.size(); i++)
	{
		a[tree.node(i)->depth()]++;
	}

	m = 0;
	cr = new crect_int[tree.size()];
	for (int i = 0; i <= tree.height(); i++)
	{
		for (int j = 0; j < a[i]; j++)
		{
			cr[m] = PrintTreeNode(hdc, x + w * (j + 1) / (a[i] + 1), y + h * (i + 1) / (2+tree.height()), *tree.node(m));
			if (tree.node(i)->parent() != NULL)
			{
				int n = tree.node(m)->parent()->order();
				Line(hdc, cr[m], cr[n]);
			}
			m++;
		}
	}
}
#endif