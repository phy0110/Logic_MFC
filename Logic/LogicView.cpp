
// LogicView.cpp : CLogicView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_ANDGATE, &CLogicView::OnAndgate)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CLogicView 생성/소멸

CLogicView::CLogicView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CLogicView::~CLogicView()
{
}

BOOL CLogicView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CLogicView 그리기

CArray<CRect, CRect&> boxes; // 박스 객체 리스트
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

	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.

	dc.SelectStockObject(NULL_BRUSH);
	//dc.SetROP2(R2_COPYPEN);

	/*
	for (int i = 0; i<boxes.GetCount(); i++) {
		dc.Rectangle(boxes[i].left, boxes[i].top, boxes[i].right, boxes[i].bottom);
	}
	*/

}


// CLogicView 인쇄

BOOL CLogicView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CLogicView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CLogicView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CLogicView 진단

#ifdef _DEBUG
void CLogicView::AssertValid() const
{
	CView::AssertValid();
}

void CLogicView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLogicDoc* CLogicView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLogicDoc)));
	return (CLogicDoc*)m_pDocument;
}
#endif //_DEBUG


// CLogicView 메시지 처리기

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

			// 이동
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
