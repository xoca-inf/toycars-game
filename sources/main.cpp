#include "W4Framework.h"

#include "Components/CameraMovementComponent.h"
#include "Components/SceneComponent.h"
#include "Components/TestPhysicsComponent.h"
#include "Components/UiLayoutComponent.h"
#include "Components/AccelerationComponent.h"
#include "Components/Inventory.h"
#include "Components/LevelProgressComponent.h"
#include "Components/ShopComponent.h"
#include "FOV/AdaptiveFov.h"
#include "Settings/Config.h"
#include "Settings/ResourceLibary.h"
#include "Settings/Settings.h"
#include "Components/Transport.h"
#include "gameUi/MainMenuUi.h"
#include "gameUi/VehicleSelectUi.h"
#include "gameUi/InGameUi.h"
#include "gameUi/CoinsPanelUi.h"

W4_USE_UNSTRICT_INTERFACE

static std::string TC_MENU = "MainMenu";
static std::string TC_VEHICLE_SELECT = "VehicleSelect";
static std::string TC_SETTINGS = "Settings";
static std::string TC_HIGHSCORES = "HighScores";
static std::string TC_SHOP = "Shop";
static std::string TC_GAME = "Game";
static std::string TC_RESULT = "Result";
static std::string TC_ADS = "Ads";
static std::string TC_LOADING = "Loading";

struct toyCarsApplication : public IGame
{
    void onConfig() override
    {
        Game::Config.StopUpdateWhenFocusLoss = false;
    }

    void onStart() override {
        W4_LOG_DEBUG("onStart");
        m_gameRoot = make::sptr<Node>("GameRoot");
        Render::getRoot()->addChild(m_gameRoot);
        m_camera = Render::getScreenCamera();
        m_cameraNode = make::sptr<Node>("CameraNode");
        m_cameraNode->setWorldTranslation(m_camera->getWorldTranslation());
        m_gameRoot->addChild(m_cameraNode);
        m_cameraNode->addChild(m_camera);

        Settings::instance();       // settings initialization here
        Inventory::instance();      // Inventory initialization
        ResourceLibary::instance(); // resource libary initialization here
        Inventory::instance().setCurrentCar(Transport::createCar(1));
        initializeShop();
        initializeUi();             // UI initialization here
        initializeFsm();            // FSM initialization here*


        m_touchEndHandler = Touch::End::subscribe(std::bind(
                &toyCarsApplication::onTouchEnd, this, std::placeholders::_1));

        // add lighting
        Render::getScreenCamera()->setClearColor(vec4(0.7f, 0.7f, 0.7f, 1));
        Render::getPass(0)->getDirectionalLight()->setColor(
                Settings::instance().getVec3("LightColor"));
        Render::getPass(0)->getDirectionalLight()->setDirection(
                Settings::instance().getVec3("LightDirection"));
        Render::getPass(0)->getDirectionalLight()->enableShadows(true);
        Render::getPass(0)->setDirectionalLightShadowMaxDistance(
                Settings::instance().getInt("ShadowMaxDistance"));
        Render::getPass(0)->setDirectionalLightShadowMapSize(
                Settings::instance().getInt("ShadowMapSize"));

        Inventory::instance().setCanisterLVL(3);
    }

    void onUpdate(float dt) override { m_fsm.update(dt); }

    void onResize(const math::size &newSize) override {
        Render::getScreenCamera()->setFov(
                games::benice::utils::AdaptiveFov::getAdaptiveFov(newSize));
	if(m_mainMenuUi) m_mainMenuUi->updateSize();
    if(m_vehicleSelectUi) m_vehicleSelectUi->updateSize();
    if(m_inGameUi) m_inGameUi->updateSize();
    if(m_coinsPanelUi) m_coinsPanelUi->updateSize();
        for (const auto &[key, ui]: m_uiCollection) {
            ui->getFirstComponent<UiLayoutComponent>().resize(newSize);
        }
    }

    void initializeShop() {
        m_shopNode = make::sptr<Node>("ShopNode");
        m_gameRoot->addChild(m_shopNode);
        m_shopNode->template addComponent<ShopComponent>();
    }

