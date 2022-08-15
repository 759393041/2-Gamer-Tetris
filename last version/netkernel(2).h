#ifndef NETKERNEL_H
#define NETKERNEL_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>
#include "MyProtocol.h"
#include <QMutex>
#include <QList>
#include "OneVedioWindow.h"

class NetKernel : public QObject
{
    Q_OBJECT
public:
    explicit NetKernel(QObject *parent = nullptr);
    ~NetKernel();

    void udpbocast();
    void BindWnd2Sock(QString,OneVedioWindow* wnd);


private:
    QTcpServer* m_server;
    QUdpSocket* m_usock;
    bool beginTcpServer();
    void NewConnect();
    void RecvData(QTcpSocket* sock);
    void SendMsg(QTcpSocket* m_sock,char* buf,int len);
    QMutex sendlock;
    QList<QTcpSocket*>sockList;
    QMap<QString,QTcpSocket*>Wnd2SockMap;
    QMap<QTcpSocket*,OneVedioWindow*> WndBind;

signals:
    void SendRecvRtsp(QByteArray,QTcpSocket*);
    void UpdateRtspList(QString);
};

#endif // NETKERNEL_H
