# DISCLAIMER
The BOF is currently only compatible with the latest version of TrustedSec's COFFLoader. Please read their [blog](https://www.trustedsec.com/blog/using-rpc-in-bofs/) for the details.

# ShadowRDP
This repository contains two applications. One is a beacon object file, which is used to retrieve the authentication string, also known as the invitation. The other is a graphical user interface program that can be run on the operator's system behind a SOCKS proxy to connect to the remote desktop session.

## BOF Usage
```
shadowrdp <HOSTNAME> [<control>|<view>] <SESSIONID>
```

# Resources
[Using RPC in BOFs](https://www.trustedsec.com/blog/using-rpc-in-bofs/)

[ShadowRDP client](http://www.rohitab.com/discuss/topic/41626-rdp-com-server-client/)

[MS-TSTS protocol documentation](https://winprotocoldoc.blob.core.windows.net/productionwindowsarchives/MS-TSTS/%5BMS-TSTS%5D.pdf)

[MS-RAI protocol documentation](https://winprotocoldoc.blob.core.windows.net/productionwindowsarchives/MS-RAI/%5bMS-RAI%5d.pdf)
