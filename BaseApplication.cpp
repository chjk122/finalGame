/*
-----------------------------------------------------------------------------
Filename:    BaseApplication.cpp
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/
Tutorial Framework (for Ogre 1.9)
http://www.ogre3d.org/wiki/
-----------------------------------------------------------------------------
*/

#include "BaseApplication.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
#include <macUtils.h>
#endif

//---------------------------------------------------------------------------
BaseApplication::BaseApplication(void)
    : mRoot(0),
    mCamera(0),
    mSceneMgr(0),
    mWindow(0),
    mResourcesCfg(Ogre::StringUtil::BLANK),
    mPluginsCfg(Ogre::StringUtil::BLANK),
    mTrayMgr(0),
    mCameraMan(0),
    mDetailsPanel(0),
    mCursorWasVisible(false),
    mShutDown(false),
    mInputManager(0),
    mMouse(0),
    mKeyboard(0),
    mOverlaySystem(0),
    mInfoLabel(0),
    mEnemyInfo(0),
    mToDoNextLabel(0),
    mPower(0),
    mAngle(0),
    mHeight(0),
    mGameState(0)
{
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
    m_ResourcePath = Ogre::macBundlePath() + "/Contents/Resources/";
#else
    m_ResourcePath = "";
#endif

    mSimulator = new Simulator;
}

//---------------------------------------------------------------------------
BaseApplication::~BaseApplication(void)
{
    if (mTrayMgr) delete mTrayMgr;
    if (mCameraMan) delete mCameraMan;
    if (mOverlaySystem) delete mOverlaySystem;

    // Remove ourself as a Window listener
    Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
    windowClosed(mWindow);
    delete mRoot;
    delete mSimulator;
    if(mGameState <= 1)
        delete playerClient;
    delete playerHost;
}

//---------------------------------------------------------------------------
bool BaseApplication::configure(void)
{
    // Show the configuration dialog and initialise the system.
    // You can skip this and use root.restoreConfig() to load configuration
    // settings if you were sure there are valid ones saved in ogre.cfg.
    if(mRoot->showConfigDialog())
    {
        // If returned true, user clicked OK so initialise.
        // Here we choose to let the system create a default rendering window by passing 'true'.
        mWindow = mRoot->initialise(true, "TutorialApplication Render Window");

        return true;
    }
    else
    {
        return false;
    }
}
//---------------------------------------------------------------------------
void BaseApplication::chooseSceneManager(void)
{
    // Get the SceneManager, in this case a generic one
    mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);

    // Initialize the OverlaySystem (changed for Ogre 1.9)
    mOverlaySystem = new Ogre::OverlaySystem();
    mSceneMgr->addRenderQueueListener(mOverlaySystem);
}
//---------------------------------------------------------------------------
void BaseApplication::createCamera(void)
{
    // // Create the camera
    mCamera = mSceneMgr->createCamera("PlayerCam");

    // Position it at 500 in Z direction
    mCamera->setPosition(Ogre::Vector3(0,0,80));
    // Look back along -Z
    mCamera->lookAt(Ogre::Vector3(0,0,-300));
    mCamera->setNearClipDistance(5);

    mCameraMan = new OgreBites::SdkCameraMan(mCamera);   // Create a default camera controller
}
//---------------------------------------------------------------------------
void BaseApplication::createGUI(void)
{
    mToDoNextLabel = mTrayMgr->createLabel(OgreBites::TL_TOP, "infoNext", "Press Enter to select the power", 400);
    mToDoNextLabel->show();
    mInfoLabel = mTrayMgr->createLabel(OgreBites::TL_TOP, "pointCounter", "Round 1             Points: 0", 400);
    mInfoLabel->show();
    if(mGameState > 1)
    {
        mEnemyInfo = mTrayMgr->createLabel(OgreBites::TL_TOP, "enemyInfo", "Opponent: Round 1   Points: 0", 400);
        mEnemyInfo->show();
    }
    mPower = mTrayMgr->createProgressBar(OgreBites::TL_TOPLEFT, "power",   "0           Max Power", 200, 20);
    mPower->show();
    mAngle = mTrayMgr->createProgressBar(OgreBites::TL_TOPLEFT, "angle",   " Left    Center   Right", 200, 20);
    mAngle->show();
    mHeight = mTrayMgr->createProgressBar(OgreBites::TL_TOPLEFT, "height", "Low              High", 200, 20);
    mHeight->show();

    /************************************select menu Gui ****************************************************/

    // mSingleButton = mTrayMgr->createButton(OgreBites::TL_CENTER, "single", "Single Player");
    // // mSingleButton->
    // // Ogre::String str = "Single Player";
    // mTrayMgr->showCursor();
    // mTrayMgr->moveWidgetToTray(mSingleButton, OgreBites::TL_CENTER, 0);

     /************************************select menu Gui ****************************************************/
    mTrayMgr->moveWidgetToTray(mToDoNextLabel, OgreBites::TL_TOP, 0);
    mTrayMgr->moveWidgetToTray(mInfoLabel, OgreBites::TL_TOP, 0);
    if(mGameState > 1)
    {
        mTrayMgr->moveWidgetToTray(mEnemyInfo, OgreBites::TL_TOP, 0);
    }
    mTrayMgr->moveWidgetToTray(mHeight, OgreBites::TL_TOPLEFT, 0);
    mTrayMgr->moveWidgetToTray(mAngle, OgreBites::TL_TOPLEFT, 0);
    mTrayMgr->moveWidgetToTray(mPower, OgreBites::TL_TOPLEFT, 0);
}

