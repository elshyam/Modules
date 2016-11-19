I have used netfilters to capture the packets.

Here, netfilters capture sk_buff also known as socket buffer. Socket buffer is the most basic entity of linux kernel Network Stack.

Then from sk_buff, ipheader is extracted.

following screenshots taken from [Rami Rosen Linux Kernel Networking Book](http://www.apress.com/us/book/9781430261964) shows the packet flow.

![alt tag](https://github.com/mysticTot/Modules/blob/master/sending-ipv4-packets.png)
![alt tag](https://github.com/mysticTot/Modules/blob/master/receiving-ipv4-packets.png)
