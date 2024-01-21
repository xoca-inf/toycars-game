#pragma once

#include "W4Framework.h"
#include "Transport.h"

W4_USE_UNSTRICT_INTERFACE

class Inventory
{
public:
    static Inventory &instance() {
        static Inventory instance;
        return instance;
    }

    Inventory();
    virtual ~Inventory()= default;

    int getPoints() const;
    void setPoints(int count);
    void addPoints(int count);
    void spendPoints(int count);

    int getOpened() const;
    void setOpened(int count);
    void incOpened();

    int getPassed() const;
    void setPassed(int count);
    void incPassed();

    sptr<Transport> getCurrentCar() const;
    void setCurrentCar(sptr<Transport> transport);

    int getCanisterLVL() const;
    void setCanisterLVL(int count);
    void incCanisterLVL();

    int getEngineLVL() const;
    void setEngineLVL(int count);
    void incEngineLVL();

    float getNeededDistance() const;
    void setNeededDistance(float value);


    float getPassedDistance() const;
    void setPassedDistance(float value);

private:
    int m_points = 0;
    int m_opened_count = 0;
    int m_passed_count = 0;
    sptr<Transport> m_current_car = nullptr;
    int m_canister_lvl = 0;
    int m_engine_lvl = 0;
    float m_neededDistance;
    float m_passedDistance;
};
