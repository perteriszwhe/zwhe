#ifndef __UILAYOUT_H__
#define __UILAYOUT_H__

#include <vector>
#include "cocos2d.h"
USING_NS_CC;

class UILayout: public CCNode
{
protected:
	float		m_padding;
	float		m_leftBlank;
	float		m_bottomBlank;
	float		m_rowPadding;
	float		m_columnPadding;

public:
	UILayout(void);
	~UILayout(void);

	void setBlank(float left,float bottom);
	void setPadding(float rowpadding,float colpadding);
	void setbounds(float left,float bottom,float rowpad,float colpad);

	virtual bool init();
	virtual bool initWithSize(const CCSize &size);

	/** align items vertically */
    void alignItemsVertically();
    /** align items vertically with padding
    @since v0.7.2
    */
    void alignItemsVerticallyWithPadding(float padding);

    /** align items horizontally */
    void alignItemsHorizontally();
    /** align items horizontally with padding
    @since v0.7.2
    */
    void alignItemsHorizontallyWithPadding(float padding);

	/** align items in rows of columns */
	void alignItemsInColumns(unsigned int columns, ...);
	void alignItemsInColumns(unsigned int columns, va_list args);
	void alignItemsInColumnsWithArray(CCArray* rows);

	/** align items in columns of rows */
	void alignItemsInRows(unsigned int rows, ...);
	void alignItemsInRows(unsigned int rows, va_list args);
	void alignItemsInRowsWithArray(CCArray* columns);

	CREATE_FUNC( UILayout);

	static UILayout* create(const CCSize &size);
};

#endif


