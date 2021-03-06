#ifndef _GR_ROUTE_H__
#define _GR_ROUTE_H__
#include "include.h"
#include "redisevent.h"
#include "accesslayer.h"
#include "config.h"
#include "redismsg.h"
#include <list>

class GR_Route
{
public:
    struct Listen 
    {
        string      strPName;   /* listen: as "hostname:port" */
        string      strName;    /* hostname */
        int         iPort;      /* port */
    };
public:
    GR_Route();
    virtual ~GR_Route();

    virtual int Init(GR_Config *pConfig);
    virtual int ReInit();

    virtual GR_RedisEvent* Route(GR_RedisEvent* vEventList, int iNum, GR_AccessEvent *pEvent);
    virtual GR_RedisEvent* Route(char *szKey, int iLen, int &iError);
    virtual GR_RedisEvent* Route(GR_MsgIdenty *pIdenty, GR_MemPoolData  *pData, GR_RedisMsg &msg,int &iError);
    virtual bool GetListenInfo(string &strIP, uint16 &uiPort, int &iBackLog);
    virtual GR_RedisServer* AddRedis(char *szIP, uint16 usPort, int &iResult);
    virtual GR_RedisServer* AddRedis(int &iResult);
    virtual GR_RedisServer* GetRedis(char *szIP, uint16 usPort);
    virtual GR_RedisServer* GetRedis(char *szAddr);
    virtual int DelRedis(GR_RedisEvent *pEvent);
public:
    GR_REDIS_ROUTE_TYPE         m_iMode;            // 工作模式 

    int                         m_iSrvNum = 0;      // 连接的redis个数
    GR_RedisServer              **m_vServers;       // redis连接信息,和后端redis连接数不会太多，增删改查需求比较少，直接数组管理
    unordered_map<uint64, GR_RedisServer*>  m_mapServers;
    list<GR_RedisServer*>       m_listSentinels;    // sentinel信息  
    bool m_bSentinel =          false;              // 是否使用sentinel服务
    GR_Config                   *m_pConfig = nullptr;
};

#endif
