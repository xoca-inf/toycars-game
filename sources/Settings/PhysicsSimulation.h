#include "W4Framework.h"

W4_USE_UNSTRICT_INTERFACE

class PhysicsSimulation {
public:
    static PhysicsSimulation& instance() {
        static PhysicsSimulation instance;
        return instance;
    }

    PhysicsSimulation();
    virtual ~PhysicsSimulation();

    sptr<physics::Simulator> getSimulator() { return m_phisSim; }
private:
    sptr<physics::Simulator> m_phisSim;
};
