/*************IP�����ײ��ṹ*********************/
typedef struct __ip_header {
	unsigned char iphVerLen;//�汾�ź�ͷ���ȸ�ռ4λ
	unsigned char ipTOS;//��������
	unsigned short ipLength;//�����ܳ���
	unsigned short ipID;//�����ʶ
	unsigned short ipFlags;//��־
	unsigned char ipTTL;//����ʱ��;TTL
	unsigned char ipProtocol;//Э�������TCP��UDP��ICMP��
	unsigned short ipChecksum;//У���
	unsigned long sourceIP;//ԴIP��ַ
	unsigned long destIP;//Ŀ��IP��ַ
}IP_HEADER,PIP_HEADER;

/*****ICMP��ͷ�ṹ****/
typedef struct icmphdr  //ICMP��ͷ��ʽ
{
	char icmpType;//ICMP��������
	char icmpCode;//����
	unsigned short icmpChecksum;//У���
	unsigned short icmpId;//��ʶ��
	unsigned short icmpSeq;//���к�
	unsigned long  icmpTimestamp;//ʱ���
}ICMPHeader;
/*******UDP��ͷ�ṹ*****/
typedef struct _UDPHeader  //UDP��ͷ��ʽ
{
	unsigned short udpSourcePort;//Դ�˿ں�
	unsigned short udpDestinationPort;//Ŀ�Ķ˿ں�
	unsigned short udpLen;//������
	unsigned short udpChecksum;//У���
}UDPHeader;
/******TCP��ͷ�ṹ******/
typedef struct _TCPHeader  //TCP��ͷ��ʽ
{
	unsigned short tcpSourcePort;//16λԴ�˿ں�
	unsigned short tcpDestinationPort;//16λĿ�Ķ˿ں�
	unsigned long tcpSequenceNumber;//32λ���к�
	unsigned long tcpAckNumber;//32λȷ�Ϻ�
	char dataoffset;//��4λ��ʾ����ƫ��
	char flags;//����λΪ��־λ
	unsigned short windows;//16λ���ڴ�С
	unsigned short tcpChecksum;//16λУ���
	unsigned short tcpUrgentPointer;//16λ��������ƫ����
}TCPHeader;

typedef struct __ip_Source {
	unsigned long sip;
	unsigned long dip;
	int count;
	CString kind;
	CString sport;
	CString dport;
}Sip;