#include "UILayout.h"

static std::vector<unsigned int> ccarray_to_std_vector(CCArray* pArray)
{
	std::vector<unsigned int> ret;
	CCObject* pObj;
	CCARRAY_FOREACH(pArray, pObj)
	{
		CCInteger* pInteger = (CCInteger*)pObj;
		ret.push_back((unsigned int)pInteger->getValue());
	}
	return ret;
}

UILayout::UILayout(void)
	:m_padding(25),
	m_leftBlank(0),
	m_bottomBlank(0),
	m_rowPadding(10),
	m_columnPadding(10)
{
}
UILayout::~UILayout(void)
{
}

bool UILayout::init()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	return initWithSize(visibleSize);
}

void UILayout::alignItemsHorizontallyWithPadding(float padding)
{
	float width = -padding;
	if (m_pChildren && m_pChildren->count() > 0)
	{
		CCObject* pObject = NULL;
		CCARRAY_FOREACH(m_pChildren, pObject)
		{
			CCNode* pChild = dynamic_cast<CCNode*>(pObject);
			if (pChild)
			{
				width += pChild->getContentSize().width * pChild->getScaleX() + padding;
			}
		}
	}

	float x = -width / 2.0f;
	if (m_pChildren && m_pChildren->count() > 0)
	{
		CCObject* pObject = NULL;
		CCARRAY_FOREACH(m_pChildren, pObject)
		{
			CCNode* pChild = dynamic_cast<CCNode*>(pObject);
			if (pChild)
			{
				pChild->setPosition(ccp(m_leftBlank + x + pChild->getContentSize().width * pChild->getScaleX() / 2.0f + this->getContentSize().width / 2, 
					getContentSize().height / 2 + m_bottomBlank));
				x += pChild->getContentSize().width * pChild->getScaleX() + padding;
			}
		}
	}
}

void UILayout::alignItemsVerticallyWithPadding(float padding)
{
	float height = -padding;
	if (m_pChildren && m_pChildren->count() > 0)
	{
		CCObject* pObject = NULL;
		CCARRAY_FOREACH(m_pChildren, pObject)
		{
			CCNode* pChild = dynamic_cast<CCNode*>(pObject);
			if (pChild)
			{
				height += pChild->getContentSize().height * pChild->getScaleY() + padding;
			}
		}
	}

	float y = height / 2.0f;
	if (m_pChildren && m_pChildren->count() > 0)
	{
		CCObject* pObject = NULL;
		CCARRAY_FOREACH(m_pChildren, pObject)
		{
			CCNode* pChild = dynamic_cast<CCNode*>(pObject);
			if (pChild)
			{
				pChild->setPosition(ccp(m_leftBlank + getContentSize().width / 2, 
					y - pChild->getContentSize().height * pChild->getScaleY() / 2.0f + getContentSize().height / 2 + m_bottomBlank));
				y -= pChild->getContentSize().height * pChild->getScaleY() + padding;
			}
		}
	}
}

void UILayout::setBlank( float left,float bottom )
{
	m_leftBlank = left;
	m_bottomBlank = bottom;
}

void UILayout::alignItemsVertically()
{
	alignItemsVerticallyWithPadding(m_padding);
}

void UILayout::alignItemsHorizontally()
{
	alignItemsHorizontallyWithPadding(m_padding);
}

UILayout* UILayout::create( const CCSize &size )
{
	UILayout *layout = new UILayout;
	layout->initWithSize(size);
	layout->autorelease();
	return layout;
}

bool UILayout::initWithSize( const CCSize &size )
{
	if( !CCNode::init()) return false;
	this->ignoreAnchorPointForPosition(false);
	this->setAnchorPoint(ccp(.5,.5));
	this->setContentSize(size);

	return true;
}

void UILayout::alignItemsInColumns(unsigned int columns, ...)
{
	va_list args;
	va_start(args, columns);

	this->alignItemsInColumns(columns, args);

	va_end(args);
}

void UILayout::alignItemsInColumns(unsigned int columns, va_list args)
{
	CCArray* rows = CCArray::create();
	while (columns)
	{
		rows->addObject(CCInteger::create(columns));
		columns = va_arg(args, unsigned int);
	}
	alignItemsInColumnsWithArray(rows);
}

