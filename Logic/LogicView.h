
// LogicView.h : CLogicView Ŭ������ �������̽�
//

#pragma once


class CLogicView : public CView
{

protected: // serialization������ ��������ϴ�.
	CLogicView();
	DECLARE_DYNCREATE(CLogicView)

// Ư���Դϴ�.
public:
	CLogicDoc* GetDocument() const;
//	void AndGate(CClientDC& dc, int x, int y);

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CLogicView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnAndgate();
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
//	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // LogicView.cpp�� ����� ����
inline CLogicDoc* CLogicView::GetDocument() const
   { return reinterpret_cast<CLogicDoc*>(m_pDocument); }
#endif

