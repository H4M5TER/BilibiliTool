// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include "windows.h"

#include "BilibiliStruct.h"

#include "base64.h"
#include "httpex.h"
#include "sslex.h"
#include "toollib/md5.h"
#include "toollib/socketsc.h"
#include "toollib/strconvert.h"
using namespace toollib;
#ifdef _DEBUG
#pragma comment(lib,"toollibd.lib")  
#else
#pragma comment(lib,"toollib.lib") 
#endif

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/encodings.h"
#include "rapidjson/filereadstream.h"   // FileReadStream
#include "rapidjson/encodedstream.h"    // AutoUTFInputStream

