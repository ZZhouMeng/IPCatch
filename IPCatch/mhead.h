/*************IP分组首部结构*********************/
typedef struct __ip_header {
	unsigned char iphVerLen;//版本号和头长度各占4位
	unsigned char ipTOS;//服务类型
	unsigned short ipLength;//分组总长度
	unsigned short ipID;//分组标识
	unsigned short ipFlags;//标志
	unsigned char ipTTL;//生存时间;TTL
	unsigned char ipProtocol;//协议可以是TCP，UDP，ICMP等
	unsigned short ipChecksum;//校验和
	unsigned long sourceIP;//源IP地址
	unsigned long destIP;//目的IP地址
}IP_HEADER,PIP_HEADER;

/*****ICMP包头结构****/
typedef struct icmphdr  //ICMP包头格式
{
	char icmpType;//ICMP包类型码
	char icmpCode;//代码
	unsigned short icmpChecksum;//校验和
	unsigned short icmpId;//标识符
	unsigned short icmpSeq;//序列号
	unsigned long  icmpTimestamp;//时间戳
}ICMPHeader;
/*******UDP包头结构*****/
typedef struct _UDPHeader  //UDP包头格式
{
	unsigned short udpSourcePort;//源端口号
	unsigned short udpDestinationPort;//目的端口号
	unsigned short udpLen;//包长度
	unsigned short udpChecksum;//校验和
}UDPHeader;
/******TCP包头结构******/
typedef struct _TCPHeader  //TCP包头格式
{
	unsigned short tcpSourcePort;//16位源端口号
	unsigned short tcpDestinationPort;//16位目的端口号
	unsigned long tcpSequenceNumber;//32位序列号
	unsigned long tcpAckNumber;//32位确认号
	char dataoffset;//高4位表示数据偏移
	char flags;//低六位为标志位
	unsigned short windows;//16位窗口大小
	unsigned short tcpChecksum;//16位校验和
	unsigned short tcpUrgentPointer;//16位紧急数据偏移量
}TCPHeader;

typedef struct __ip_Source {
	unsigned long sip;
	unsigned long dip;
	int count;
	CString kind;
	CString sport;
	CString dport;
}Sip;