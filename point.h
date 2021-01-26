#pragma once

//////////////////////////////////////////////////////////////////////////
// FileName : point.h
// Creator : 王文喜
// Data : 2021/1/14
// Comment : 二维点类，保存两个维度的坐标，有加、减、判断相等方法。
//////////////////////////////////////////////////////////////////////////

#include <iostream>

class Point {
public:
	Point() : m_nx(0), m_ny(0) {};  
	Point(int a_x, int a_y) : m_nx(a_x), m_ny(a_y) {};
	~Point() {};

	// 移动构造函数和移动赋值运算符
	Point(Point&& a_point) noexcept;
	Point& operator=(Point&& a_point) noexcept;
	
	void setX(int a_x) { m_nx = a_x; }
	void setY(int a_y) { m_ny = a_y; }
	int x() const { return m_nx; }
	int y() const { return m_ny; }

	Point addPoint(const Point&) const;                               // 两点相加
	Point minusPoint(const Point&) const;                             // 两点相减
	bool equalPoint(const Point&) const;                              // 判断两点相等

	virtual bool pointAroundPoint(const Point&, int) const;                 // 判断两点是否接近
	virtual bool pointAroundLine(const Point&, const Point&, int) const;    // 判断一个点是否靠近线
	

private:
	int m_nx;
	int m_ny;
};