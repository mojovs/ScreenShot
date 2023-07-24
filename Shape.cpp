#include "pch.h"
#include "Shape.h"

void Shape::SetPoints(const CPoint& n_startPnt, const CPoint& n_endPnt)
{	m_startPnt=n_startPnt;
	m_endPnt=n_endPnt;
}

CPoint Shape::get_m_start_pnt() const
{
	return m_startPnt;
}

CPoint Shape::get_m_end_pnt() const
{
	return m_endPnt;
}

void ShapeRect::OnDraw(CDC* pDc)
{
	
	pDc->MoveTo(m_startPnt);
	pDc->Rectangle(CRect(m_startPnt,m_endPnt));
}
