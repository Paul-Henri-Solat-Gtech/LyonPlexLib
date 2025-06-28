#include "pch.h"
#include "Player.h"

Player::Player() : m_StateMachine(this, State::Count)
{
	// IDLE
	//{
	//	Behaviour<Plant>*pIdle = mStateMachine.CreateBehaviour(State::Idle);
	//	pIdle->AddAction(new PlantAction_Idle());

	//	//-> SHOOTING
	//	{
	//		auto transition = pIdle->CreateTransition(State::Shooting);

	//		auto condition = transition->AddCondition<PlantCondition_ZombieOnLane>();
	//	}

	//	//-> RELOADING
	//	{
	//		auto transition = pIdle->CreateTransition(State::Reloading);

	//		auto condition1 = transition->AddCondition<PlantCondition_FullAmmo>();
	//		condition1->expected = false;

	//		auto condition2 = transition->AddCondition<PlantCondition_ZombieOnLane>();
	//		condition2->expected = false;
	//	}
	//}

	//	//SHOOTING
	//{
	//	Behaviour<Plant>* pShooting = mStateMachine.CreateBehaviour(State::Shooting);
	//	pShooting->AddAction(new PlantAction_Shooting());

	//	//-> IDLE
	//	{
	//		auto transition = pShooting->CreateTransition(State::Idle);

	//		auto condition = transition->AddCondition<PlantCondition_ZombieOnLane>();
	//		condition->expected = false;
	//	}

	//	//-> RELOADING
	//	{
	//		auto transition = pShooting->CreateTransition(State::Reloading);

	//		transition->AddCondition<PlantCondition_NoAmmo>();
	//	}
	//}

	////RELOADING
	//{
	//	Behaviour<Plant>* pShooting = mStateMachine.CreateBehaviour(State::Reloading);
	//	pShooting->AddAction(new PlantAction_Reloading());

	//	//-> IDLE
	//	{
	//		auto transition = pShooting->CreateTransition(State::Idle);

	//		auto condition = transition->AddCondition<PlantCondition_FullAmmo>();
	//	}
	//}

	//m_StateMachine.SetState(State::Idle);
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
