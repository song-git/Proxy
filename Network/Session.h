//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : Session.h
//  @ Date : 2011-1-21
//  @ Author : chenjinyi
//
//


#if !defined(_CSESSION_H)
#define _CSESSION_H

#include <list>
using namespace std;

#include "Network.h"
#include "../Thread/Mutex.h"

#include "NetworkDefine.h"
#include "Buffer.h"

class CNetwork;

class CSession
{
public:
    CSession(CNetwork* pNetwork);
    ~CSession();

    //此函数为回调函数调用
    int Send(int fd);
    int Recv(int fd);

    //此函数由用户调用
    int Send(const char* pData, int dataSize);

    void Shutdown();

    void SetFd(int fd) { m_mutex.Lock(); m_nFd = fd; m_mutex.Unlock(); }
    int GetFd() { return m_nFd; }

    void SetState(int state) { m_mutex.Lock(); m_state = state; m_mutex.Unlock(); }
    int GetState() { return m_state; }

    void SetIP(const char* ip) { m_mutex.Lock(); strcpy(m_ip, ip); m_mutex.Unlock(); }
    char* GetIP() { return m_ip; }

    void SetPort(unsigned short port) { m_mutex.Lock(); m_port = port; m_mutex.Unlock(); }
    unsigned short GetPort() { return m_port; }

    void SetListenPort(unsigned short port) { m_mutex.Lock(); m_listenPort = port; m_mutex.Unlock(); }
    unsigned short GetListenPort() { return m_listenPort; }

    void SetRole(int role) {  m_mutex.Lock(); m_role = role; m_mutex.Unlock(); }
    int GetRole() { return m_role; }

    void SetType(int type) { m_mutex.Lock(); m_type = type; m_mutex.Unlock(); }
    int GetType() { return m_type; }

private:
    void DispatchPacket(const char* packet, int packetLen);

    int NetDatainQueue(int fd);

private:
    const static int MAX_SEND_LIST_SIZE = 1024*1024*20;
    const static int DEFAULT_PACKET_MAXLEN = 2*1024*1024;
    const static int UNREACHABLE_PACKET_LEN = 20*1024*1024;
    const static int PACKET_LENGHT_UNKNOWN = -1;

    const static size_t DEFAULT_SEND_LEN = 4096;
    const static size_t DEFAULT_RECV_LEN = 4096;

    int m_state;
    int m_role;
    int m_type;
    char* m_ip;
    unsigned short m_port;
    unsigned short m_listenPort;
    int m_nFd;

    char* m_tmpRecvBuffer;

    char* m_pPacket;
    int m_nPacketLen;

    CNetwork* m_network;
    CMutex m_mutex;

    CMutex m_readMutex;
    CMutex m_writeMutex;
    CBuffer m_readBuffer;
    CBuffer m_writeBuffer;

    int m_npacketType;
};

#endif  //_CSESSION_H
