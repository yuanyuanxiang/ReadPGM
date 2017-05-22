
// ReadPGMDoc.h : CReadPGMDoc ��Ľӿ�
//


#pragma once

#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4)

class CReadPGMDoc : public CDocument
{
protected: // �������л�����
	CReadPGMDoc();
	DECLARE_DYNCREATE(CReadPGMDoc)

// ����
public:
	CImage*					m_pImage;			// ͼ��ָ��
	int						m_nType;			// ͼ�����
	int						m_nImageWidth;		// ͼ����
	int						m_nImageHeight;		// ͼ��߶�
	int						m_nBitCount;		// ͼ��λ��

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CReadPGMDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
};
