
// ReadPGMDoc.cpp : CReadPGMDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "ReadPGM.h"
#endif

#include "ReadPGMDoc.h"
#include <cmath>
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CReadPGMDoc

IMPLEMENT_DYNCREATE(CReadPGMDoc, CDocument)

BEGIN_MESSAGE_MAP(CReadPGMDoc, CDocument)
END_MESSAGE_MAP()


// CReadPGMDoc ����/����

CReadPGMDoc::CReadPGMDoc()
{
	m_pImage = NULL;
}

CReadPGMDoc::~CReadPGMDoc()
{
	if (m_pImage != NULL)
		delete m_pImage;
}

BOOL CReadPGMDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CReadPGMDoc ���л�

void CReadPGMDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CReadPGMDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CReadPGMDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CReadPGMDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CReadPGMDoc ���

#ifdef _DEBUG
void CReadPGMDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CReadPGMDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CReadPGMDoc ����


BOOL CReadPGMDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	char *fStream;
	CFile file;
	ULONGLONG filelength;

	if (!file.Open(lpszPathName, CFile::modeRead | CFile::shareDenyWrite))
		return FALSE;

	//��ȡ�ļ�����
	filelength = file.GetLength();
	fStream = new char[filelength];
	file.Read(fStream, filelength);

	int i = 0, j = 0, k = 0, start = 0, speLine = -1, curLine = 0, tempnum = 0, arg[4] = {0, 0, 0, 0};

	// �����Ƿ���ע����
	bool note = false;
	for (i = 0; curLine<3 && i<filelength; i++)
	{
		if(fStream[i] == '\n')
		{
			curLine++;
			//�Ƿ�Ϊע����
			if (i+1 < filelength && fStream[i+1] == '#')
			{
				speLine = curLine + 1;
				note = true;
				break;
			}
		}
	}

	bool IsPBM = false;
	if (!note)
	{
		for(i = 0; i < filelength; i++)
		{
			//��ʱ�������
			if(fStream[i] >= '0' && fStream[i] <= '9')
				tempnum = tempnum * 10 + fStream[i] - '0';
			if(fStream[i] == '\n' || fStream[i] == '\t' || fStream[i] == ' ')
			{
				arg[j++] = tempnum;
				tempnum = 0;
			}
			if (arg[0] == 1 || arg[0] == 4)
				IsPBM = true;
			if(j == 4 - IsPBM)
				break;
		}
	}
	else
	{
		curLine = 0;
		for(i = 0; i < filelength; i++)
		{
			//��ʱ�������
			if(fStream[i] >= '0' && fStream[i] <= '9')
				tempnum = tempnum * 10 + fStream[i] - '0';
			if(curLine != speLine)
			{
				if(fStream[i] == '\n')
				{
					curLine++;
					//�Ƿ�Ϊע����
					if(curLine != speLine)
					{
						arg[j++] = tempnum;
						tempnum = 0;
					}
					else tempnum = 0;
				}
			}
			else if(fStream[i] == '\n' || fStream[i] == '\t' || fStream[i] == ' ')
			{
				arg[j++] = tempnum;
				tempnum = 0;
			}
			if (arg[0] == 1 || arg[0] == 4)
				IsPBM = true;
			if(j == 4 - IsPBM)
				break;
		}
	}
	start = i + 1;

	m_nType = arg[0];
	m_nImageWidth = arg[1];
	m_nImageHeight = arg[2];
	m_nBitCount;
	if (m_nImageWidth * m_nImageHeight == 0)
	{
		file.Close();
		delete fStream;
		fStream = NULL;
		return FALSE;
	}

	switch (m_nType)
	{
	case 1: case 4: m_nBitCount = 1; break;
	case 2: case 5: m_nBitCount = 8; break;
	case 3: case 6: m_nBitCount = 24;break;
	default:
		AfxMessageBox(L"ͼ���Ƿ�Ϊ��׼��PGM��ʽ��", MB_OK | MB_ICONQUESTION);
		file.Close();
		delete fStream;
		fStream = NULL;
		return FALSE;
	}

	long Rowlen;
	if (m_nBitCount == 1)
		Rowlen = WIDTHBYTES(m_nImageWidth * 8);
	else
		Rowlen = WIDTHBYTES(m_nImageWidth * m_nBitCount);

	// ����CImage����
	if (m_pImage != NULL) delete m_pImage;
	m_pImage = new CImage;
	m_pImage->Create(m_nImageWidth, m_nImageHeight, m_nBitCount);
	BYTE* pBits = (BYTE*)m_pImage->GetBits() + m_pImage->GetPitch() * (m_nImageHeight - 1);

	int x = 0, y = 0;
	i = j = tempnum = 0;
	switch(m_nType)
	{
	case 4:
		{
			memcpy(pBits, fStream + start, filelength - start);
			break;
		}
	case 5:
	case 6:
		{
			BYTE *pCur = pBits + m_nImageHeight * Rowlen;
			for(i = start; i < filelength; ++i)
			{
				pCur--;
				*pCur = (BYTE)fStream[i];
			}
			break;
		}
	case 1:
		{
			BYTE one = 128;	//1000,0000
			BYTE zero = ~one;//0111,1111
			BYTE* pCur;
			for(i = start; i < filelength; ++i)
			{
				if(fStream[i] >= '0' && fStream[i] <= '9')
					tempnum = tempnum * 10 + fStream[i] - '0';
				if(fStream[i] == '\t' || fStream[i] == ' ')
				{
					pCur = (BYTE*)m_pImage->GetPixelAddress(x++, y);
					if (tempnum == 1)
					{
						*pCur = (*pCur | one);
						tempnum = 0;
					}
					else
					{
						*pCur = (*pCur & zero);
					}
					if (x == m_nImageWidth)
					{
						x = 0;
						y++;
					}
				}
			}
			break;
		}
	case 2:
	case 3:
		{
			BYTE *pCur = pBits + m_nImageHeight * Rowlen;
			for(i = start; i < filelength; ++i)
			{
				if(fStream[i] >= '0' && fStream[i] <= '9')
					tempnum = tempnum * 10 + fStream[i] - '0';
				if(fStream[i] == '\t' || fStream[i] == ' ')
				{
					pCur--;
					*pCur = (BYTE)tempnum;
					tempnum = 0;
				}
			}
			break;
		}
	}

	// ������ɫ��
	switch (m_nBitCount)
	{
	case 1:
		{
			RGBQUAD ColorTable[2];
			ColorTable[0].rgbRed = ColorTable[0].rgbGreen = ColorTable[0].rgbBlue = 255;
			ColorTable[0].rgbReserved = 0;
			ColorTable[1].rgbRed = ColorTable[1].rgbGreen = ColorTable[1].rgbBlue = 0;
			ColorTable[1].rgbReserved = 0;
			m_pImage->SetColorTable(0, 2, ColorTable);
			break;
		}
	case 8:
		{
			RGBQUAD ColorTable[256];
			for (i = 0; i < 256; i++)
			{
				ColorTable[i].rgbRed = ColorTable[i].rgbGreen = ColorTable[i].rgbBlue = i;
				ColorTable[i].rgbReserved = 0;
			}
			m_pImage->SetColorTable(0, 256, ColorTable);
			break;
		}
	default:
		break;
	}

	file.Close();
	delete fStream;
	fStream = NULL;

	// ��ӵ�����ļ��б�
	SetPathName(lpszPathName);
	SetModifiedFlag(FALSE);

	return TRUE;
}