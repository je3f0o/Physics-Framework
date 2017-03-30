#pragma once
#include <glm/vec3.hpp>
#include <glm/mat3x3.hpp>
#include "Component.h"

class Physics : public Component
{
public:
	/* -------- VARIABLES ---------- */
	struct Derivative
	{
		glm::vec3 mDerivedVelocity;
		glm::vec3 mDerivedAcceleration;
		Derivative()
		{
			mDerivedAcceleration= glm::vec3();
			mDerivedVelocity = glm::vec3();
		}
	};
	glm::vec3 NextPosition = glm::vec3();
	glm::vec3 CurrentPosition = glm::vec3();
	glm::vec3 PreviousPosition = glm::vec3();

	glm::vec3 LinearVelocity = glm::vec3();
	glm::vec3 AngularVelocity = glm::vec3();

	glm::vec3 Force = glm::vec3();
	glm::vec3 Torque = glm::vec3();

	float Mass = 100.0f;
	float InverseMass = 1.0f/Mass;
	glm::mat3 InertiaTensor = glm::mat3(1);
	glm::mat3 InverseInertiaTensor = glm::mat3(1);
	/* -------- FUNCTIONS ---------- */
	
	Physics() : Component(Component::PHYSICS)
	{}
	~Physics() {}
	
	static inline Component::ComponentType GetComponentID() { return (ComponentType::PHYSICS); }
	static inline const char * GetComponentName() { return ComponentTypeName[ComponentType::PHYSICS]; }

	// GETTERS
	inline float GetMass() { return Mass; }
	inline glm::vec3 GetCurrentPosition() { return CurrentPosition; }
	inline glm::vec3 GetVelocity() { return LinearVelocity; }
	// SETTERS
	inline void SetMass(float mass) { Mass = mass; InverseMass = 1 / Mass; }
	inline void SetCurrentPosition(glm::vec3 position) { CurrentPosition = position; }
	inline void SetNextPosition(glm::vec3 position) { NextPosition = position; }
	inline void ApplyForce(glm::vec3 newForce) { Force += newForce; }

	virtual void Update() override {}
	virtual void Deserialize(TextFileData aTextFileData) override {};
	
	// Used at start of frame to sync physics with transforms (for updates from editor)
	void SyncPhysicsWithTransform();
	// Used at end of frame to sync transform to updated physics values
	void UpdateTransform();

	void IntegrateRK4(float totalTime, float dt);
	Derivative Evaluate(float t, float dt, const Derivative &);

	void IntegrateExplicitEuler(float dt);
	void IntegratePositionVerlet(float dt);
};