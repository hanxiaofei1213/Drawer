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
	Point(int x, int y) : m_nx(x), m_ny(y) {};
	~Point() {};

	// �ƶ����캯�����ƶ���ֵ�����
	Point(Point&& point) noexcept;
	Point& operator=(Point&& point) noexcept;
	
	void setX(int x) { m_nx = x; }
	void setY(int y) { m_ny = y; }
	int x() const { return m_nx; }
	int y() const { return m_ny; }

	Point addPoint(const Point& point) const;                               // �������
	Point minusPoint(const Point& point) const;                             // �������
	bool equalPoint(const Point& point) const;                              // �ж��������

	virtual bool pointAroundPoint(const Point& p1, int level) const;        // �ж������Ƿ�ӽ�
	virtual bool pointAroundLine(const Point& lineBegin, const Point& lineEnd, int level) const;  // �ж�һ�����Ƿ񿿽���
	

private:
	int m_nx = 0;
	int m_ny = 0;
};