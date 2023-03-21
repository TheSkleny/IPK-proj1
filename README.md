# IPK project 1 2022/2023

# Requirements
- g++
- make

# Build and usage
```
make
./ipkcpc -h <host> -p <port> -m <mode[tcp|udp]>
```
- ```host``` is IPv4 server address
- ```port``` is number of port on the server
- ```mode``` is either _udp_ or _tcp_

__Server__ then takes input from user and responds with result or error mesage, based on ```mode``` and user input

### TCP communication
Input:
```bash
HELLO
SOLVE (+ 1 2)
BYE
```
Output:
```bash
HELLO
RESULT 3
BYE
```

### UDP communication
Input:
```bash
(+ 1 2)
(a b)
```
Output:
```bash
OK:3
ERR:<error message>
```

# Testing

Testing was done manually, by sending some examples of input to the server and checking right response.

### Environment
- Windows subsystem for Linux (Ubuntu) version 1.1.3.0 - the project was developed in this environment on local machine
- VirtualBox version 7.0.6 - this software was used for hosting the reference VM with ipkpd server
- Wireshark version 4.0.4 - used for packet catching, mainly at UDP implementation

### Network settings in VirtualBox

At first, the VM was set to Bridged adapter mode, because it was the easiest (and the most familiar way) for me. But later, because I wanted to use Wireshark to capture UDP packets, I changed the VM to VirtualBox host-only mode and finished project with that.


# References
[1] Vladimir Vesely DemoTcp [online]. Publisher: Brno University of Technology, Faculty of Information Technology, January 30th 2023. [cit. 2023-03-02]. Available at: https://git.fit.vutbr.cz/NESFIT/IPK-Projekty/src/branch/master/Stubs/cpp/DemoTcp.

[2] Vladimir Vesely DemoUdp [online]. Publisher: Brno University of Technology, Faculty of Information Technology, January 30th 2023. [cit. 2023-03-02]. Available at: https://git.fit.vutbr.cz/NESFIT/IPK-Projekty/src/branch/master/Stubs/cpp/DemoUdp.

[3] Vladimir Vesely IPK Project 1 [online]. Publisher: Brno University of Technology, Faculty of Information Technology, January 30th 2023. [cit. 2023-03-02]. Available at: https://git.fit.vutbr.cz/NESFIT/IPK-Projekty/src/branch/master/Project%201.

[4] Vladimir Vesely IPK CALCULATOR PROTOCOL [online]. Publisher: Brno University of Technology, Faculty of Information Technology, January 30th 2023. [cit. 2023-03-02]. Available at: https://git.fit.vutbr.cz/NESFIT/IPK-Projekty/src/branch/master/Project%201/Protocol.md.

[5] https://www.rfc-editor.org/info/std68

and countless pages of stackoverflow questions...