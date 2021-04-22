#pragma once

//////////////////////////////////////////////////////////////////////////
// FileName : size.h
// Creator : ����ϲ
// Data : 2021/04/18
//////////////////////////////////////////////////////////////////////////

class Size
{
public:
	Size(int width, int height);
	virtual ~Size();

	int getHeight() { return m_nHeight; }
	int getWidth() { return m_nWidth; }



private:
	int m_nWidth = 0;
	int m_nHeight = 0;
};


