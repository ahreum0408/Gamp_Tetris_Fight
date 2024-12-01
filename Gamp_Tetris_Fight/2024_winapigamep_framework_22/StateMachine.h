#pragma once
class BaseState;

template <typename T>
class StateMachine {
public:
    StateMachine(T* owner) : m_owner(owner), m_currentState(nullptr) {}
    ~StateMachine() { ChangeState(nullptr); }

    void Update() {
        if (m_currentState) {
            m_currentState->Update(m_owner);
        }
    }

    void ChangeState(BaseState* newState) {
        if (m_currentState) {
            m_currentState->Exit(m_owner);
            delete m_currentState; // ���� ���� ����
        }
        m_currentState = newState;
        if (m_currentState) {
            m_currentState->Enter(m_owner);
        }
    }

private:
    T* m_owner;              // ���¸� ������ ��ü
    BaseState* m_currentState; // ���� ����
};