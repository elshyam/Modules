I have used [**netfilters hooks**](https://en.wikipedia.org/wiki/Netfilter) to capture the packets.

Here, netfilters capture [**sk_buff**](http://vger.kernel.org/~davem/skb_data.html) also known as socket buffer. Socket buffer is the most basic entity of linux kernel Network Stack.

Then from sk_buff, ipheader is extracted.

following screenshots taken from [Rami Rosen Linux Kernel Networking Book](http://www.apress.com/us/book/9781430261964) shows the packet flow.

![alt tag](https://github.com/mysticTot/Modules/blob/master/sending-ipv4-packets.png)
![alt tag](https://github.com/mysticTot/Modules/blob/master/receiving-ipv4-packets.png)

Look at **NF_INET_PRE_ROUTING**, **NF_INET_LOCAL_IN**, **NF_INET_FORWARD**, **NF_INET_POST_ROUTING**, and **NF_INET_LOCAL_OUT**  entry points of the netfilter hooks in the above screenshots.

NF_INET_PRE_ROUTING  :- It is the first hook point that all incoming packets reach.

NF_INET_LOCAL_IN     :- All incoming packets addressed to the local host reach this hook.

NF_INET_FORWARD      :- All forwarded packets reach this hook point.

NF_INET_POST_ROUTING :- Packets that are forwarded reach this hook point after passing the NF_INET_FORWARD hook point.

NF_INET_LOCAL_OUT    :- All outgoing packets that were created on the local host reach this point before reaching the 
                        NF_INET_POST_ROUTING hook point.