void BaseApplication::setupSingleOrMultiGUI(void)
{
    mMenuLabel = mTrayMgr->createLabel(OgreBites::TL_CENTER, "menuLabel", "select game mode", 220);
    mButton1 = mTrayMgr->createButton(OgreBites::TL_CENTER, "single", "Single-Player", 220);
    mButton2 = mTrayMgr->createButton(OgreBites::TL_CENTER, "multi", "MutiPlayer", 220);
}

void BaseApplication::setupHostOrJoinGUI(void)
{
    mMenuLabel->setCaption("host or join game");
    mButton1 = mTrayMgr->createButton(OgreBites::TL_CENTER, "host", "Host Game", 220);
    mButton2 = mTrayMgr->createButton(OgreBites::TL_CENTER, "join", "Join Game", 220);
    mButtonBack = mTrayMgr->createButton(OgreBites::TL_CENTER, "hostOrJoinBack", "Back", 220);
}

void BaseApplication::setupHostGUI(void)
{
    mMenuLabel->setCaption("searching for client...");
    mButtonBack = mTrayMgr->createButton(OgreBites::TL_CENTER, "cancelHost", "Cancel", 220);
}

void BaseApplication::setupJoinGUI(void)
{
    mMenuLabel->setCaption("searching for host...");
    mButtonBack = mTrayMgr->createButton(OgreBites::TL_CENTER, "cancelJoin", "Cancel", 220);
}

void BaseApplication::createObjects(void)
{
    Ogre::SceneNode* node;
    Ogre::SceneNode* playerNode;

    Ball* ball = new Ball("ball", mSceneMgr, mSimulator, node, 90., Ogre::Vector3(0.,-240.,210.));
    ball->create();

    Goal* goal = new Goal("goal", mSceneMgr, mSimulator, node, 0.,100, 100, Ogre::Vector3::UNIT_Z, -249.6);
    goal->create();


    playerHost = new Player("playerHost", mSceneMgr, mSimulator, playerNode, 0.,ball, Ogre::Vector3(0.,-250.,225.));
    playerHost->create();

    if(mGameState != 1) //if not single player
    {
        GhostBall* ghostBall = new GhostBall("ghostBall", mSceneMgr, mSimulator, node, 90., Ogre::Vector3(0.,-240.,-210.));
        ghostBall->create();
        playerClient = new Player("playerClient", mSceneMgr, mSimulator, playerNode, 0.,ghostBall, Ogre::Vector3(0.,-250.,-225.));
        playerClient->create(Ogre::Degree(90), Ogre::Degree(0));
    }
}
//---------------------------------------------------------------------------
void BaseApplication::createFrameListener(void)
{
    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;

    mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

    mInputManager = OIS::InputManager::createInputSystem(pl);

    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, true));
    mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, true));

    mMouse->setEventCallback(this);
    mKeyboard->setEventCallback(this);

    // Set initial mouse clipping size
    windowResized(mWindow);

    // Register as a Window listener
    Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

    mInputContext.mKeyboard = mKeyboard;
    mInputContext.mMouse = mMouse;
    mTrayMgr = new OgreBites::SdkTrayManager("InterfaceName", mWindow, mInputContext, this);
    mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    mTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
    mTrayMgr->hideCursor();

    // Create a params panel for displaying sample details
    Ogre::StringVector items;
    items.push_back("cam.pX");
    items.push_back("cam.pY");
    items.push_back("cam.pZ");
    items.push_back("");
    items.push_back("cam.oW");
    items.push_back("cam.oX");
    items.push_back("cam.oY");
    items.push_back("cam.oZ");
    items.push_back("");
    items.push_back("Filtering");
    items.push_back("Poly Mode");

    mDetailsPanel = mTrayMgr->createParamsPanel(OgreBites::TL_NONE, "DetailsPanel", 200, items);
    mDetailsPanel->setParamValue(9, "Bilinear");
    mDetailsPanel->setParamValue(10, "Solid");
    mDetailsPanel->hide();

    mRoot->addFrameListener(this);
}
//---------------------------------------------------------------------------
void BaseApplication::destroyScene(void)
{
}
//---------------------------------------------------------------------------
void BaseApplication::createViewports(void)
{
    // Create one viewport, entire window
    Ogre::Viewport* vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}
