//=================================================================
//crect.h
//CreateBy Croper
//last modified at Dec.17.2018
//矩形的类，矩形的坐标可以是任何支持四则运算的变量格式。默认有支持float类型的crect和支持int类型的crect_int
//在下面的函数中 使用类T时并没有使用T&的格式是为了能进行自动类型转换
//===================================================================
#pragma once
#define CRECT_H
#include "location.h"
#include <Windows.h>

template <typename T> class crect_template;
typedef crect_template<float> crect;
typedef crect_template<int> crect_int;

template <typename T> class crect_template
{
private:
	T Left, Top, Right, Bottom;
public:
	crect_template();
	crect_template(const location_template<T>&, const location_template<T>&);
	crect_template(T, T, T, T);                //不使用const T& 是为了使其能进行自动类型转换
	crect_template(const crect_template<T>&);  //复制构造函数
	template <typename T2> crect_template(const crect_template<T2>&);  //类型转换函数
	~crect_template();

	const T& left() const;
	const T& top() const;
	const T& right() const;
	const T& bottom() const;

	location_template<T> centre() const;
	T height() const;
	T width() const;
	relatpos rltpos(location_template<T>) const;   //与点的相对位置，pos_intersect相交 pos_tangency 相切（点在矩形边上) pos_separation相离
	relatpos rltpos(crect_template<T>) const;   //与矩形的相对位置，pos_intersect相交 pos_tangency 相切（只有顶点接触也算相切) pos_separation相离
	bool contain(location_template<T>,bool=false) const;   //是否包含点，第二个参数表示相切时是否算包含
	bool contain(crect_template<T>,bool=false) const;   //是否包含矩形，第二个参数表示相切时是否算包含
	bool iscontained(crect_template<T>, bool = false) const;   //是否被矩形包含，第二个参数表示相切时是否算包含

	void SetHeight(T, int = 0);   //设置高度，第二个参数为0时默认为中心点不变，为1时为顶不变，为2时为底不变
	void SetWidth(T, int = 0);  //设置宽度，第二个参数为0时默认为中心点不变，为1时为左边不变，为2时为右边不变
	void SetLeft(T);             
	void SetRight(T);
	void SetTop(T);
	void SetBottom(T);
	void SetCentre(const location_template<T>&); //设置中心点
	void SetCentre(const T&,const T&);           //设置中心点
	void SetCentreX(const T&); //设置中心X坐标
	void SetCentreY(const T&); //设置中心Y坐标

#ifdef _WINDOWS_
	void draw(HDC hdc);
#endif
};

template <typename T> crect_template<T>::crect_template()
{
	Left = (T)0;
	Right = (T)0;
	Top = (T)0;
	Bottom = (T)0;
}
template <typename T> crect_template<T>::crect_template(const location_template<T>& loc1, const location_template<T>& loc2)
{
	Left = min(loc1.x, loc2.x);
	Top = min(loc1.y, loc2.y);
	Right = max(loc1.x, loc2.x);
	Bottom = max(loc1.y, loc2.y);
}
template <typename T> crect_template<T>::crect_template(T x1, T y1, T x2, T y2)
{
	Left = min(x1, x2);
	Top = min(y1, y2);
	Right = max(x1, x2);
	Bottom = max(y1, y2);
}

template <typename T> crect_template<T>::crect_template(const crect_template<T>& crect0)
{
	Left = crect0.Left;
	Top = crect0.Top;
	Right = crect0.Right;
	Bottom = crect0.Bottom;
}

template <typename T> template <typename T2> crect_template<T>::crect_template(const crect_template<T2>& crect0)
{
	Left =(T) crect0.left();
	Top = (T)crect0.top();
	Right = (T)crect0.right();
	Bottom = (T)crect0.bottom();
}
template <typename T> crect_template<T>::~crect_template()
{}

template <typename T> inline const T& crect_template<T>::left() const
{
	return Left;
}
template <typename T> inline const T& crect_template<T>::right() const
{
	return Right;
}
template <typename T> inline const T& crect_template<T>::bottom() const
{
	return Bottom;
}
template <typename T> inline const T& crect_template<T>::top() const
{
	return Top;
}

template <typename T> inline location_template<T> crect_template<T>::centre() const
{
	return location_template<T>((Left + Right) / 2, (Top + Bottom) / 2);
}
template <typename T> inline T crect_template<T>::height() const
{
	return Bottom - Top;
}
template <typename T> inline T crect_template<T>::width() const
{
	return Right - Left;
}

