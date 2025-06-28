#include "pch.h"
#include "Player.h"

#include "playerAction.h"
#include "playerCondition.h"

Player::Player() : m_stateMachine(this, State::Count)
{
    // --- IDLE ---
    {
        auto* b = m_stateMachine.CreateBehaviour(State::Idle);
        b->AddAction(new PlayerAction_Idle());
        // si vous avez des transitions, ajoutez-les ici :
        // auto* t = b->CreateTransition(State::Move);
        // t->AddCondition<PlayerCondition_Some>();
    }

    // --- MOVE ---
    {
        auto* b = m_stateMachine.CreateBehaviour(State::Move);
        b->AddAction(new PlayerAction_Move());
        // Åc
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

void Player::OnUdpdate()
{
	//m_stateMachine.Update();
}