void UILayout::alignItemsInColumnsWithArray(CCArray* rowsArray)
{
	std::vector<unsigned int> rows = ccarray_to_std_vector(rowsArray);

	int height = -m_rowPadding;
	unsigned int row = 0;
	unsigned int rowHeight = 0;
	unsigned int columnsOccupied = 0;
	unsigned int rowColumns;

	if (m_pChildren && m_pChildren->count() > 0)
	{
		CCObject* pObject = NULL;
		CCARRAY_FOREACH(m_pChildren, pObject)
		{
			CCNode* pChild = dynamic_cast<CCNode*>(pObject);
			if (pChild)
			{
				CCAssert(row < rows.size(), "");

				rowColumns = rows[row];
				// can not have zero columns on a row
				CCAssert(rowColumns, "");

				float tmp = pChild->getContentSize().height;
				rowHeight = (unsigned int)((rowHeight >= tmp || isnan(tmp)) ? rowHeight : tmp);

				++columnsOccupied;
				if (columnsOccupied >= rowColumns)
				{
					height += rowHeight + m_rowPadding;

					columnsOccupied = 0;
					rowHeight = 0;
					++row;
				}
			}
		}
	}    

	// check if too many rows/columns for available menu items
	CCAssert(! columnsOccupied, "");

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	row = 0;
	rowHeight = 0;
	rowColumns = 0;
	float w = 0.0;
	float x = 0.0;
	float y = (float)(height / 2);

	if (m_pChildren && m_pChildren->count() > 0)
	{
		CCObject* pObject = NULL;
		CCARRAY_FOREACH(m_pChildren, pObject)
		{
			CCNode* pChild = dynamic_cast<CCNode*>(pObject);
			if (pChild)
			{
				if (rowColumns == 0)
				{
					rowColumns = rows[row];
					w = winSize.width / (1 + rowColumns);
					x = w;
				}

				float tmp = pChild->getContentSize().height;
				rowHeight = (unsigned int)((rowHeight >= tmp || isnan(tmp)) ? rowHeight : tmp);

				pChild->setPosition(ccp(x - winSize.width / 2 + getContentSize().width *.5 + m_leftBlank,
					y - pChild->getContentSize().height / 2 + getContentSize().height * .5 + m_bottomBlank));

				x += w + m_columnPadding;
				++columnsOccupied;

				if (columnsOccupied >= rowColumns)
				{
					y -= rowHeight + m_rowPadding;

					columnsOccupied = 0;
					rowColumns = 0;
					rowHeight = 0;
					++row;
				}
			}
		}
	}    
}

void UILayout::alignItemsInRows(unsigned int rows, ...)
{
	va_list args;
	va_start(args, rows);

	this->alignItemsInRows(rows, args);

	va_end(args);
}

void UILayout::alignItemsInRows(unsigned int rows, va_list args)
{
	CCArray* pArray = CCArray::create();
	while (rows)
	{
		pArray->addObject(CCInteger::create(rows));
		rows = va_arg(args, unsigned int);
	}
	alignItemsInRowsWithArray(pArray);
}

void UILayout::alignItemsInRowsWithArray(CCArray* columnArray)
{
	std::vector<unsigned int> columns = ccarray_to_std_vector(columnArray);

	std::vector<unsigned int> columnWidths;
	std::vector<unsigned int> columnHeights;

	int width = -10;
	int columnHeight = -5;
	unsigned int column = 0;
	unsigned int columnWidth = 0;
	unsigned int rowsOccupied = 0;
	unsigned int columnRows;

	if (m_pChildren && m_pChildren->count() > 0)
	{
		CCObject* pObject = NULL;
		CCARRAY_FOREACH(m_pChildren, pObject)
		{
			CCNode* pChild = dynamic_cast<CCNode*>(pObject);
			if (pChild)
			{
				// check if too many menu items for the amount of rows/columns
				CCAssert(column < columns.size(), "");

				columnRows = columns[column];
				// can't have zero rows on a column
				CCAssert(columnRows, "");

				// columnWidth = fmaxf(columnWidth, [item contentSize].width);
				float tmp = pChild->getContentSize().width;
				columnWidth = (unsigned int)((columnWidth >= tmp || isnan(tmp)) ? columnWidth : tmp);

				columnHeight += (int)(pChild->getContentSize().height + 5);
				++rowsOccupied;

				if (rowsOccupied >= columnRows)
				{
					columnWidths.push_back(columnWidth);
					columnHeights.push_back(columnHeight);
					width += columnWidth + 10;

					rowsOccupied = 0;
					columnWidth = 0;
					columnHeight = -5;
					++column;
				}
			}
		}
	}

	// check if too many rows/columns for available menu items.
	CCAssert(! rowsOccupied, "");

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	column = 0;
	columnWidth = 0;
	columnRows = 0;
	float x = (float)(-width / 2);
	float y = 0.0;

	if (m_pChildren && m_pChildren->count() > 0)
	{
		CCObject* pObject = NULL;
		CCARRAY_FOREACH(m_pChildren, pObject)
		{
			CCNode* pChild = dynamic_cast<CCNode*>(pObject);
			if (pChild)
			{
				if (columnRows == 0)
				{
					columnRows = columns[column];
					y = (float) columnHeights[column];
				}

				// columnWidth = fmaxf(columnWidth, [item contentSize].width);
				float tmp = pChild->getContentSize().width;
				columnWidth = (unsigned int)((columnWidth >= tmp || isnan(tmp)) ? columnWidth : tmp);

				pChild->setPosition(ccp(x + columnWidths[column] / 2 + getContentSize().width * .5 + m_leftBlank,
					y - winSize.height / 2 + getContentSize().height * .5 + m_bottomBlank));

				y -= pChild->getContentSize().height + 10;
				++rowsOccupied;

				if (rowsOccupied >= columnRows)
				{
					x += columnWidth + 5;
					rowsOccupied = 0;
					columnRows = 0;
					columnWidth = 0;
					++column;
				}
			}
		}
	}
}

void UILayout::setPadding( float rowpadding,float colpadding )
{
	m_rowPadding = rowpadding;
	m_columnPadding = colpadding;
}

void UILayout::setbounds( float left,float bottom,float rowpad,float colpad )
{
	setBlank(left,bottom);
	setPadding(rowpad,colpad);
}
