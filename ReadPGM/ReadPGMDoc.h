
// ReadPGMDoc.h : CReadPGMDoc 类的接口
//


#pragma once

#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4)

class CReadPGMDoc : public CDocument
{
protected: // 仅从序列化创建
	CReadPGMDoc();
	DECLARE_DYNCREATE(CReadPGMDoc)

// 特性
public:
	CImage*					m_pImage;			// 图像指针
	int						m_nType;			// 图像类别
	int						m_nImageWidth;		// 图像宽度
	int						m_nImageHeight;		// 图像高度
	int						m_nBitCount;		// 图像位深

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CReadPGMDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
};
