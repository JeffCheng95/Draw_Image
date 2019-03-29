#pragma once
class CGraph
{
public:
	CGraph();
	CGraph(UINT m_nDrawType, CPoint m_ptOrigin, CPoint m_ptEnd);
	~CGraph();

public:		//成员变量
	UINT m_nDrawType;
	CPoint m_ptOrigin;
	CPoint m_ptEnd;
};