    void initializeUi() {
        m_cameraUi = make::sptr<Node>("CameraUI");
        m_cameraNode->addChild(m_cameraUi, false);

        // settings ui
        auto &settingsUI = addUi(TC_SETTINGS);
        settingsUI.getButton("BackButton")->setClickCallback([this]() {
            m_fsm.processEvent(FSM::Events::Back);
        });
        // shop ui
        auto &shopUI = addUi(TC_SHOP);
        shopUI.getButton("BackButton")->setClickCallback([this]() {
            m_fsm.processEvent(FSM::Events::Back);
        });
        shopUI.getButton("upEngineButton")->setClickCallback([this]() {
            m_shopNode->getFirstComponent<ShopComponent>().buyEngine();
        });
        shopUI.getButton("upFuelButton")->setClickCallback([this]() {
            m_shopNode->getFirstComponent<ShopComponent>().buyFuel();
        });
        shopUI.getButton("upPoints")->setClickCallback([this]() {
            m_shopNode->getFirstComponent<ShopComponent>().buyScoreBoost();
        });
        // highScores ui
        auto &highscoresUI = addUi(TC_HIGHSCORES);
        highscoresUI.getButton("BackButton")->setClickCallback([this]() {
            m_fsm.processEvent(FSM::Events::Back);
        });
        // vehicle select ui
//        auto &vehicleselectUI = addUi(TC_VEHICLE_SELECT);
//        vehicleselectUI.getButton("CarButton1")->setClickCallback([this]() {
//            Inventory::instance().setCurrentCar(Transport::createCar("car1"));
//        });
//        vehicleselectUI.getButton("CarButton2")->setClickCallback([this]() {
//            Inventory::instance().setCurrentCar(Transport::createCar("car2"));
//        });
//        vehicleselectUI.getButton("CarButton3")->setClickCallback([this]() {
//            Inventory::instance().setCurrentCar(Transport::createCar("car3"));
//        });
//        vehicleselectUI.getButton("CarButton4")->setClickCallback([this]() {
//            Inventory::instance().setCurrentCar(Transport::createCar("car4"));
//        });
//        vehicleselectUI.getButton("GameStartButton")->setClickCallback([this]() {
//            m_fsm.processEvent(FSM::Events::Start);
//        });
        // game ui!
        //auto &gameUI = addUi(TC_GAME);

        // result ui
        auto &resultUI = addUi(TC_RESULT);
        resultUI.getButton("MainMenuButton")->setClickCallback([this]() {
            m_fsm.processEvent(FSM::Events::Next);
        });

        // show main menu ui first
        switchUi(TC_MENU);

        m_shopNode->getFirstComponent<ShopComponent>().setup(m_cameraNode, shopUI);
        //m_cameraNode->addComponent<LevelProgressComponent>().setup(gameUI.getImage("ProgressBarInside"),
        //                                                           gameUI.getImage("ProgressBarCar"),
        //                                                           gameUI.getLabel("Score"));
    }

    UiLayoutComponent &addUi(const std::string &uiName) {
        auto node = make::sptr<Node>(uiName);
        node->setName(uiName);
        m_cameraUi->addChild(node);
        auto &uiComponent = node->addComponent<UiLayoutComponent>(uiName);
        m_uiCollection[uiName] = node;
        return uiComponent;
    }

    void switchUi(const std::string &uiName) {
        W4_LOG_DEBUG("[UI switched to] %s", uiName.c_str());
        for (const auto &[key, item]: m_uiCollection) {
            if (item->getName() != uiName) {
                item->getFirstComponent<UiLayoutComponent>().enable(false);
            } else
                item->getFirstComponent<UiLayoutComponent>().enable(true);
        }
    }

    void onEndGame() {
        auto &score = Inventory::instance();
        score.setPoints(score.getPoints() + score.getPassedDistance());
        score.setPassedDistance(0);
        m_fsm.processEvent(FSM::Events::Next);
    }