//---------------------------------------------------------------------------
void BaseApplication::setupResources(void)
{
    // Load resource paths from config file
    Ogre::ConfigFile cf;
    cf.load(mResourcesCfg);

    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
            // OS X does not set the working directory relative to the app.
            // In order to make things portable on OS X we need to provide
            // the loading with it's own bundle path location.
            if (!Ogre::StringUtil::startsWith(archName, "/", false)) // only adjust relative directories
                archName = Ogre::String(Ogre::macBundlePath() + "/" + archName);
#endif

            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
        }
    }
}
//---------------------------------------------------------------------------
void BaseApplication::createResourceListener(void)
{
}
//---------------------------------------------------------------------------
void BaseApplication::loadResources(void)
{
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}
//---------------------------------------------------------------------------
void BaseApplication::go(void)
{
#ifdef _DEBUG
#ifndef OGRE_STATIC_LIB
    mResourcesCfg = m_ResourcePath + "resources_d.cfg";
    mPluginsCfg = m_ResourcePath + "plugins_d.cfg";
#else
    mResourcesCfg = "resources_d.cfg";
    mPluginsCfg = "plugins_d.cfg";
#endif
#else
#ifndef OGRE_STATIC_LIB
    mResourcesCfg = m_ResourcePath + "resources.cfg";
    mPluginsCfg = m_ResourcePath + "plugins.cfg";
#else
    mResourcesCfg = "resources.cfg";
    mPluginsCfg = "plugins.cfg";
#endif
#endif

    if (!setup())
        return;

    mRoot->startRendering();

    // Clean up
    destroyScene();
}
//---------------------------------------------------------------------------
bool BaseApplication::setup(void)
{
    mRoot = new Ogre::Root(mPluginsCfg);

    setupResources();

    bool carryOn = configure();
    if (!carryOn) return false;

    chooseSceneManager();
    createCamera();
    createViewports();

    // Set default mipmap level (NB some APIs ignore this)
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

    // Create any resource listeners (for loading screens)
    createResourceListener();
    // Load resources
    loadResources();

    // Create the scene
    createScene();

    createFrameListener();

    SDL_Init(SDL_INIT_EVERYTHING);
    Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096);
    music = Mix_LoadMUS("game_music.mp3");
    Mix_PlayMusic(music,-1);
    Mix_Volume(-1, 40);

    mNetworkWrapper = new NetworkWrapper();
    mTrayMgr->showCursor();
    setupSingleOrMultiGUI();
    // createGUI();
   // createObjects();

    return true;
};
//---------------------------------------------------------------------------
bool shotTheBall = false;
bool scored = false;
int points = 0;
int enemyPoints = 0;
int enemyRound = 1;
int roundNum = 1;
Ogre::Real power = -1;
Ogre::Real angle = -1;
Ogre::Real height = -1;
bool powerUp = true;
bool angleUp = true;
bool heightUp = true;
bool gameIsOver = false;
bool enemyFinishedGame = false;

int firstGamePoints = -1;
bool buttonMade = false;