template <typename T> relatpos crect_template<T>::rltpos(location_template<T> loc) const   //与点的相对位置，pos_intersect相交(点在矩形内） pos_tangency 相切（点在矩形边上) pos_separation相离
{
	if ((loc.x > Left) && (loc.x < Right) && (loc.y > Top) && (loc.y < Bottom)) return pos_intersect;
	if ((loc.x < Left) || (loc.x > Right) || (loc.y < Top) || (loc.y > Bottom)) return pos_separation;
	return pos_tangency;
}
template <typename T> relatpos crect_template<T>::rltpos(crect_template<T> crect0) const  //与矩形的相对位置，pos_intersect相交(包括包含) pos_tangency 相切（只有顶点接触也算相切) pos_separation相离
{
	//相交，任意一个顶点在另一个矩形内
	if ((Right < crect0.Left) || (Left > crect0.Right) || (Top < crect0.Bottom) || (Bottom > crect0.Top)) return pos_separation;
	if ((Right == crect0.Left) || (Left == crect0.Right) || (Top == crect0.Bottom) || (Bottom == crect0.Top)) return pos_tangency;
	return pos_intersect;
}
template <typename T> bool crect_template<T>::contain(location_template<T> loc, bool withtgc) const  //是否包含点，第二个参数表示相切时是否算包含
{
	if (withtgc) return ((loc.x >= Left) && (loc.x <= Right) && (loc.y >= Top) && (loc.y <= Bottom));
	return ((loc.x > Left) && (loc.x < Right) && (loc.y > Top) && (loc.y < Bottom));
}
template <typename T> bool crect_template<T>::contain(crect_template<T> rect0, bool withtgc) const  //是否包含矩形，第二个参数表示相切时是否算包含
{
	if (withtgc) return ((rect0.Left >= Left) && (rect0.Right <= Right) && (rect0.Top >= Top) && (rect0.Bottom <= Bottom));
	return ((rect0.Left > Left) && (rect0.Right < Right) && (rect0.Top > Top) && (rect0.Bottom < Bottom));
}
template <typename T> bool crect_template<T>::iscontained(crect_template<T> rect0, bool withtgc) const  //是否被矩形包含，第二个参数表示相切时是否算包含
{
	if (withtgc) return ((rect0.Left <= Left) && (rect0.Right >= Right) && (rect0.Top <= Top) && (rect0.Bottom >= Bottom));
	return ((rect0.Left < Left) && (rect0.Right > Right) && (rect0.Top < Top) && (rect0.Bottom > Bottom));
}

template <typename T> void crect_template<T>::SetHeight(T t, int param)   //设置高度，第二个参数为0时默认为中心点不变，为1时为顶不变，为2时为底不变
{
	if (t < 0) t = 0 - t;
	switch (param)
	{
	case 0:
		Top = Top + (Bottom - Top - t) / 2;
		Bottom = Top + t;
		return;
	case 1:
		Bottom = Top + t;
		return;
	case2:
		Top = Bottom - t;
	}
}

template <typename T> void crect_template<T>::SetWidth(T t, int param)  //设置宽度，第二个参数为0时默认为中心点不变，为1时为左边不变，为2时为右边不变
{
	if (t < 0) t = 0 - t;
	switch (param)
	{
	case 0:
		Left = Left + (Right - Left - t) / 2;
		Right = Left + t;
		return;
	case 1:
		Right = Left + t;
		return;
	case2:
		Left = Right - t;
	}
}
template <typename T> inline  void crect_template<T>::SetCentre(const location_template<T>& loc) //设置中心点
{
	Left = loc.x - (Right - Left) / 2;
	Right = 2 * loc.x - Left;
	Top = loc.y + (Top - Bottom) / 2;
	Bottom = 2 * loc.y - Top;
}
template <typename T> void crect_template<T>::SetCentre(const T& x, const T& y)           //设置中心点
{
	Left = x - (Right - Left) / 2;
	Right = 2*x - Left;
	Top = y + (Top - Bottom) / 2;
	Bottom = 2 *y - Top;
}
template <typename T> void crect_template<T>::SetCentreX(const T& x) //设置中心X坐标
{
	Left = x - (Right - Left) / 2;
	Right = 2 * x - Left;
}
template <typename T> void crect_template<T>::SetCentreY(const T& y) //设置中心Y坐标
{
	Top = y + (Top - Bottom) / 2;
	Bottom = 2 * y - Top;
}

#ifdef _WINDOWS_
#include <Windows.h>
template <typename T> void crect_template<T>::draw(HDC hdc)
{
	Rectangle(hdc, Left, Top, Right, Bottom);
}
void Line(HDC hdc,const crect_int r1,const crect_int r2)
{
	location_int loc1, loc2;
	int p = 1;
	int q = 1;
	float a;
	if (r1.rltpos(r1) != pos_separation) return;
	loc1 = r1.centre();
	loc2 = r2.centre();
	if (loc2.x == loc1.x)
	{
		if (loc2.y > loc1.y)
		{
			loc2.y = loc2.y - r2.height() / 2;
			loc1.y = loc1.y + r1.height() / 2;
		}
		else
		{
			loc2.y = loc2.y + r2.height() / 2;
			loc1.y = loc1.y - r1.height() / 2;
		}
	}
	else
	{
		a = ((float)loc2.y - loc1.y) / (loc2.x - loc1.x);
		if (loc1.x > loc2.x) p = -1;
		if (loc1.y > loc2.y) q = -1;
		if (r2.height() > r2.width()*abs(a))
		{
			loc2.y = loc2.y - p*a * r2.width()/2;
			loc2.x = loc2.x - p * r2.width() / 2;
		}
		else
		{
			loc2.x = loc2.x - q*r2.height() / a / 2;
			loc2.y = loc2.y - q*r2.height()/2;
		}

		if (r1.height() > r1.width()*abs(a))
		{
			loc1.y = loc1.y + p*a*r1.width()/2;
			loc1.x = loc1.x + p * r1.width() / 2;
		}
		else
		{
			loc1.x = loc1.x + q * r1.height() / a / 2;
			loc1.y = loc1.y + q * r1.height() / 2;
		}
		
	}
	MoveToEx(hdc, (int)loc1.x, (int)loc1.y, NULL);
	LineTo(hdc, (int)loc2.x, (int)loc2.y);
}
#endif