#pragma once

class Shape
{
protected:
	CPoint m_startPnt;
	CPoint m_endPnt;
public:
	virtual void OnDraw(CDC *pDc)=0;

	void SetPoints(const CPoint &n_startPnt,const CPoint &n_endPnt);
	CPoint get_m_start_pnt() const;
	CPoint get_m_end_pnt() const;
};

class ShapeRect:public Shape
{
public:
	void OnDraw(CDC* pDc) override;
};
