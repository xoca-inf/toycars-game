#include "PhysicsSimulation.h"
#include "Settings.h"

PhysicsSimulation::PhysicsSimulation() {
    m_phisSim = make::sptr<physics::Simulator>(500, 10, 0, Settings::instance().getVec3("Gravity"));
    w4::physics::SimulatorCollector::addSimulator(m_phisSim);
    W4_LOG_DEBUG("[Physics Simulation] Created");
}

PhysicsSimulation::~PhysicsSimulation() {}
