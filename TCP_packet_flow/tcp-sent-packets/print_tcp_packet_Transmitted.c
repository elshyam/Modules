#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/tcp.h>


static struct nf_hook_ops nfho;

static unsigned int hook_func(const struct nf_hook_ops *ops, struct sk_buff *skb, const struct net_device *in,
		const struct net_device *out, int (*okfn)(struct sk_buff *))
{
	struct iphdr *ip_header;
	struct tcphdr *tcp_header;
	u16 source_port, destination_port;
	u32 source_address, destination_address;
	u32 sequence_number, acknowledgement_number;

	if(!skb)
		return NF_ACCEPT;

	ip_header =ip_hdr(skb);

	if(ip_header->protocol != IPPROTO_TCP) /*check for TCP protocol*/
		return NF_ACCEPT;

	tcp_header = tcp_hdr(skb); /*Extract tcp_header from sk_buffer*/
   
       	/* Convert network endianness to host endiannes */
	source_address = ntohl(ip_header->saddr);
	destination_address = ntohl(ip_header->daddr);
	source_port = ntohs(tcp_header->source);
	destination_port = ntohs(tcp_header->dest);
	sequence_number = ntohl(tcp_header->seq);
	acknowledgement_number = ntohl(tcp_header->ack_seq);	
	
	
    	/* Print packet route */
	printk(KERN_INFO "Transmitted: %pI4h:%d ------> %pI4h:%d\n", &source_address, source_port, &destination_address, destination_port);
	printk(KERN_INFO "sequence number = %u    acknowlede number = %u \n", sequence_number, acknowledgement_number);
	printk(KERN_INFO "-----------------------------------------------------------------------------------------------------\n");
	
	return NF_ACCEPT;
}

static int __init tcpFields_init(void)
{
	int res;

	nfho.hook = (nf_hookfn *)hook_func;    /* hook function */
	nfho.hooknum = NF_INET_POST_ROUTING;         /* Transmitted packets */
	nfho.pf = PF_INET;                          /* IPv4 */
	nfho.priority = NF_IP_PRI_FIRST;            /* max hook priority */

	res = nf_register_hook(&nfho);              /*register netfilter hook structure */

	if (res < 0) {
		printk(KERN_INFO "Transmitter: error in nf_register_hook()\n");
		return res;
	}
	printk(KERN_INFO "Transmitter: loaded\n");

	return 0;
}

static void __exit tcpFields_exit(void)
{
	nf_unregister_hook(&nfho);           /*Unregister netfilter hook structure */
	printk(KERN_INFO "Transmitter: unloaded\n");
}

module_init(tcpFields_init);
module_exit(tcpFields_exit);

MODULE_AUTHOR("shyam saini");
MODULE_DESCRIPTION("Module for printing TCP header to see TCP syn-ack flow");
MODULE_LICENSE("GPL");