    void initializeFsm() {
        //*************************PRELOADING****************************************
        m_fsm.state<FSM::States::Preloading>().onEnterFunc = [&](auto &, auto &,
                                                                 auto &) {
            W4_LOG_INFO("Preloading onEnter");
            Timer::addTask(0.5, [this]() {
                m_fsm.processEvent(FSM::Events::Initialize);
                return true;
            });
        };
        m_fsm.state<FSM::States::Preloading>().onLeaveFunc =
                [&](auto &, auto &, auto &) { W4_LOG_INFO("Preloading onLeave"); };

        //*************************MAIN MENU***************************************
        m_fsm.state<FSM::States::MainMenu>().onEnterFunc = [&](auto &, auto &,
                                                               auto &) {
          W4_LOG_INFO("MainMenu onEnter");
            W4_LOG_DEBUG("CURREND CANISTER LEVEL: %d", Inventory::instance().getCanisterLVL());

            m_cameraNode->setWorldTranslation(vec3::zero);
          m_cameraNode->setWorldRotation(Rotator(0, 0, 0));
          m_mainMenuUi =
              make::sptr<MainMenuUi>(m_cameraNode, m_camera, 2.f, 0.f);
          m_mainMenuUi->init(false);
          m_mainMenuUi->setPlayPressedCallback(
              [this]() { m_fsm.processEvent(FSM::Events::Start); });
          m_mainMenuUi->setHighScoresPressedCallback(
              [this]() { m_fsm.processEvent(FSM::Events::HighScores); });
          m_mainMenuUi->setSettingsPressedCallback(
              [this]() { m_fsm.processEvent(FSM::Events::Settings); });
          m_mainMenuUi->setShopPressedCallback(
              [this]() { m_fsm.processEvent(FSM::Events::Shop); });
          m_coinsPanelUi = make::sptr<CoinsPanelUi>(0.f);
          m_coinsPanelUi->init(false);
          m_coinsPanelUi->setCoins(Inventory::instance().getPoints());
          switchUi(TC_MENU);
        };
        m_fsm.state<FSM::States::MainMenu>().onLeaveFunc =
                [&](auto &, auto &, auto &) {
            m_mainMenuUi = nullptr;
            m_coinsPanelUi = nullptr;
        };

        //*************************VEHICLE SELECT***************************************
        m_fsm.state<FSM::States::VehicleSelect>().onEnterFunc = [&](auto &, auto &,
                                                                    auto &) {
            W4_LOG_INFO("VehicleSelect onEnter!");
		    m_vehicleSelectUi = make::sptr<VehicleSelectUi>(m_cameraNode,m_camera, 2.f, 0.f);
            m_vehicleSelectUi->init(false);
            m_vehicleSelectUi->setPlayPressedCallback([this](){m_fsm.processEvent(FSM::Events::Start);});
            m_vehicleSelectUi->setCarPressedCallback([this](const int id) {
                Inventory::instance().setCurrentCar(Transport::createCar(id));
            });
            switchUi(TC_VEHICLE_SELECT);
        };
        m_fsm.state<FSM::States::VehicleSelect>().onLeaveFunc =
                [&](auto &, auto &, auto &) { m_vehicleSelectUi = nullptr; };

        //***************************GAME_PROCESS********************************************
        m_fsm.state<FSM::States::Game>().onEnterFunc = [&](auto &, auto &, auto &) {
            W4_LOG_INFO("Game onEnter");
            switchUi(TC_GAME);
            // SCENE LAUNCHING TEST!
            m_inGameUi = make::sptr<InGameUi>(m_cameraNode, m_camera, 0.3f, 0.f);
            m_inGameUi->init(false);
            m_sceneNode = make::sptr<Node>("SceneNode");
            m_gameRoot->addChild(m_sceneNode);
            auto &scene = m_sceneNode->template addComponent<SceneComponent>();
            scene.setup(m_cameraNode);
            auto &testPhysics =
                    m_sceneNode->template addComponent<TestPhysicsComponent>();
            testPhysics.setZeroVelocityCallback([&]() { onEndGame(); });
            m_physicsNode = m_sceneNode;
            auto &cameraMovement =
                    m_cameraNode->template addComponent<CameraMovementComponent>();
            m_cameraMovementNode = m_cameraNode;
            cameraMovement.setup(m_cameraNode, testPhysics.getCarNode());
            auto &acceleration = m_cameraNode->addComponent<AccelerationComponent>();
            acceleration.setup(m_sceneNode);
            W4_LOG_DEBUG("CANISTER: %d", Inventory::instance().getCanisterLVL());
            m_inGameUi->setKeyPressedCallback(
                    [this]() { m_sceneNode->getFirstComponent<TestPhysicsComponent>().launchCar(); });
            m_inGameUi->setCanisterPressedCallback(
                    [this]() { m_sceneNode->getFirstComponent<TestPhysicsComponent>().startAcceleration(); });
        };
        m_fsm.state<FSM::States::Game>().onLeaveFunc = [&](auto &, auto &, auto &) {
            W4_LOG_INFO("Game onLeave");
            m_gameRoot->removeChild(m_sceneNode);
            m_sceneNode->template removeAllComponents<SceneComponent>();
            m_sceneNode->template removeAllComponents<TestPhysicsComponent>();
            m_cameraNode->template removeAllComponents<CameraMovementComponent>();
            m_cameraNode->template removeAllComponents<AccelerationComponent>();
            m_physicsNode = nullptr;
            m_cameraMovementNode = nullptr;
            m_sceneNode = nullptr;
            m_inGameUi = nullptr;
        };

        //***********************GAME RESULT*********************************
        m_fsm.state<FSM::States::Result>().onEnterFunc = [&](auto &, auto &,
                                                             auto &) {
            W4_LOG_INFO("Result onEnter");
            switchUi(TC_RESULT);
        };
        m_fsm.state<FSM::States::Result>().onLeaveFunc =
                [&](auto &, auto &, auto &) { W4_LOG_INFO("Result onLeave"); };
        //***********************ADS*********************************
        m_fsm.state<FSM::States::Ads>().onEnterFunc = [&](auto &, auto &, auto &) {
            W4_LOG_INFO("Ads onEnter");
            switchUi(TC_ADS);
        };
        m_fsm.state<FSM::States::Ads>().onLeaveFunc = [&](auto &, auto &, auto &) {
            W4_LOG_INFO("Ads onLeave");
        };

        //***********************SETTINGS MENU*********************************
        m_fsm.state<FSM::States::SettingsMenu>().onEnterFunc = [&](auto &, auto &,
                                                                   auto &) {
            W4_LOG_INFO("SettingsMenu onEnter");
            switchUi(TC_SETTINGS);
        };
        m_fsm.state<FSM::States::SettingsMenu>().onLeaveFunc =
                [&](auto &, auto &, auto &) { W4_LOG_INFO("SettingsMenu onLeave"); };

        //***********************HIGHSCORES MENU*********************************
        m_fsm.state<FSM::States::HighScores>().onEnterFunc = [&](auto &, auto &,
                                                                 auto &) {
            W4_LOG_INFO("HighScores onEnter");
            switchUi(TC_HIGHSCORES);
        };
        m_fsm.state<FSM::States::HighScores>().onLeaveFunc =
                [&](auto &, auto &, auto &) { W4_LOG_INFO("HighScores onLeave"); };

        //***********************SHOP MENU*********************************
        m_fsm.state<FSM::States::Shop>().onEnterFunc = [&](auto &, auto &, auto &) {
            W4_LOG_INFO("Shop onEnter");
            m_shopNode->template getFirstComponent<ShopComponent>().updateScores();
            m_coinsPanelUi = make::sptr<CoinsPanelUi>(0.f);
            m_coinsPanelUi->init(false);
            m_coinsPanelUi->setCoins(Inventory::instance().getPoints());
            switchUi(TC_SHOP);
        };
        m_fsm.state<FSM::States::Shop>().onLeaveFunc = [&](auto &, auto &, auto &) {
            W4_LOG_INFO("Shop onLeave");
            m_coinsPanelUi = nullptr;
        };

        //***********************LAUNCH FIRST STATE*********************************
        m_fsm.init<FSM::States::Preloading>(FSM::Events::Initialize);
        W4_LOG_DEBUG("FSM initialized");
    }

