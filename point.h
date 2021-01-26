#pragma once

//////////////////////////////////////////////////////////////////////////
// FileName : point.h
// Creator : ����ϲ
// Data : 2021/1/14
// Comment : ��ά���࣬��������ά�ȵ����꣬�мӡ������ж���ȷ�����
//////////////////////////////////////////////////////////////////////////

#include <iostream>

class Point {
public:
	Point() : m_nx(0), m_ny(0) {};  
	Point(int a_x, int a_y) : m_nx(a_x), m_ny(a_y) {};
	~Point() {};

	// �ƶ����캯�����ƶ���ֵ�����
	Point(Point&& a_point) noexcept;
	Point& operator=(Point&& a_point) noexcept;
	
	void setX(int a_x) { m_nx = a_x; }
	void setY(int a_y) { m_ny = a_y; }
	int x() const { return m_nx; }
	int y() const { return m_ny; }

	Point addPoint(const Point&) const;                               // �������
	Point minusPoint(const Point&) const;                             // �������
	bool equalPoint(const Point&) const;                              // �ж��������

	virtual bool pointAroundPoint(const Point&, int) const;                 // �ж������Ƿ�ӽ�
	virtual bool pointAroundLine(const Point&, const Point&, int) const;    // �ж�һ�����Ƿ񿿽���
	

private:
	int m_nx;
	int m_ny;
};