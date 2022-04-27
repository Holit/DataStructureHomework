//defs.h
//���ļ������˴󲿷�Ԥ�����ֵ
#ifndef __DEF_H__
#define __DEF_H__
#pragma once
#include <corecrt_malloc.h>
#include <cstdlib>
#include <cstdio>
#include <type_traits>

typedef int Status;//���ڴ洢״̬
#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef OK
#define OK 1
#endif

#ifndef ERROR
#define ERROR 0
#endif
//����������
#ifndef INFEASIBLE
#define INFEASIBLE -1
#endif

#ifndef OVERFLOW
#define OVERFLOW -2
#else
#pragma once
#pragma message("defs.h(30,1) OVERFLOW�����Ѿ�������")
#endif

#ifndef UNKNOWNERROR
#define UNKNOWNERROR -5
#endif

#ifndef _In
#define _In
#endif // !_In

#ifndef _Out
#define _Out
#endif
#endif //!__DEF_H__