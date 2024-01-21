#include "Inventory.h"
#include "Settings/Settings.h"
#include "Transport.h"

Inventory::Inventory() {
    W4_LOG_DEBUG("[INVENTORY] called constructor");
}

int Inventory::getPoints() const {
    return m_points;
}

void Inventory::setPoints(int count) {
    m_points = count;
    W4_LOG_DEBUG("[INVENTORY] set points to %d", m_points);
}

void Inventory::addPoints(int count) {
    setPoints(m_points + count);
}

void Inventory::spendPoints(int count) {
    setPoints(m_points - count);
}

int Inventory::getOpened() const {
    return m_opened_count;
}

void Inventory::setOpened(int count) {
    m_opened_count = count;
    W4_LOG_DEBUG("[INVENTORY] OPENED count set to %d", m_opened_count);
}

void Inventory::incOpened() {
    setOpened(m_opened_count + 1);
}

int Inventory::getPassed() const {
    return m_passed_count;
}

void Inventory::setPassed(int count) {
    m_passed_count = count;
    W4_LOG_DEBUG("[INVENTORY] PASSED set to %d", m_passed_count);
}

void Inventory::incPassed() {
    setPassed(m_passed_count + 1);
}

sptr<Transport> Inventory::getCurrentCar() const {
    return m_current_car;
}

void Inventory::setCurrentCar(sptr<Transport> transport) {
    m_current_car = transport;
    W4_LOG_DEBUG("[INVENTORY] CURRENT Car set to %s", m_current_car->getAtlasResource().c_str());
}

int Inventory::getCanisterLVL() const {
    return m_canister_lvl;
}

void Inventory::setCanisterLVL(int count) {
    m_canister_lvl = count;
    W4_LOG_DEBUG("[INVENTORY] canister level set to %d", m_canister_lvl);
}

void Inventory::incCanisterLVL() {
    setCanisterLVL(m_canister_lvl + 1);
}

int Inventory::getEngineLVL() const {
    return m_engine_lvl;
}

void Inventory::setEngineLVL(int count) {
    m_engine_lvl = count;
    W4_LOG_DEBUG("[INVENTORY] ENGINE LVL set to %d", m_engine_lvl);
}

void Inventory::incEngineLVL() {
    setEngineLVL(m_engine_lvl + 1);
}

float Inventory::getNeededDistance() const {
    return m_neededDistance;
}

void Inventory::setNeededDistance(float value) {
    m_neededDistance = value;
    W4_LOG_DEBUG("[INVENTORY] Needed Distance set to %d", m_neededDistance);
}

float Inventory::getPassedDistance() const {
    return m_passedDistance;
}

void Inventory::setPassedDistance(float value) {
    m_passedDistance = value;
}
