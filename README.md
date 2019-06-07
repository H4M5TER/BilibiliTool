# BilibiliTool

Bilibili直播站小工具 

模式12使用wss协议(websocketpp)连接弹幕服务器，监控5个房间。

模式13使用tcp协议(boost asio)连接弹幕服务器，经测试，网络条件允许时，1800个房间没问题。



说心里话，这样一个号一天捡捡低保也不会消耗贵站多少资源，我们领低保也很开心，然后出了活动还会怀着感恩的心氪一单两单。何况，比起进进出出各个房间领低保，专心看主播看内容的在线时长会更可观。我们有了喜欢的主播，也不会忍心让他们没饭吃。

以前进一次小黑屋一天就出来了，这样吃一天饿一天，我们忍忍也就过去了。后来慢慢变成3天，7天，吃一顿要饿好久。我们都快饿死了。

求求你了，给我们留点口粮，不要这么赶尽杀绝，拜谢。

**每次都是领一天就进去，我就一个号呀，这下连活动任务都做不了了。**



## Features  

**程序**  

- Bilibili 为助手主程序  
- ToolConfig 为配置程序(只能配置已登录用户)  

**目前实现的功能**  

- 7 账户cookie有效性检测 **(在导入账号后必须执行)**  

- 8 信息查询

  背包道具查询

  扭蛋币查询  

- 11 挂机相关 

  经验

  签到

  银瓜子任务

  每日礼物领取

  银瓜子换硬币

  ~~主站登录奖励硬币(方案失效)~~

- 12 全区或分区广播事件

  小电视API抽奖(包括摩天大楼，小金人) 

  总督上船低保

- 13 无广播事件

  节奏风暴

  舰长以及提督上船低保



**相关说明**   

- 在导入账号后需要使用功能(7)查询账户有效性后该账户才能执行其它操作。  
- 添加账户后默认开启所有功能，可以通过配置程序修改。  
- 当检测到账号被封禁时会立即停止该账号的所有活动。  
- 挂机与参与抽奖两个功能目前不能同时开启，如有需要可以开启两份软件。  
- 在参与抽奖时设置有延时，多账号情况下两次领取间也存在1到2秒的延时。延时数值目前无法通过配置文件修改。  
- 参与活动抽奖时能够过滤不可进入的房间，避免钓鱼。  



**别人家的资料库**

- 樱花助手上船数据查询：[点我](https://list.bilibili.wiki/)



## Build and Usage

### 文件组织结构

```
source dir
├── README
├── CMakelists.txt (cmake配置文件)
├── cmake/ (cmake插件)
├── doc/
├── Bilibili/ (主程序)
├── ToolConfig/ (配置修改程序)
└── LotteryHistory/ (历史记录) 

build dir
├── bin/ (生成目录)
└── install/ (安装目录) 
```



### 依赖库  

- boost  
- curl  
- openssl  
- rapidjson  
- websocketpp(需要做一些修改)
- zlib

依赖库的编译参考[doc/lib-build.md](doc/lib-build.md)

**[重要]WSS相关内容参考[doc/notes-wss.md](doc/notes-wss.md)**



### 项目配置  

使用Cmake配置依赖库，定义下述变量：

* `BOOST_ROOT`：boost库的根目录，静态链接
* `libcurl`库的相关变量，动态链接
  * `CURL_INCLUDE_DIR`：头文件所在文件夹
  * `CURL_LIBRARY_RELEASE`：库文件路径
  * `CURL_DLL`：DLL文件路径
* `OPENSSL_ROOT_DIR`：OpenSSL安装目录，动态链接
* `RapidJSON_ROOT`：RapidJSON头文件所在文件夹
* `WebsocketPP_ROOT`：WebsocketPP头文件所在文件夹
* `ZLIB_ROOT`：ZLIB安装目录，动态链接

输出目录可以选择其它文件夹，不建议使用当前文件夹。

编译器建议使用VS2017，由于插件`WebsocketPP`目前不支持`Boost 1.70.0`，目前无法使用VS2019。

按照提示一步步添加路径，然后生成解决方案。

先执行`ALL_BUILD`，然后执行`INSTALL`，这时程序以及所需的DLL会被拷贝至`install/bin`文件夹，如果库文件的路径没有问题。



## TODO

- 添加验证码识别领取瓜子(识别部分就不用C写了 是个大工程 有生之年)



## License

本项目采用MIT开源协议  



## Thanks

感谢以下大佬贡献的代码： 

[Military-Doctor](https://github.com/Military-Doctor/Bilibili/) 

[Dawnnnnnn](https://github.com/Dawnnnnnn/bilibili-live-tools/)  

