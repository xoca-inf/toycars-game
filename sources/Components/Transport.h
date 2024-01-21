//
// Created by tima on 13.10.2021.
//
#pragma once

#include "W4Framework.h"
#include "W4JSON.h"

W4_USE_UNSTRICT_INTERFACE

class Transport
{
public:
    Transport(float startSpeed, const vec3 &vehicleSize, const std::string &modelResource,
              const std::string &atlasResource);
    ~Transport() = default;

    static sptr<Transport> createCar(const int id);

    sptr<Asset> getAsset();
    sptr<Texture> getTexture();

    float getStartSpeed();
    void setStartSpeed(float startSpeed);

    vec3 getVehicleSize();
    void setVehicleSize(vec3 vehicleSize);

    std::string getModelResource();
    void setModelResource(std::string modelResource);

    std::string getAtlasResource();
    void setAtlasResource(std::string atlasResources);
private:
    static sptr<Transport> getCar(const int id);

    float m_startSpeed;
    vec3 m_VehicleSize;
    std::string m_modelResource;
    std::string m_atlasResource;
};