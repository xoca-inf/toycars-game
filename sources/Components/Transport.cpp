//
// Created by tima on 13.10.2021.
//

#include "Transport.h"

float Transport::getStartSpeed() {
    return this->m_startSpeed;
}

void Transport::setStartSpeed(float startSpeed) {
    this->m_startSpeed = startSpeed;
}

vec3 Transport::getVehicleSize() {
    return this->m_VehicleSize;
}

void Transport::setVehicleSize(vec3 vehicleSize) {
    this->m_VehicleSize = vehicleSize;
}

std::string Transport::getModelResource() {
    return this->m_modelResource;
}

void Transport::setModelResource(std::string modelResource) {
    this->m_modelResource = modelResource;
}

std::string Transport::getAtlasResource() {
    return this->m_atlasResource;
}

void Transport::setAtlasResource(std::string atlasResources) {
    this->m_atlasResource = atlasResources;
}

Transport::Transport(float startSpeed, const vec3 &vehicleSize, const std::string &modelResource,
                     const std::string &atlasResource) : m_startSpeed(startSpeed), m_VehicleSize(vehicleSize),
                                                         m_modelResource(modelResource), m_atlasResource(atlasResource) {}

sptr<Transport> Transport::getCar(const int id) {
    auto file = w4::filesystem::open("carResources.json");
    auto json = nlohmann::json::parse(file->data(), file->data() + file->size());

    float startSpeed = json["Cars"][id]["startSpeed"];
    vec3 vehicleSize = json["Cars"][id]["vehicleSize"];
    std::string atlas = json["Cars"][id]["texture"];
    std::string model = json["Cars"][id]["model"];
    auto car = make::sptr<Transport>(startSpeed, vehicleSize, model, atlas);
    return car;
}

sptr<Transport> Transport::createCar(const int id) {
    return Transport::getCar(id);
}

sptr<Asset> Transport::getAsset() {
    return Asset::get(m_modelResource);
}

sptr<Texture> Transport::getTexture() {
    return Texture::get(m_atlasResource);
}
