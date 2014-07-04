//
//  DBUtil.h
//  BuggyBug
//
//  Created by He Zhiwei on 14-6-6.
//
//

#ifndef __BuggyBug__DBUtil__
#define __BuggyBug__DBUtil__
#include "cocos2d.h"
#include "sqlite3.h"
USING_NS_CC;
class DBUtil{
public:
    
    /************************************************************
     封装 sqlite3操作
     ************************************************************/
    //用来创建一个db数据库 db为数据库的名字
    //  打开数据库
    static void initDB(std::string dbName);
    
    //用来判断表格是否存在
    // name:表示表名
    static bool tableIsExist(std::string name);
    
    
    //用来创建一个表名为name的表格，创建时会先匹配时否有该表的存在如果存在则不创建
    //创建表
    static void createTable(std::string sql,std::string name);
    
    //用来删除一张表名为name的表格，删除时会先匹配是否有该表的存在如果不存在则不执行删除操作
    //删除表名
    static void deleteTable(std::string sql,std::string name);
    
    //用来向表中插入一条数据
    //插入一条数据
    static void insertData(std::string sql);
    
    //用来向表中删除一条数据
    //删除一条数据
    static void deleteData(std::string sql);
    
    //用来向表中修改一条数据
    // 修改一条数据
    static void updateData(std::string sql);
    
    //获取一个记录的条数
    // 获得记录的条数
    static int getDataCount(std::string sql);
    
    //读取一条记录的信息
    /*
     *  此方法是查询方法,相当之重要,pSender最好是个vector
     */
    static int getDataInfo(std::string sql);
    
    //读取N条记录的信息
    /*
     *
     */
    static CCArray* getAllDataInfo(std::string sql);
    
    //关闭打开的数据库
    static void closeDB();
    
};

#endif /* defined(__BuggyBug__DBUtil__) */
