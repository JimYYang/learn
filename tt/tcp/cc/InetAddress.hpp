#pragma once
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string>
// socket的地址协议类
class InetAddress
{
private:
    sockaddr_in addr;                                                          // 表示地址协议的结构体
public : lnetAddress(const std::string &ip, uint16 t port); // 如果是监听的fd，用这个构造函数。InetAddress(const sockaddr in addr):addr addr) // 如果是客户端连上来的fd，用这个构造函数~InetAddress(0):
    // 返回字符串表示的地址，例如: 192.168.150.128
    const char *ip0 const;
    // 返回整数表示的端口，例如: 80、8080
uint16 t port0) const;
const sockaddr *addr() const; // 返回addr 成员的地址，转换成了sockaddr
};