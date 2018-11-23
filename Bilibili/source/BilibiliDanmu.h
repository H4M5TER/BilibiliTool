﻿/*
弹幕协议说明
协议头一般为16位规则如下
 0- 3 总长度
 4- 5 头部长度(0x0010)
 6- 7 版本 客户端版本目前为1 
 8-11 数据类型 3为在线人数 5为JSON数据 8为连接成功
12-15 设备 socket为0 flash为1
*/

#pragma once
#include <fstream>
#include <deque>
#include "tcpio/socketsc.h"
#include "source/source_base.h"

class CBilibiliDanmu:
	public source_base,
	public CIOCPClient {
public:
	CBilibiliDanmu();
	~CBilibiliDanmu();

// 重载CIOCPClient中的函数
protected:
	int OnClose(PER_SOCKET_CONTEXT* pSocketContext) override;
	int OnReceive(PER_SOCKET_CONTEXT* pSocketContext, PER_IO_CONTEXT* pIoContext, int byteslen) override;
	int OnHeart() override;

public:
	// 开启主监视线程 初始化IOCP类
	int start() override;
	// 退出所有线程 断开Socket 释放所有IOCP资源
	int stop() override;
	// 连接一个房间 在心跳线程中连接
	int add_context(const unsigned id, const ROOM_INFO& info) override;
	// 断开特定房间
	int del_context(const unsigned id) override;
	// 更新房间
	int update_context(std::set<unsigned> &nlist, const unsigned opt) override;
	// 显示当前连接数
	void show_stat() override;

private:
	long long GetRUID();
	int CheckMessage(const unsigned char *str);
	int MakeConnectionInfo(unsigned char* str, int len, int room);
	int MakeHeartInfo(unsigned char* str, int len, int room);
	int SendConnectionInfo(int room);

private:
	bool _isworking;
	// 需要重连的房间列表
	std::deque<int> m_list_reconnect;
	// 正在主动关闭的房间
	std::set<unsigned> m_list_closing;
};