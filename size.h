#pragma once

//////////////////////////////////////////////////////////////////////////
// FileName : size.h
// Creator : ÍõÎÄÏ²
// Data : 2021/04/18
//////////////////////////////////////////////////////////////////////////

class Size
{
public:
	Size(int width, int height);
	virtual ~Size();

	int getWidth() { return m_nWidth; }
	int getHeight() { return m_nHeight; }

	void setWidth(int width) { m_nWidth = width; }
	void setHeight(int height) { m_nHeight = height; }

private:
	int m_nWidth = 0;
	int m_nHeight = 0;
};


