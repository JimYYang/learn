#include "InetAddress.h"

class InetAddress

private:
sockaddr in addr ;// 表示地址协议的结构体

public.
lnetAddress(const std.:string &ip,uint16 t port);// 如果是监听的fd，用这个构造函数。InetAddressiconst sockaddr in addr):addr (addr)0 // 如果是客户端连上来的fd，用这个构造函数~lnetAddress();
const char *ip() const;// 返回字符串表示的地址，例如: 192.168.150.128uint16 t port() const;// 返回整数表示的端口，例如: 80、8080const sockaddr *addr() const;// 返回addr 成员的地址，转换成了sockaddr.
lnetAddress::lnetAddress(const std::string &ipuint16 t port)// 如果是监听的fd，用这个构造函数

addr .sin family = AF INET;addr .sin addrs addr = inet addr(ip.c str());
// IPv4网络协议的套接字类型// 服务端用于监听的ip地址。// 服务端用于监听的端口。
addr .sin port = htons(port);

InetAddress;netAddress(const sockaddr in addr):addr addr)0 // 如果是客户端连上来的fd，用这个构造函数


lnetAddress:lnetAddress(const sockaddr in addr):addr (addr) // 如果是客户端连上来的fd，用这个构造函数
lnetAddress::~lnetAddress(
const char *InetAddress..ip0 const
uint16 tlnetAddress::port() const
// 返回字符串表示的地址，例如: 192.168.150.128
// 返回整数表示的端口，例如: 80、8080
const sockaddr *InetAddress.:addr0) const // 返回addr 成员的地址，转换成了sockaddr。