#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/in.h>


static struct nf_hook_ops nfho;
int count = 0;

static unsigned int UDP_counter_hook_func(const struct nf_hook_ops *ops, struct sk_buff *skb, const struct net_device *in,
		const struct net_device *out, int (*okfn)(struct sk_buff *))
{
	struct iphdr *ipheader;
	
	if(!skb)
		return NF_ACCEPT;

	ipheader = ip_hdr(skb);   /*Extracts IP header from sk_buff*/
	

	/*check for UDP packet comparing ip header protocol */
	if(ipheader->protocol ==  IPPROTO_UDP){       /* see full list of protocols in <linux/in.h> */
		count = count + 1;
		printk(KERN_INFO "UDP Paket number %d\n", count);
		return count;
	}

	return NF_ACCEPT;  /* The packet continues its traversal in the kernel network stack as usual, 
			      See more verdicts in include/uapi/linux/netfilter.h */
	
}
static int __init udpCounter_init(void)
{
	int res;

	nfho.hook = (nf_hookfn *)UDP_counter_hook_func;    /* hook function */
	nfho.hooknum = NF_INET_POST_ROUTING;         /* received packets */
	nfho.pf = PF_INET;                          /* IPv4 */
	nfho.priority = NF_IP_PRI_FIRST;            /* max hook priority */

	res = nf_register_hook(&nfho);              /*register netfilter hook structure */

	if (res < 0) {
		pr_err("udp _Packet_counter: error in nf_register_hook()\n");
		return res;
	}

	pr_debug("udp_packet_counter loaded\n");

	return 0;
}

static void __exit udpCounter_exit(void)
{
	nf_unregister_hook(&nfho);           /*Unregister netfilter hook structure */
	pr_debug("udp_packet_counter unloaded\n");
}

module_init(udpCounter_init);
module_exit(udpCounter_exit);


MODULE_AUTHOR("shyam saini");
MODULE_DESCRIPTION("Module for counting  UDP packets");
MODULE_LICENSE("GPL");
