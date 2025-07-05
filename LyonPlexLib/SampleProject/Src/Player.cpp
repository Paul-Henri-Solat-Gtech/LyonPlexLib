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
            //transition->AddCondition<PlayerCondition_IsAttacking>();
        }
        //-> ATTACK TRANSITION
        {
            auto transition = sIdle->CreateTransition(State::Attack);
            auto condition = transition->AddCondition<PlayerCondition_IsAttacking>();
        }
        //-> FALL TRANSITION
        {
            auto transition = sIdle->CreateTransition(State::Fall);
            auto condition = transition->AddCondition<PlayerCondition_IsInTheAir>();
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
        //-> ATTACK TRANSITION
        {
            auto transition = sMove->CreateTransition(State::Attack);
            auto condition = transition->AddCondition<PlayerCondition_IsAttacking>();
        }
        //-> FALL TRANSITION
        {
            auto transition = sMove->CreateTransition(State::Fall);
            auto condition = transition->AddCondition<PlayerCondition_IsInTheAir>();
        }
    }

    // --- JUMP ---
    {
        auto* sJump = m_stateMachine.CreateBehaviour(State::Jump);
        sJump->AddAction(new PlayerAction_Jump());
    }
    
    // --- FALL ---
    {
        auto* sFall = m_stateMachine.CreateBehaviour(State::Fall);
        sFall->AddAction(new PlayerAction_Fall());
        //-> IDLE TRANSITION
        {
            auto transition = sFall->CreateTransition(State::Idle);
            auto condition = transition->AddCondition<PlayerCondition_IsNotMoving>();
        }
        //-> MOVE TRANSITION
        {
            auto transition = sFall->CreateTransition(State::Move);
            auto condition = transition->AddCondition<PlayerCondition_IsMoving>();
        }
    }

    // --- Attack ---
    {
        auto* sAttack = m_stateMachine.CreateBehaviour(State::Attack);
        sAttack->AddAction(new PlayerAction_Attack());
        //-> IDLE TRANSITION
        {
            auto transition = sAttack->CreateTransition(State::Idle);
            auto condition = transition->AddCondition<PlayerCondition_IsNotMoving>();
        }
        //-> MOVE TRANSITION
        {
            auto transition = sAttack->CreateTransition(State::Move);
            auto condition = transition->AddCondition<PlayerCondition_IsMoving>();
        }
        //-> FALL TRANSITION
        {
            auto transition = sAttack->CreateTransition(State::Fall);
            auto condition = transition->AddCondition<PlayerCondition_IsInTheAir>();
        }
    }


    // Base State
    m_stateMachine.SetState(State::Idle);
}

void Player::Init(GameObject gameObject)
{
	m_playerGameObject = gameObject;
    m_moveSpeed = m_walkSpeed;

    m_deltatime = 0;

	OutputDebugStringA("\nINIT PLAYER REUSSI !\n");

    //AnimationManager newAnim;

    m_testAnimation.Init(2.f, &m_playerArm);
    m_testAnimation.AddFrame(TEXTURES::bras);
    m_testAnimation.AddFrame(TEXTURES::test);
    m_testAnimation.AddFrame(TEXTURES::tex0);

}

const char* Player::GetStateName(State state) const
{
	switch (state)
	{
	case Idle: return "Idle";
	case Move: return "Move";
    case Jump: return "Jump";
    case Attack: return "Attack";
    case Fall: return "Fall";
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
    m_testAnimation.Update(deltatime);
}