bool BaseApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    // updateMultiplayerBalls();
    double progressStepValue = evt.timeSinceLastFrame*.8;
    if(mWindow->isClosed())
        return false;

    if(mShutDown)
        return false;

    // Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();

    //check if both games are done
    if(mGameState > 1)
    {
        //game is done
        if(firstGamePoints != -1 && enemyFinishedGame && !buttonMade)
        {
            std::string result;
            if(firstGamePoints > enemyPoints)
                result = "YOU WON :)";
            else if(firstGamePoints < enemyPoints)
                result = "YOU LOST :(";
            else
                result = "YOU TIED :|";
            mTrayMgr->showCursor();
            mMenuLabel = mTrayMgr->createLabel(OgreBites::TL_CENTER, "TESTEND", "GAME OVER", 220);
            mButtonGameOver = mTrayMgr->createButton(OgreBites::TL_CENTER, "result", result, 220);
            buttonMade = true;
        }
    }


    if(mGameState == 2) //host
    {
        // PLAYER HOST SENDING DATA TO CLIENT JOIN
        Ball* testBall = playerHost->playerBall;
        Ogre::SceneNode* node = testBall->rootNode;
        Ogre::Vector3 pos = node->getPosition();
        mNetworkWrapper->sendData(pos.x, pos.y, pos.z, points, roundNum);

        //PLAYER HOST RECIEVING DATA
        if(!enemyFinishedGame)
        {
            node = playerClient->playerBall->rootNode;
            pos = node->getPosition();
            vector<float> *ClientInfo = mNetworkWrapper->receiveData();
            // for(int i = 0; i < HostInfo->size(); i++)
            // {
            //     std::cout << "ClentInfo[" << i << "] = " << (*HostInfo)[i] << std::endl;

            // }
            playerClient->playerBall->setGhostBallPos(-(*ClientInfo)[0], (*ClientInfo)[1], -(*ClientInfo)[2]);
            enemyPoints = (*ClientInfo)[3];
            if((*ClientInfo)[4] == 16)
            {
                enemyFinishedGame = true;
            }
            else
                enemyRound = (*ClientInfo)[4];
            delete ClientInfo;

            std::string label3 = "Opponent: Round: ";
            std::string label4 = "   Points: ";
            std::ostringstream eTemp1;
            std::ostringstream eTemp2;
            eTemp1<<enemyRound;
            eTemp2<<enemyPoints;
            std::string ints1=eTemp1.str();
            std::string ints2=eTemp2.str();
            mEnemyInfo->setCaption(label3 + ints1 + label4 + ints2);
        }
    }
    if(mGameState == 3) //client
    {
        //PLAYER CLIENT RECIEVING DATA
        Ogre::SceneNode* node;
        Ogre::Vector3 pos;
        if(!enemyFinishedGame)
        {
            node = playerClient->playerBall->rootNode;
            pos = node->getPosition();
            vector<float> *HostInfo = mNetworkWrapper->receiveData();
            // for(int i = 0; i < HostInfo->size(); i++)
            // {
            //     std::cout << "HostInfo[" << i << "] = " << (*HostInfo)[i] << std::endl;

            // }
            playerClient->playerBall->setGhostBallPos(-(*HostInfo)[0], (*HostInfo)[1], -(*HostInfo)[2]);
            enemyPoints = (*HostInfo)[3];
            if((*HostInfo)[4] == 16)
            {
                enemyFinishedGame = true;
            }
            else
                enemyRound = (*HostInfo)[4];
            delete HostInfo;

            std::string label3 = "Opponent: Round: ";
            std::string label4 = "   Points: ";
            std::ostringstream eTemp1;
            std::ostringstream eTemp2;
            eTemp1<<enemyRound;
            eTemp2<<enemyPoints;
            std::string ints1=eTemp1.str();
            std::string ints2=eTemp2.str();
            mEnemyInfo->setCaption(label3 + ints1 + label4 + ints2);
        }

        // PLAYER CLIENT SENDING DATA TO CLIENT JOIN
        Ball* testBall = playerHost->playerBall;
        node = testBall->rootNode;
        pos = node->getPosition();
        mNetworkWrapper->sendData(pos.x, pos.y, pos.z, points, roundNum);
    }



    if(mGameState != 0)
    {
        if(!gameIsOver)
        {
            if(mGameState != 1)
            {
                // if(mGameState == 2) //host
                // {
                //     // PLAYER HOST SENDING DATA TO CLIENT JOIN
                //     Ball* testBall = playerHost->playerBall;
                //     Ogre::SceneNode* node = testBall->rootNode;
                //     Ogre::Vector3 pos = node->getPosition();
                //     mNetworkWrapper->sendData(pos.x, pos.y, pos.z, points, roundNum);

                //     //PLAYER HOST RECIEVING DATA
                //     if(!enemyFinishedGame)
                //     {
                //         node = playerClient->playerBall->rootNode;
                //         pos = node->getPosition();
                //         vector<float> *ClientInfo = mNetworkWrapper->receiveData();
                //         // for(int i = 0; i < HostInfo->size(); i++)
                //         // {
                //         //     std::cout << "ClentInfo[" << i << "] = " << (*HostInfo)[i] << std::endl;

                //         // }
                //         playerClient->playerBall->setGhostBallPos(-(*ClientInfo)[0], (*ClientInfo)[1], -(*ClientInfo)[2]);
                //         enemyPoints = (*ClientInfo)[3];
                //         if((*ClientInfo)[4] == 16)
                //         {
                //             enemyFinishedGame = true;
                //         }
                //         else
                //             enemyRound = (*ClientInfo)[4];
                //         delete ClientInfo;
                //     }
                // }
                // if(mGameState == 3) //client
                // {
                //     //PLAYER CLIENT RECIEVING DATA
                //     Ogre::SceneNode* node;
                //     Ogre::Vector3 pos;
                //     if(!enemyFinishedGame)
                //     {
                //         node = playerClient->playerBall->rootNode;
                //         pos = node->getPosition();
                //         vector<float> *HostInfo = mNetworkWrapper->receiveData();
                //         // for(int i = 0; i < HostInfo->size(); i++)
                //         // {
                //         //     std::cout << "HostInfo[" << i << "] = " << (*HostInfo)[i] << std::endl;

                //         // }
                //         playerClient->playerBall->setGhostBallPos(-(*HostInfo)[0], (*HostInfo)[1], -(*HostInfo)[2]);
                //         enemyPoints = (*HostInfo)[3];
                //         if((*HostInfo)[4] == 16)
                //         {
                //             enemyFinishedGame = true;
                //         }
                //         else
                //             enemyRound = (*HostInfo)[4];
                //         delete HostInfo;
                //     }

                //     // PLAYER CLIENT SENDING DATA TO CLIENT JOIN
                //     Ball* testBall = playerHost->playerBall;
                //     node = testBall->rootNode;
                //     pos = node->getPosition();
                //     mNetworkWrapper->sendData(pos.x, pos.y, pos.z, points, roundNum);
                // }
            }
            if(!shotTheBall)
            {
                if(power == -1)
                {
                    if(powerUp)
                    {
                        mPower->setProgress(mPower->getProgress() + progressStepValue);
                        if(mPower->getProgress() >= 1)
                            powerUp = false;
                    }
                    else
                    {
                        mPower->setProgress(mPower->getProgress() - progressStepValue);
                        if(mPower->getProgress() <= .1)
                            powerUp = true;
                    }
                }
                else if(angle == -1)
                {
                    if(angleUp)
                    {
                        mAngle->setProgress(mAngle->getProgress() + progressStepValue);
                        if(mAngle->getProgress() >= 1)
                            angleUp = false;
                    }
                    else
                    {
                        mAngle->setProgress(mAngle->getProgress() - progressStepValue);
                        if(mAngle->getProgress() <= .1)
                            angleUp = true;
                    }
                }
                else if(height == -1)
                {
                    if(heightUp)
                    {
                        mHeight->setProgress(mHeight->getProgress() + progressStepValue);
                        if(mHeight->getProgress() >= 1)
                            heightUp = false;
                    }
                    else
                    {
                        mHeight->setProgress(mHeight->getProgress() - progressStepValue);
                        if(mHeight->getProgress() <= .1)
                            heightUp = true;
                    }
                }
            }

            bool scoredNow = mSimulator->stepSimulation(scored, evt.timeSinceLastFrame, music2);
            if(scoredNow && !scored)
            {   
                Mix_Chunk* chunk;
                chunk = Mix_LoadWAV("196461__paulw2k__football-crowd-goal.wav");
                if(Mix_PlayChannel( -1, chunk, 0 ) == -1)
                {
                    printf("Mix_PlayChannel: %s\n",Mix_GetError());
                }
                Mix_Volume(-1, 20);
                scored = scoredNow;
                points++;
            }
            std::string label1 = "Round: ";
            std::string label2 = "              Points: ";
            std::string ints1;
            std::string ints2;
            std::ostringstream temp1;
            std::ostringstream temp2;
            temp1<<roundNum;
            temp2<<points;
            ints1=temp1.str();
            ints2=temp2.str();
            mInfoLabel->setCaption(label1 + ints1 + label2 + ints2);
        }
        else
        {
            mSimulator->stepSimulation(scored, evt.timeSinceLastFrame, music2);
        }
    }

    mTrayMgr->frameRenderingQueued(evt);

    if (!mTrayMgr->isDialogVisible())
    {
        mCameraMan->frameRenderingQueued(evt);   // If dialog isn't up, then update the camera
        if (mDetailsPanel->isVisible())          // If details panel is visible, then update its contents
        {
            mDetailsPanel->setParamValue(0, Ogre::StringConverter::toString(mCamera->getDerivedPosition().x));
            mDetailsPanel->setParamValue(1, Ogre::StringConverter::toString(mCamera->getDerivedPosition().y));
            mDetailsPanel->setParamValue(2, Ogre::StringConverter::toString(mCamera->getDerivedPosition().z));
            mDetailsPanel->setParamValue(4, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().w));
            mDetailsPanel->setParamValue(5, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().x));
            mDetailsPanel->setParamValue(6, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().y));
            mDetailsPanel->setParamValue(7, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().z));
        }
    }

    return true;
}
//---------------------------------------------------------------------------
bool playingMusic = true;
bool BaseApplication::keyPressed( const OIS::KeyEvent &arg )
{
    if (mTrayMgr->isDialogVisible()) return true;   // don't process any more keys if dialog is up

    if (arg.key == OIS::KC_F)   // toggle visibility of advanced frame stats
    {
        mTrayMgr->toggleAdvancedFrameStats();
    }
    else if (arg.key == OIS::KC_G)   // toggle visibility of even rarer debugging details
    {
        if (mDetailsPanel->getTrayLocation() == OgreBites::TL_NONE)
        {
            mTrayMgr->moveWidgetToTray(mDetailsPanel, OgreBites::TL_TOPRIGHT, 0);
            mDetailsPanel->show();
        }
        else
        {
            mTrayMgr->removeWidgetFromTray(mDetailsPanel);
            mDetailsPanel->hide();
        }
    }
    else if (arg.key == OIS::KC_T)   // cycle polygon rendering mode
    {
        Ogre::String newVal;
        Ogre::TextureFilterOptions tfo;
        unsigned int aniso;

        switch (mDetailsPanel->getParamValue(9).asUTF8()[0])
        {
        case 'B':
            newVal = "Trilinear";
            tfo = Ogre::TFO_TRILINEAR;
            aniso = 1;
            break;
        case 'T':
            newVal = "Anisotropic";
            tfo = Ogre::TFO_ANISOTROPIC;
            aniso = 8;
            break;
        case 'A':
            newVal = "None";
            tfo = Ogre::TFO_NONE;
            aniso = 1;
            break;

        default:
            newVal = "Bilinear";
            tfo = Ogre::TFO_BILINEAR;
            aniso = 1;
        }

        Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(tfo);
        Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(aniso);
        mDetailsPanel->setParamValue(9, newVal);
    }
    else if(arg.key == OIS::KC_SPACE){
        if(height != -1 && shotTheBall && !gameIsOver)
        {
            shotTheBall = false;
            scored = false;
            power = -1;
            height = -1;
            angle = -1;
            mHeight->show();
            mAngle->show();
            mPower->show();
            mTrayMgr->moveWidgetToTray(mHeight, OgreBites::TL_TOPLEFT, 0);
            mTrayMgr->moveWidgetToTray(mAngle, OgreBites::TL_TOPLEFT, 0);
            mTrayMgr->moveWidgetToTray(mPower, OgreBites::TL_TOPLEFT, 0);
            mToDoNextLabel->setCaption("Press Enter to select the power");
            if(roundNum > 15)
            {

            }
            if(roundNum == 15)
            {
                mToDoNextLabel->setCaption("Press M to replay or ESC to quit");
                std::string label1;
                if(points == 0 )
                {
                    label1 = "You're garbage... press ESC ";
                }
                else if(points <= 4)
                {
                    label1 = "You're almost garbage ";
                }
                else if(points <= 8)
                {
                    label1 = "you're average ";
                }
                else if(points <= 9)
                {
                    label1 = "You almost won ";
                }
                else if(points <= 12)
                {
                    label1 = "You won";
                }
                else if(points <= 14)
                {
                    label1 = "Almost scored them all :(";
                }
                else if(points <= 15)
                {
                    label1 = "PERFECT GAME OMG ";
                }
                std::string label2 = "    Points: ";
                std::string ints2;
                std::ostringstream temp2;
                temp2<<points;
                ints2=temp2.str();
                mInfoLabel->setCaption(label1 + label2 + ints2);
                gameIsOver = true;
                if(firstGamePoints == -1)
                    firstGamePoints = points;
                roundNum++;
            }
            else
            {
                roundNum++;
                playerHost->playerBall = mSimulator->reload();
            }
        }
    }
    else if(arg.key == OIS::KC_RETURN){
        if(mGameState != 0)
        {
            if(!gameIsOver)
            {
                if(power == -1)
                {
                    //scale the range of [.1, 1] to [0, 1]
                    power = (mPower->getProgress() - .1) * (1/.9);
                    mToDoNextLabel->setCaption("Press Enter to select the angle");
                }
                else if(angle == -1)
                {
                    angle = (mAngle->getProgress() - .1) * (1/.9);
                    mToDoNextLabel->setCaption("Press Enter to select the height");
                }
                else if(height == -1)
                {
                    height = (mHeight->getProgress() - .1) * (1/.9);
                    mSimulator->kickBall(-15000 * power, angle - .5, height);
                    Mix_Chunk* chunk;
                    chunk = Mix_LoadWAV("Ball_Single_Kick_Sound_Effect.wav");
                    if(Mix_PlayChannel( 0, chunk, 0 ) == -1)
                    {
                        printf("Mix_PlayChannel: %s\n",Mix_GetError());
                    }
                    shotTheBall = true;
                    mHeight->setProgress(.1);
                    mAngle->setProgress(.1);
                    mPower->setProgress(.1);
                    mHeight->hide();
                    mAngle->hide();
                    mPower->hide();
                    mTrayMgr->removeWidgetFromTray(mHeight);
                    mTrayMgr->removeWidgetFromTray(mAngle);
                    mTrayMgr->removeWidgetFromTray(mPower);
                    mToDoNextLabel->setCaption("Press Space to go to the next round");
                }
            }
        }
    }

    else if (arg.key == OIS::KC_R)   // cycle polygon rendering mode
    {
        Ogre::String newVal;
        Ogre::PolygonMode pm;

        switch (mCamera->getPolygonMode())
        {
        case Ogre::PM_SOLID:
            newVal = "Wireframe";
            pm = Ogre::PM_WIREFRAME;
            break;
        case Ogre::PM_WIREFRAME:
            newVal = "Points";
            pm = Ogre::PM_POINTS;
            break;
        default:
            newVal = "Solid";
            pm = Ogre::PM_SOLID;
        }

        mCamera->setPolygonMode(pm);
        mDetailsPanel->setParamValue(10, newVal);
    }
    else if(arg.key == OIS::KC_M)   // refresh all textures
    {
        if(gameIsOver)
        {
            gameIsOver = false;
            roundNum = 1;
            points = 0;
            mToDoNextLabel->setCaption("Press Enter to select the power");
            playerHost->playerBall = mSimulator->reload();
        }
    }
    else if(arg.key == OIS::KC_F5)   // refresh all textures
    {
        Ogre::TextureManager::getSingleton().reloadAll();
    }
    else if (arg.key == OIS::KC_SYSRQ)   // take a screenshot
    {
        mWindow->writeContentsToTimestampedFile("screenshot", ".jpg");
    }
    else if (arg.key == OIS::KC_ESCAPE)
    {
        mShutDown = true;
    }
    // else if(arg.key == OIS::KC_W ||
    //         arg.key == OIS::KC_A ||
    //         arg.key == OIS::KC_S ||
    //         arg.key == OIS::KC_D ||
    //         arg.key == OIS::KC_UP ||
    //         arg.key == OIS::KC_DOWN ||
    //         arg.key == OIS::KC_RIGHT ||
    //         arg.key == OIS::KC_LEFT)
    // {

    // }
    else if(arg.key == OIS::KC_P)
    {
        if(playingMusic){
            Mix_PauseMusic();
            playingMusic = false;
        } else {
            Mix_ResumeMusic();
            playingMusic = true;
        }
    }
    else if(mGameState != 0)
        mCameraMan->injectKeyDown(arg);
    return true;
}
//---------------------------------------------------------------------------
bool BaseApplication::keyReleased(const OIS::KeyEvent &arg)
{
    if(mGameState != 0)
        mCameraMan->injectKeyUp(arg);
    return true;
}
//---------------------------------------------------------------------------
bool BaseApplication::mouseMoved(const OIS::MouseEvent &arg)
{
    if (mTrayMgr->injectMouseMove(arg)) return true;
    if(mGameState != 0)
        mCameraMan->injectMouseMove(arg);
    return true;
}
//---------------------------------------------------------------------------
bool BaseApplication::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
    if (mTrayMgr->injectMouseDown(arg, id)) return true;
    if(mGameState != 0)
        mCameraMan->injectMouseDown(arg, id);
    return true;
}
//---------------------------------------------------------------------------
bool BaseApplication::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
    if (mTrayMgr->injectMouseUp(arg, id)) return true;
    if(mGameState != 0)
        mCameraMan->injectMouseUp(arg, id);
    return true;
}
void BaseApplication::buttonHit(OgreBites::Button* button)
{
    if(button->getName().compare("single") == 0 )
    {
        mTrayMgr->destroyWidget("single");
        mTrayMgr->destroyWidget("multi");
        mTrayMgr->destroyWidget("menuLabel");
        mGameState = 1; // singleMode
        createObjects();
        createGUI();
        mTrayMgr->hideCursor();
        /**************STARTS THE GAME FOR SINGLE PLAYER**************************/
    }
    else if(button->getName().compare("multi") == 0 )
    {
        mTrayMgr->destroyWidget("single");
        mTrayMgr->destroyWidget("multi");
        setupHostOrJoinGUI();
        // vector<float>* result = mNetworkWrapper->decode("x:1.534y:532.3245z:-456.34points:2rounds:3");
        // for(int i = 0; i < result->size(); i++)
        // {
        //     std::cout << "result[" << i << "] = " << (*result)[i] << std::endl;
        // }
        // delete result;
    }
    else if(button->getName().compare("host") == 0 )
    {
        mTrayMgr->destroyWidget("host");
        mTrayMgr->destroyWidget("join");
        mTrayMgr->destroyWidget("hostOrJoinBack");
        setupHostGUI();

        //search for client
        mNetworkWrapper->initNetwork(true);
        bool foundClient = mNetworkWrapper->findClient();
        if(foundClient)
        {
            mTrayMgr->destroyWidget("cancelHost");
            mTrayMgr->destroyWidget("menuLabel");
            mGameState = 2; // multiplayer host
            createObjects();
            createGUI();
            mTrayMgr->hideCursor();
            /**************STARTS THE GAME FOR HOST**************************/
        }
        else
        {
            mNetworkWrapper->closeSocket();
            delete mNetworkWrapper;
            mNetworkWrapper = new NetworkWrapper();
            mMenuLabel->setCaption("Failed to find Client");

        }
    }
    else if(button->getName().compare("join") == 0 )
    {
        mTrayMgr->destroyWidget("host");
        mTrayMgr->destroyWidget("join");
        mTrayMgr->destroyWidget("hostOrJoinBack");
        setupJoinGUI();

        //search for server
        mNetworkWrapper->initNetwork(false);
        bool foundServer = mNetworkWrapper->findServer();
        if(foundServer)
        {
            mTrayMgr->destroyWidget("cancelJoin");
            mTrayMgr->destroyWidget("menuLabel");
            mGameState = 3; // multiplayer client
            createObjects();
            createGUI();
            mTrayMgr->hideCursor();
            /**************STARTS THE GAME FOR CLIENT**************************/
        }
        else
        {
            mNetworkWrapper->closeSocket();
            delete mNetworkWrapper;
            mNetworkWrapper = new NetworkWrapper();
            mMenuLabel->setCaption("Failed to find server");

        }
    }
    else if(button->getName().compare("hostOrJoinBack") == 0 )
    {

        mTrayMgr->destroyWidget("host");
        mTrayMgr->destroyWidget("join");
        mTrayMgr->destroyWidget("hostOrJoinBack");
        mTrayMgr->destroyWidget("menuLabel");
        setupSingleOrMultiGUI();
    }
    else if(button->getName().compare("cancelHost") == 0 )
    {
        mNetworkWrapper->cancelSearch(); // might "break" the code
        mTrayMgr->destroyWidget("cancelHost");
        setupHostOrJoinGUI();
    }
    else if(button->getName().compare("cancelJoin") == 0 )
    {
        //add netowrking
        mTrayMgr->destroyWidget("cancelJoin");
        setupHostOrJoinGUI();
    }
    else if(button->getName().compare("result") == 0 )
    {
        //add netowrking
        mTrayMgr->destroyWidget("result");
        mTrayMgr->destroyWidget("TESTEND");
        mTrayMgr->hideCursor();
    }
}

