#pragma once

class CMyShape
{
public:
	CMyShape();
	~CMyShape();

	struct MYSHAPE
	{
		int x;
		int y;
		int cx;
		int cy;
		COLORREF cbrush;
	};

	CPoint	m_point;
	CSize	m_size;
	COLORREF	m_cBrush = RGB(0, 255, 0);
	COLORREF	m_cPen = RGB(255, 0, 0);
	int			m_nPenWidth = 5;
	BOOL PtInShape(CPoint point);
	MYSHAPE GetData();
};