    void onTouchEnd(const Touch::End &evt) {
        auto ray = m_camera->createRayFromScreen(evt.point);
        ray.length = 100;
        auto hit = Render::raycast(ray);
        if (hit.target != nullptr) {
            W4_LOG_DEBUG("[RAYCAST] hitted %s",
                         hit.target->getParent()->getName().c_str());
        }
    }

private:
    struct FSM
    {
        enum class Events
        {
            Initialize,
            Settings,
            HighScores,
            Shop,
            Back,
            Start,
            Next,
            Restart,
            TryAgain,
            Bonus
        };
        struct States
        {
            struct Preloading : w4::fsm::FuncState<Events>
            {
            };
            struct MainMenu : w4::fsm::FuncState<Events>
            {
            };
            struct SettingsMenu : w4::fsm::FuncState<Events>
            {
            };
            struct HighScores : w4::fsm::FuncState<Events>
            {
            };
            struct Shop : w4::fsm::FuncState<Events>
            {
            };
            struct VehicleSelect : w4::fsm::FuncState<Events>
            {
            };
            struct Game : w4::fsm::FuncState<Events>
            {
            };
            struct Result : w4::fsm::FuncState<Events>
            {
            };
            struct Ads : w4::fsm::FuncState<Events>
            {
            };
        };
        using Type = w4::fsm::FSM<
                    // initialization
                    w4::fsm::Transition<Events::Initialize, States::Preloading,
                            States::MainMenu>,
                // main game cycle
                w4::fsm::Transition<Events::Start, States::MainMenu,
                        States::VehicleSelect>,
                w4::fsm::Transition<Events::Start, States::VehicleSelect, States::Game>,
                w4::fsm::Transition<Events::Next, States::Game, States::Result>,
                w4::fsm::Transition<Events::TryAgain, States::Result, States::Game>,
                w4::fsm::Transition<Events::Restart, States::Result,
                        States::VehicleSelect>,
                w4::fsm::Transition<Events::Next, States::Result, States::MainMenu>,
                w4::fsm::Transition<Events::Bonus, States::Result, States::Ads>,
                w4::fsm::Transition<Events::Next, States::Ads, States::MainMenu>,
                // settings menu
                w4::fsm::Transition<Events::Settings, States::MainMenu,
                        States::SettingsMenu>,
                w4::fsm::Transition<Events::Back, States::SettingsMenu,
                        States::MainMenu>,
                // highScores menu
                w4::fsm::Transition<Events::HighScores, States::MainMenu,
                        States::HighScores>,
                w4::fsm::Transition<Events::Back, States::HighScores, States::MainMenu>,
                // shop menu
                w4::fsm::Transition<Events::Shop, States::MainMenu, States::Shop>,
                w4::fsm::Transition<Events::Back, States::Shop, States::MainMenu>>;
    };
    FSM::Type m_fsm;
	
    sptr<MainMenuUi> m_mainMenuUi;
    sptr<VehicleSelectUi> m_vehicleSelectUi;
    sptr<InGameUi> m_inGameUi;
    sptr<CoinsPanelUi> m_coinsPanelUi;

    std::unordered_map<std::string, sptr<Node>> m_uiCollection;
    sptr<Node> m_gameRoot;
    sptr<Node> m_sceneNode;
    sptr<Node> m_cameraUi;
    sptr<Node> m_cameraNode;
    sptr<Node> m_physicsNode;
    sptr<Node> m_cameraMovementNode;
    sptr<Node> m_shopNode;
    sptr<LayoutLabel> m_label;


    sptr<Camera> m_camera;
    sptr<event::Touch::End::Handle> m_touchEndHandler;
};

W4_RUN(toyCarsApplication)