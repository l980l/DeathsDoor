#include "pch.h"

#include "CThread.h"
#include "CSync.h"

CThread::CThread() :
    m_Loop(false),
    m_Suspend(false)
{
}

CThread::~CThread()
{
    //Stop();

    DeleteCriticalSection(&m_CRT);
}

//������ �Ͻ�����
void CThread::Suspend()
{
    CSync   sync(&m_CRT);

    // ���������� suspend count�� ���� �ִµ�, SuspendThread()�� ȣ���ϸ� 1 ����. ResumeThread()�� �ϸ� 1 ����. 0�� �Ǿ������ ������� ��. 
    SuspendThread(m_Thread);

    m_Suspend = true;
}

// ������ �����
void CThread::Resume()
{
    CSync   sync(&m_CRT);

    DWORD Count = ResumeThread(m_Thread);

    if (Count > 0)
        m_Suspend = false;
}

// Suspend Count�� 0�� �ɶ����� ResumeThread�� ȣ���Ͽ� ������ ����� �����ִ� �Լ�.
void CThread::ReStart()
{
    CSync   sync(&m_CRT);

    DWORD   Count = 0;

    do
    {
        Count = ResumeThread(m_Thread);
    } while (Count > 0);

    m_Suspend = false;
}

void CThread::Stop()
{
    if (m_Thread)
    {
        m_Loop = false;
        Start();
        ReStart();

        // �����尡 ����ɶ����� ��ٸ���.
        WaitForSingleObject(m_Thread, INFINITE);
        CloseHandle(m_Thread);
        m_Thread = 0;
    }
}

void CThread::Start()
{
    SetEvent(m_StartEvent);
}

bool CThread::Init()
{
    m_StartEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);

    InitializeCriticalSection(&m_CRT);

    m_Thread = (HANDLE)_beginthreadex(nullptr, 0, CThread::ThreadFunction,
        (void*)this, 0, nullptr);

    return true;
}

unsigned int __stdcall CThread::ThreadFunction(void* Arg)
{
    CThread* Thread = (CThread*)Arg;

    // ������ ��ü
    WaitForSingleObject(Thread->m_StartEvent, INFINITE);

    do
    {
        Thread->Run();
    } while (Thread->m_Loop);

    return 0;
}
