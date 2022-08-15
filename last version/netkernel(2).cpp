#include "netkernel.h"
#include <iostream>

NetKernel::NetKernel(QObject *parent)
    : QObject{parent}
{
    m_server= new QTcpServer(this);
    m_usock = new QUdpSocket(this);
    connect(m_server,&QTcpServer::newConnection,this,&NetKernel::NewConnect);
    beginTcpServer();
}

NetKernel::~NetKernel()
{
    if(m_server)
    {
        m_server->close();
        m_server->deleteLater();
        m_server = nullptr;
    }
    if(m_usock)
    {
        m_usock->close();
        m_usock->deleteLater();
        m_usock = nullptr;
    }
}

bool NetKernel::beginTcpServer()
{
    m_server->listen(QHostAddress::Any,USR_CONNECT_PORT);
    return true;
}

void NetKernel::udpbocast()
{
    std::cout<<"udp send data"<<std::endl;
    QByteArray sendData = "START_INFO";
    m_usock->writeDatagram(sendData,QHostAddress::Broadcast,UDP_BOCAST_PORT);
    std::cout<<"send finish"<<std::endl;

}

// 从树莓派接收和处理数据
void NetKernel::RecvData(QTcpSocket* sock)
{
    //std::cout<<sock<<std::endl;
    if(sock == nullptr) return;
    QByteArray buff = sock->readAll(); //接收主机端的数据
    int* type = (int*)buff.data();
    std::cout<<*type<<std::endl;
    if(*type == DATA_RSP) // 根据包类型 处理 最开始广播后 树莓派连接本主机 发出rtsp地址
    {
        std::cout<<"recv rsp"<<std::endl;
        DATARSP* recvpack = (DATARSP*)buff.data();
        std::cout<<recvpack->type<<" RTSP "<<recvpack->rtspaddr<<std::endl;
        std::cout<<recvpack->rtspaddr<<std::endl;

        Wnd2SockMap[recvpack->rtspaddr] = sock; // 绑定 rtsp 地址和 socket
        std::cout<<"Wnd2SockMap[addr]"<<Wnd2SockMap[recvpack->rtspaddr]<<std::endl;
        QString rtsp(recvpack->rtspaddr);

        //emit SendRecvRtsp(rtsp,sock); // 将rtsp 和 套机字发送到主机端
        emit UpdateRtspList(rtsp);

        RSPOK* okrsp = new RSPOK;  // 向树莓派返回确认收到的信息，此后树莓派不再发送 rtsp信息
        okrsp->type = RSP_RECV_OK;
        SendMsg(sock,(char*)okrsp,sizeof(RSPOK));
        delete okrsp;
    }

    else if(*type == DATA_ENV_INFO)  // 环境信息

    {
        envInfoPack* recvpack = (envInfoPack*)buff.data();
        std::cout<<recvpack->type<<" "<<recvpack->Soil_moisture<<" "<<recvpack->env_temperature<<" "<<recvpack->env_moisture<<std::endl;
        std::cout<<WndBind[sock]<<std::endl;
        if(WndBind[sock]){ // 如果该套机字已经绑定，更新该窗口的环境信息
            std::cout<<"WndBind update"<<std::endl;
            WndBind[sock]->UpdateEnv(recvpack->Soil_moisture,recvpack->env_temperature,recvpack->env_moisture); //更新
        }
    }
}


void NetKernel::SendMsg(QTcpSocket* m_sock,char* buf,int len) // tcp 发送消息函数
{
    std::cout<<"send msg"<<std::endl;
    sendlock.lock();
    m_sock->write(buf,len);
    sendlock.unlock();
}


void NetKernel::NewConnect()
{
    QTcpSocket* m_sock = m_sock = m_server->nextPendingConnection();
  //  QString sock_ip = m_sock->peerAddress().toString();
    sockList.append(m_sock);
    connect(m_sock,&QTcpSocket::readyRead,this,[=](){ // 此处用引用传递报错
        std::cout<<"recv msg"<<std::endl;
        this->RecvData(m_sock);
    });
}

void NetKernel::BindWnd2Sock(QString rtsp,OneVedioWindow* Wnd) // 将子窗口和套接字关联
{
    std::cout<<"test bind "<<rtsp.toStdString()<<std::endl;
    if(Wnd2SockMap[rtsp])
    {
        std::cout<<"test  "<<rtsp.toStdString()<<std::endl;
        std::cout<<"Wnd2SockMap"<<Wnd2SockMap[rtsp]<<std::endl;
        WndBind[Wnd2SockMap[rtsp]] = Wnd;
    }
}
