/**
 * Copyright (c) 2016, 爱wifi（版权声明）
 *
 * @file	CException.h
 * @brief 此文件的简单描述。(必填字段)
 *
 * 此文件的详细功能描述。(可选字段)
 *
 * @author: 		cj
 * @date: 		2016年1月6日
 *
 * 修订说明:初始版本
 */
#ifndef CEXCEPTION_H_
#define CEXCEPTION_H_
#include <stdio.h>
#include <sstream>

namespace Taiji
{

enum EEXCECODE
{
	/*基本异常*/
	REDIS_ERR = 10, ///redis异常
	MYSQL_ERR = 20, ///数据库异常
	SERVER_ERR = 30, ///服务器异常
	FILE_ERR = 40, ///文件异常
	DATA_ERR = 50, //数值异常
	REQUEST_ERR = 60, ///请求错误

	/*自定义派生异常*/
	TYPE_CONVER_ERR = 51, ///类型转换错误
	INVALID_ARG_ERR = 52, ///参数错误
	EXCEED_MAX_ERR = 53, ///超过最大值
	OVERFLOW_ERR = 54, ///数值溢出
	Out_Of_Range_ERR = 55, ///各种数据结构的访问越界异常

	REDIS_CONN_ERR = 11, ///redis连接异常
	MYSQL_CONN_ERR = 21,
	SERVER_CONN_ERR = 31,
};

class CException: public std::exception
{

public:
	CException( const std::string &pErrInfo ) :
			_errInfo(pErrInfo)
	{

	}

	~CException( ) throw ( )
	{

	}

	virtual const char* what( ) const throw ( )
	{
		return _errInfo.c_str();
	}

	const string getErrorCode( ) throw ( )
	{
		string errCode;
		stringstream ss;
		ss << _errCode;
		ss >> errCode;

		return errCode;
	}

	const string getErrInfo( )
	{
		string errCode, errInfo;
		stringstream ss;
		ss << _errCode;
		ss >> errCode;
		errInfo = errCode + ":" + _errInfo;

		return errInfo;
	}

private:
	void initCodeMap( )
	{
	}

protected:
	std::string _errInfo;
	EEXCECODE _errCode;
};

#define NEW_EXCEPTION( name,parent,code ) \
    class name : public parent \
    { \
        public: 	\
            name( const std::string& pErrInfo) \
            : parent( pErrInfo) \
            { \
        	_errCode=code;\
            }	\
            \
            ~name( ) throw()\
            { \
                \
            }\
    };

///<  redis error
NEW_EXCEPTION(RedisErr, CException, REDIS_ERR)
///<  数据库连接不成功
NEW_EXCEPTION(MysqlErr, CException, MYSQL_ERR)
///<  服务器连接超时
NEW_EXCEPTION(ServerErr, CException, SERVER_ERR)
///<  配置文件不存在
NEW_EXCEPTION(FileErr, CException, FILE_ERR)
///<  类型转换除错
NEW_EXCEPTION(TypeConvertErr, CException, TYPE_CONVER_ERR)
///< 参数错误
NEW_EXCEPTION(InvalidArgErr, CException, INVALID_ARG_ERR)
///< 超过最大值
NEW_EXCEPTION(ExceedMaxErr, CException, EXCEED_MAX_ERR)
///< 各种数据结构的访问越界异常
NEW_EXCEPTION(OutOfRangeErr, CException, Out_Of_Range_ERR)
///< 数值溢出
NEW_EXCEPTION(OverflowErr, CException, OVERFLOW_ERR)

/**********测试自定义继承异常************/
///<  redis连接不成功
NEW_EXCEPTION(RedisConnErr, RedisErr, REDIS_CONN_ERR)
NEW_EXCEPTION(MysqlConnErr, MysqlErr, MYSQL_CONN_ERR)
}
#endif /* CEXCEPTION_H_ */
