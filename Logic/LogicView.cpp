
// LogicView.cpp : CLogicView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Logic.h"
#endif

#include "LogicDoc.h"
#include "LogicView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CLogicView

IMPLEMENT_DYNCREATE(CLogicView, CView)

BEGIN_MESSAGE_MAP(CLogicView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_ANDGATE, &CLogicView::OnAndgate)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CLogicView ����/�Ҹ�

CLogicView::CLogicView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CLogicView::~CLogicView()
{
}

BOOL CLogicView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CLogicView �׸���

CArray<CRect, CRect&> boxes; // �ڽ� ��ü ����Ʈ
int current;
bool move;
int startx;
int starty;

void CLogicView::OnDraw(CDC* /*pDC*/)
{
	CLogicDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

					   // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

	dc.SelectStockObject(NULL_BRUSH);
	//dc.SetROP2(R2_COPYPEN);

	/*
	for (int i = 0; i<boxes.GetCount(); i++) {
		dc.Rectangle(boxes[i].left, boxes[i].top, boxes[i].right, boxes[i].bottom);
	}
	*/

}


// CLogicView �μ�

BOOL CLogicView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CLogicView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CLogicView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CLogicView ����

#ifdef _DEBUG
void CLogicView::AssertValid() const
{
	CView::AssertValid();
}

void CLogicView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLogicDoc* CLogicView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLogicDoc)));
	return (CLogicDoc*)m_pDocument;
}
#endif //_DEBUG


// CLogicView �޽��� ó����

/*
void CLogicView::AndGate(CClientDC& dc, int x, int y) {
	Graphics ScreenG(dc.GetSafeHdc());
	Bitmap* pBitmapAND;
	pBitmapAND = Bitmap::FromResource(AfxGetInstanceHandle(), (WCHAR*)MAKEINTRESOURCE(IDB_ANDGATE));

	ScreenG.DrawImage(pBitmapAND, Rect(x, y, pBitmapAND->GetWidth() + x, pBitmapAND->GetHeight() + y), x, y, pBitmapAND->GetWidth() + x, pBitmapAND->GetHeight() + y, UnitPixel);
	//boxes.Add(*pBitmapAND);
	//current = boxes.GetCount() - 1;
	delete pBitmapAND;
}
*/

void CLogicView::OnAndgate()
{
	CClientDC dc(this);

	
	Graphics ScreenG(dc.GetSafeHdc());
	Bitmap* pBitmapAND;
	pBitmapAND = Bitmap::FromResource(AfxGetInstanceHandle(), (WCHAR*)MAKEINTRESOURCE(IDB_ANDGATE));

	ScreenG.DrawImage(pBitmapAND, Rect(0, 0, pBitmapAND->GetWidth(), pBitmapAND->GetHeight()), 0, 0, pBitmapAND->GetWidth(), pBitmapAND->GetHeight(), UnitPixel);
	CRect* box = new CRect(0, 0, pBitmapAND->GetWidth(), pBitmapAND->GetHeight());
	boxes.Add(*box);
	current = boxes.GetCount() - 1;
	delete pBitmapAND;
}
/*
void CLogicView::OnLButtonDown(UINT nFlags, CPoint point)
{
	startx = point.x;
	starty = point.y;

	current = -1;
	for (int i = 0; i < boxes.GetCount(); i++) {
		if (boxes[i].GetWidth <= point.x && point.x <= boxes[i].right ||boxes[i].right <= point.x && point.x <= boxes[i].left) {
			if (boxes[i].top <= point.y && point.y <= boxes[i].bottom ||boxes[i].bottom <= point.y && point.y <= boxes[i].top) {
				current = i;
				move = true;
				break;
			}
		}
	}

	CView::OnLButtonDown(nFlags, point);
}


void CLogicView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (current != -1) {
		if(move==true) {
			CClientDC dc(this);
			dc.SelectStockObject(NULL_BRUSH);
			dc.SetROP2(R2_NOT);

			dc.Rectangle(boxes[current].left, boxes[current].top, boxes[current].right, boxes[current].bottom);

			// �̵�
			boxes[current].left += point.x - startx;
			boxes[current].top += point.y - starty;
			boxes[current].right += point.x - startx;
			boxes[current].bottom += point.y - starty;

			startx = point.x;
			starty = point.y;

			AndGate(dc, startx, starty);
		}
	}

	CView::OnMouseMove(nFlags, point);
}


void CLogicView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (current != -1) {

		CClientDC dc(this);
		dc.SelectStockObject(NULL_BRUSH);
		dc.SetROP2(R2_COPYPEN);

		dc.Rectangle(boxes[current].left, boxes[current].top, boxes[current].right, boxes[current].bottom);

		current = -1;
		move = false;
	}

	CView::OnLButtonUp(nFlags, point);
}
*/