// void BaseApplication::setupHostOrJoinGUI(void)
// {
//     mMenuLabel->setCaption("host or join game");
//     mButton1 = mTrayMgr->createButton(OgreBites::TL_CENTER, "host", "Host Game", 220);
//     mButton2 = mTrayMgr->createButton(OgreBites::TL_CENTER, "join", "Join Game", 220);
//     mButtonBack = mTrayMgr->createButton(OgreBites::TL_CENTER, "hostOrJoinBack", "Back", 220);
// }

// void BaseApplication::setupHostGUI(void)
// {
//     mMenuLabel->setCaption("searching for client...");
//     mButtonBack = mTrayMgr->createButton(OgreBites::TL_CENTER, "cancelHost", "Cancel", 220);
// }

// void BaseApplication::setupJoinGUI(void)
// {
//     mMenuLabel->setCaption("searching for host...");
//     mButtonBack = mTrayMgr->createButton(OgreBites::TL_CENTER, "cancelJoin", "Cancel", 220);
// }
//---------------------------------------------------------------------------
// Adjust mouse clipping area
void BaseApplication::windowResized(Ogre::RenderWindow* rw)
{
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

    const OIS::MouseState &ms = mMouse->getMouseState();
    ms.width = width;
    ms.height = height;
}
//---------------------------------------------------------------------------
// Unattach OIS before window shutdown (very important under Linux)
void BaseApplication::windowClosed(Ogre::RenderWindow* rw)
{
    // Only close for window that created OIS (the main window in these demos)
    if(rw == mWindow)
    {
        if(mInputManager)
        {
            mInputManager->destroyInputObject(mMouse);
            mInputManager->destroyInputObject(mKeyboard);

            OIS::InputManager::destroyInputSystem(mInputManager);
            mInputManager = 0;
        }
    }
}
//---------------------------------------------------------------------------