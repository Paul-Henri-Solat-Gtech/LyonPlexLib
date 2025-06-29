#include "pch.h"
#include "Player.h"

#include "playerAction.h"
#include "playerCondition.h"

Player::Player() : m_stateMachine(this, State::Count)
{
    // --- IDLE ---
    {
        auto* sIdle = m_stateMachine.CreateBehaviour(State::Idle);
        sIdle->AddAction(new PlayerAction_Idle());
        //-> MOVE TRANSITION
        {
            auto transition = sIdle->CreateTransition(State::Move);
            auto condition = transition->AddCondition<PlayerCondition_IsMoving>();
        }
    }

    // --- MOVE ---
    {
        auto* sMove = m_stateMachine.CreateBehaviour(State::Move);
        sMove->AddAction(new PlayerAction_Move());
        //-> IDLE TRANSITION
        {
            auto transition = sMove->CreateTransition(State::Idle);
            auto condition = transition->AddCondition<PlayerCondition_IsNotMoving>();
        }
    }

    // --- JUMP ---
    {
        auto* b = m_stateMachine.CreateBehaviour(State::Jump);
        b->AddAction(new PlayerAction_Jump());
        // Åc
    }

    // Vous pouvez maintenant faire :
    m_stateMachine.SetState(State::Idle);
}

void Player::Init(GameObject gameObject)
{
	m_playerGameObject = gameObject;
    m_moveSpeed = m_walkSpeed;

    m_deltatime = 0;

	OutputDebugStringA("\nINIT PLAYER REUSSI !\n");

	//m_stateMachine.SetState(State::Idle);
}

const char* Player::GetStateName(State state) const
{
	switch (state)
	{
	case Idle: return "Idle";
	case Move: return "Move";
	case Jump: return "Jump";
	default: return "Unknown";
	}
}

const char* Player::GetCurrentStateName() const
{
    int state = m_stateMachine.GetCurrentState();
    return GetStateName(static_cast<State>(state));
}

void Player::OnUdpdate(float deltatime)
{
	m_stateMachine.Update();
    m_deltatime = deltatime;
}
