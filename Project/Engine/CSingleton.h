#pragma once

using EXIT = void(*)(void);

template <typename T>
class CSingleton
{
    static T* m_Inst;

public:
    static T*   GetInst();
    static void Destroy();

protected:
    CSingleton()
    {
    }

    virtual ~CSingleton()
    {
    }
};

template <typename T>
T* CSingleton<T>::m_Inst = nullptr;

template <typename T>
T* CSingleton<T>::GetInst()
{
    if (nullptr == m_Inst)
    {
        m_Inst = new T;
        atexit(&CSingleton<T>::Destroy);
    }

    return m_Inst;
}

template <typename T>
void CSingleton<T>::Destroy()
{
    if (nullptr != m_Inst)
    {
        delete m_Inst;
        m_Inst = nullptr;
    }
}
