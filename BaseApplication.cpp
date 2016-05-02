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

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

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
    mDifficulty(1),
    mLevel(1),
    mGameStart(false),
    mInMenu(false),
    mMusic(true)//,
    // mButtonLevels()
{
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
    m_ResourcePath = Ogre::macBundlePath() + "/Contents/Resources/";
#else
    m_ResourcePath = "";
#endif

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
    delete player;
    delete gameMap;
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

    mCamera->setPosition(Ogre::Vector3(0,0,80));
    mCamera->lookAt(Ogre::Vector3(0,0,-300));
    mCamera->setNearClipDistance(5);

    mCameraMan = new OgreBites::SdkCameraMan(mCamera);   // Create a default camera controller
}

//*-----------------------------------menu setup ------------------------------*//
void BaseApplication::setupMainMenu(void)
{
    mMenuLabel = mTrayMgr->createLabel(OgreBites::TL_CENTER, "menuLabel", "\"Game's Name\"", 250);
    mTrayMgr->moveWidgetToTray(mMenuLabel, OgreBites::TL_TOP, 0);
    mTrayMgr->createButton(OgreBites::TL_CENTER, "start", "Start Game", 250);
    mTrayMgr->createButton(OgreBites::TL_CENTER, "sound", "Sound Option", 250);
    mTrayMgr->createButton(OgreBites::TL_CENTER, "credit", "Credit Page", 250);
    mTrayMgr->createButton(OgreBites::TL_CENTER, "quit", "Quit Game", 250);
    mTrayMgr->showCursor();  
}

void BaseApplication::setupLevelMenu(void)
{
    removeGUI();
    mInMenu = true;
    mMenuLabel = mTrayMgr->createLabel(OgreBites::TL_CENTER, "pauseLabel", "Paused", 250);
    mTrayMgr->moveWidgetToTray(mMenuLabel, OgreBites::TL_CENTER, 0);
    mTrayMgr->createButton(OgreBites::TL_CENTER, "resume level", "Resume the Fun", 250);
    mTrayMgr->createButton(OgreBites::TL_CENTER, "quit level", "Back to Main Menu", 250);
    mTrayMgr->showCursor();
}
void BaseApplication::removeLevelMenu(void)
{
    mInMenu = false;
    mTrayMgr->destroyWidget("pauseLabel");
    mTrayMgr->destroyWidget("quit level");
    mTrayMgr->destroyWidget("resume level");
    mTrayMgr->hideCursor();
}

void BaseApplication::setupSoundMenu(void)
{
    mTrayMgr->createButton(OgreBites::TL_CENTER, "on", "Sound ON", 250);
    mTrayMgr->createButton(OgreBites::TL_CENTER, "off", "Sound OFF", 250);
}

void BaseApplication::setupDifficultyMenu(void)
{
    mMenuLabel = mTrayMgr->createLabel(OgreBites::TL_CENTER, "menuLabel", "Select Difficulty", 250);
    mTrayMgr->createButton(OgreBites::TL_CENTER, "intro", "Intro level", 250);
    mTrayMgr->createButton(OgreBites::TL_CENTER, "medium", "Medium level", 250);
    mTrayMgr->createButton(OgreBites::TL_CENTER, "hard", "Hard level", 250);
    mTrayMgr->createButton(OgreBites::TL_CENTER, "extreme", "Extreme level", 250);
    mButtonBack = mTrayMgr->createButton(OgreBites::TL_CENTER, "back to main menu", "Back to Main Menu", 250);

}

void BaseApplication::setupIntroLevelSelect(void)
{
    mMenuLabel = mTrayMgr->createLabel(OgreBites::TL_CENTER, "menuLabel", "Select Level", 250);
    for(int x = 1; x <= Level::numIntroLevels(); x++)
    {
        mTrayMgr->createButton(OgreBites::TL_CENTER, "intro " + patch::to_string(x), Level::getName(1,x), 250);
    }
    mButtonBack = mTrayMgr->createButton(OgreBites::TL_CENTER, "back to select difficulty from intro", "Back to Select Difficulty", 250);
}

void BaseApplication::setupMediumLevelSelect(void)
{
    mMenuLabel = mTrayMgr->createLabel(OgreBites::TL_CENTER, "menuLabel", "Select Level", 250);
    for(int x = 1; x <= Level::numMediumLevels(); x++)
    {
        mTrayMgr->createButton(OgreBites::TL_CENTER, "medium " + patch::to_string(x), Level::getName(2,x), 250);
    }
    mButtonBack = mTrayMgr->createButton(OgreBites::TL_CENTER, "back to select difficulty from medium", "Back to Select Difficulty", 250);
}

void BaseApplication::setupHardLevelSelect(void)
{
    mMenuLabel = mTrayMgr->createLabel(OgreBites::TL_CENTER, "menuLabel", "Select Level", 250);
    for(int x = 1; x <= Level::numHardLevels(); x++)
    {
        mTrayMgr->createButton(OgreBites::TL_CENTER, "hard " + patch::to_string(x), Level::getName(3,x), 250);
    }
    mButtonBack = mTrayMgr->createButton(OgreBites::TL_CENTER, "back to select difficulty from hard", "Back to Select Difficulty", 250);
}

void BaseApplication::setupExtremeLevelSelect(void)
{
    mMenuLabel = mTrayMgr->createLabel(OgreBites::TL_CENTER, "menuLabel", "Select Level", 250);
    for(int x = 1; x <= Level::numExtremeLevels(); x++)
    {
        mTrayMgr->createButton(OgreBites::TL_CENTER, "extreme " + patch::to_string(x), Level::getName(4,x), 250);
    }
    mButtonBack = mTrayMgr->createButton(OgreBites::TL_CENTER, "back to select difficulty from extreme", "Back to Select Difficulty", 250);
}



void BaseApplication::setupGUI(std::string levelName)
{
    mLevelName = mTrayMgr->createLabel(OgreBites::TL_TOP, "levelName", levelName, 500);
    mLevelName->show();
    mPlayerHp = mTrayMgr->createProgressBar(OgreBites::TL_TOP, "hpBar", "100/100", 200, 20);
    mPlayerHp->show();

    /************************************select menu Gui ****************************************************/
    mTrayMgr->moveWidgetToTray(mPlayerHp, OgreBites::TL_TOP, 0);
    mTrayMgr->moveWidgetToTray(mLevelName, OgreBites::TL_TOP, 0);
}

void BaseApplication::removeGUI()
{
    mTrayMgr->destroyWidget("levelName");
    mTrayMgr->destroyWidget("hpBar");
}
//---------------------------------------------------------------------------

void BaseApplication::createObjects()
{
    Ogre::SceneNode* node;
    Ogre::SceneNode* playerNode;
    //name doesnt mater rakans code is boosted
    player = new Player("playerNode", mSceneMgr, playerNode, 10., Ogre::Vector3(-25.,-250.,225.));
 
    gameMap = new Map(player, mSceneMgr, Ogre::Vector3(-225.0,-250.0, -225.0), mDifficulty, mLevel);
   
}

void BaseApplication::deleteMap()
{
    delete gameMap;
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
    // mTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
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
          
    setupMainMenu();

    return true;
};
//---------------------------------------------------------------------------
void BaseApplication::calcNextLevel()
{
    mLevel++;
    if(mDifficulty == 1 && mLevel > Level::numIntroLevels()) //num intro levels
    {
        mLevel = 1;
        mDifficulty++;
    }
    if(mDifficulty == 2 && mLevel > Level::numMediumLevels()) //num intro levels
    {
        mLevel = 1;
        mDifficulty++;
    }
    if(mDifficulty == 3 && mLevel > Level::numHardLevels()) //num intro levels
    {
        mLevel = 1;
        mDifficulty++;
    }
    if(mDifficulty == 4 && mLevel > Level::numExtremeLevels()) //num intro levels
    {
        mLevel = 1;
        mDifficulty++;
    }
    if(mDifficulty == 5 && mLevel > Level::numCreditLevels()) //num intro levels
    {
        mLevel = 1;
        mDifficulty++;
        // do whatever the **** we want
    }
    if(mDifficulty > Level::numDifficulties())
    {
        //ran out of levels sad face
        // open main menu for level select
        mLevel = 1;
        mDifficulty = 1;
    }
}   
bool scored = false;
int points = 0;
bool wisDown = false;
bool disDown = false;
bool sisDown = false;
bool aisDown = false;
bool BaseApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    if(mWindow->isClosed())
        return false;

    //run save code then shut down

    if(mShutDown)
        return false;

    // Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();
    if(!mMusic)
    {
        Mix_VolumeMusic(0);
    }
    else
    {
        Mix_VolumeMusic(45);
    }

    if(mGameStart && !mInMenu)
    {
        if(player->levelFinished)
        {
            calcNextLevel();
            deleteMap();
            createObjects();
            mLevelName->setCaption(gameMap->getName());
        }
        mPlayerHp->setProgress((player->health)/100.0);
        mPlayerHp->setCaption("current HP is " + patch::to_string(player->health) + "/100");
        Ogre::SceneNode* tem = mSceneMgr->getSceneNode("playerNode");    
        Ogre::Vector3 position = tem->getPosition();
        mCamera->setPosition(position.x , 300, position.z+200);
        if(wisDown)
            gameMap->move(0);
        else if(disDown)
            gameMap->move(1);
        else if(sisDown)
            gameMap->move(2);
        else if(aisDown)
            gameMap->move(3);
        gameMap->simulate(evt.timeSinceLastFrame);
        // mSimulator->stepSimulation(evt.timeSinceLastFrame, music2);
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
    else if(arg.key == OIS::KC_SPACE)
    {
        mShutDown = true;
    }
    else if(arg.key == OIS::KC_RETURN)
    {

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
        if(!mGameStart)
            ;
        else if(!mInMenu)
        {
            setupLevelMenu();
        }
        else if(mInMenu)
        {
            removeLevelMenu();
            setupGUI(gameMap->getName());
        }
    }
    else if(arg.key == OIS::KC_W || arg.key == OIS::KC_UP )
    {
        wisDown = true;
    }
    else if(arg.key == OIS::KC_D || arg.key == OIS::KC_RIGHT )
    {
        disDown = true;
    }
    else if(arg.key == OIS::KC_S || arg.key == OIS::KC_DOWN)
    {
        sisDown = true;
    }
    else if(arg.key == OIS::KC_A||  arg.key == OIS::KC_LEFT)
    {
        aisDown = true;
    }

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
    if(!(arg.key == OIS::KC_W ||
            arg.key == OIS::KC_A ||
            arg.key == OIS::KC_S ||
            arg.key == OIS::KC_D || arg.key == OIS::KC_UP ||
             arg.key == OIS::KC_DOWN ||
            arg.key == OIS::KC_RIGHT ||
             arg.key == OIS::KC_LEFT))
    {
        mCameraMan->injectKeyDown(arg);
    }
    return true;
}
//---------------------------------------------------------------------------
bool BaseApplication::keyReleased(const OIS::KeyEvent &arg)
{
    if(arg.key == OIS::KC_W || arg.key == OIS::KC_UP )
    {
        wisDown = false;
    }
    else if(arg.key == OIS::KC_D || arg.key == OIS::KC_RIGHT )
    {
        disDown = false;
    }
    else if(arg.key == OIS::KC_S || arg.key == OIS::KC_DOWN)
    {
        sisDown = false;
    }
    else if(arg.key == OIS::KC_A||  arg.key == OIS::KC_LEFT)
    {
        aisDown = false;
    }
    mCameraMan->injectKeyUp(arg);
    return true;
}
//---------------------------------------------------------------------------
bool BaseApplication::mouseMoved(const OIS::MouseEvent &arg)
{
    if (mTrayMgr->injectMouseMove(arg)) return true;
    //mCameraMan->injectMouseMove(arg);
    return true;
}
//---------------------------------------------------------------------------
bool BaseApplication::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
    if (mTrayMgr->injectMouseDown(arg, id)) return true;
    mCameraMan->injectMouseDown(arg, id);
    return true;
}
//---------------------------------------------------------------------------
bool BaseApplication::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
    if (mTrayMgr->injectMouseUp(arg, id)) return true;
    mCameraMan->injectMouseUp(arg, id);
    return true;
}
void BaseApplication::buttonHit(OgreBites::Button* button)
{
    if(button->getName().compare("start") == 0)        
    {       
        mTrayMgr->destroyWidget("menuLabel");
        mTrayMgr->destroyWidget("start");       
        mTrayMgr->destroyWidget("sound");       
        mTrayMgr->destroyWidget("credit");
        mTrayMgr->destroyWidget("quit");  
        setupDifficultyMenu();        
        return;
    }       
    else if(button->getName().compare("sound") == 0 )
    {
        mTrayMgr->destroyWidget("menuLabel");
        mTrayMgr->destroyWidget("start");       
        mTrayMgr->destroyWidget("sound");       
        mTrayMgr->destroyWidget("credit");
        mTrayMgr->destroyWidget("quit");   
        setupSoundMenu();
        return;
    }
    else if(button->getName().compare("credit") == 0)
    {
        mTrayMgr->destroyWidget("menuLabel");
        mTrayMgr->destroyWidget("start");       
        mTrayMgr->destroyWidget("sound");       
        mTrayMgr->destroyWidget("credit");
        mTrayMgr->destroyWidget("quit");

        mDifficulty =5;
        mLevel = 1; 
        createObjects();              
        mGameStart= true;        
        mTrayMgr->hideCursor();      
        setupGUI(gameMap->getName()); 
        return;   

    }
    else if(button->getName().compare("quit") == 0)
    {
        mShutDown = true;
    }
    else if(button->getName().compare("on") == 0 )
    {
        mTrayMgr->destroyWidget("on");       
        mTrayMgr->destroyWidget("off");  
        mMusic = true;        
        setupMainMenu();
        return;
    }
    else if(button->getName().compare("off") == 0 )
    {
        mTrayMgr->destroyWidget("on");       
        mTrayMgr->destroyWidget("off");   
        mMusic = false;       
        setupMainMenu();
        return;
    }
    else if(button->getName().compare("intro") == 0 )       
    {       
        mTrayMgr->destroyWidget("intro"); 
        mTrayMgr->destroyWidget("medium"); 
        mTrayMgr->destroyWidget("hard"); 
        mTrayMgr->destroyWidget("extreme"); 
        mTrayMgr->destroyWidget("back to main menu");  
        mTrayMgr->destroyWidget("menuLabel");
        setupIntroLevelSelect();        
        return;  
    }
    else if(button->getName().compare("medium") == 0 )       
    {       
        mTrayMgr->destroyWidget("intro"); 
        mTrayMgr->destroyWidget("medium"); 
        mTrayMgr->destroyWidget("hard"); 
        mTrayMgr->destroyWidget("extreme"); 
        mTrayMgr->destroyWidget("back to main menu");  
        mTrayMgr->destroyWidget("menuLabel");
        setupMediumLevelSelect();        
        return;  
    }
    else if(button->getName().compare("hard") == 0 )       
    {       
        mTrayMgr->destroyWidget("intro"); 
        mTrayMgr->destroyWidget("medium"); 
        mTrayMgr->destroyWidget("hard"); 
        mTrayMgr->destroyWidget("extreme"); 
        mTrayMgr->destroyWidget("back to main menu");  
        mTrayMgr->destroyWidget("menuLabel");
        setupHardLevelSelect();        
        return;  
    }
    else if(button->getName().compare("extreme") == 0 )       
    {       
        mTrayMgr->destroyWidget("intro"); 
        mTrayMgr->destroyWidget("medium"); 
        mTrayMgr->destroyWidget("hard"); 
        mTrayMgr->destroyWidget("extreme"); 
        mTrayMgr->destroyWidget("back to main menu");  
        mTrayMgr->destroyWidget("menuLabel");
        setupExtremeLevelSelect();        
        return;  
    }
    else if(button->getName().compare("back to main menu") == 0 )
    {
        mTrayMgr->destroyWidget("intro"); 
        mTrayMgr->destroyWidget("medium"); 
        mTrayMgr->destroyWidget("hard"); 
        mTrayMgr->destroyWidget("extreme"); 
        mTrayMgr->destroyWidget("back to main menu");  
        mTrayMgr->destroyWidget("menuLabel");
        setupMainMenu(); 
        return;
    }
    else if(button->getName().compare("back to select difficulty from intro") == 0 )
    {
        mTrayMgr->destroyWidget("menuLabel");
        for(int x = 1; x <= Level::numIntroLevels(); x++)
        {
            mTrayMgr->destroyWidget("intro " + patch::to_string(x));
        }
        mTrayMgr->destroyWidget("back to select difficulty from intro");
        setupDifficultyMenu();   
        return;
    }  
    else if(button->getName().compare("back to select difficulty from medium") == 0 )
    {
        mTrayMgr->destroyWidget("menuLabel");
        for(int x = 1; x <= Level::numMediumLevels(); x++)
        {
            mTrayMgr->destroyWidget("medium " + patch::to_string(x));
        } 
        mTrayMgr->destroyWidget("back to select difficulty from medium");
        setupDifficultyMenu();   
        return;
    }  
    else if(button->getName().compare("back to select difficulty from hard") == 0 )
    {
        mTrayMgr->destroyWidget("menuLabel");
        for(int x = 1; x <= Level::numHardLevels(); x++)
        {
            mTrayMgr->destroyWidget("hard " + patch::to_string(x));
        } 
        mTrayMgr->destroyWidget("back to select difficulty from hard");
        setupDifficultyMenu();   
        return;
    }  
    else if(button->getName().compare("back to select difficulty from extreme") == 0 )
    {
        mTrayMgr->destroyWidget("menuLabel");
        for(int x = 1; x <= Level::numExtremeLevels(); x++)
        {
            mTrayMgr->destroyWidget("extreme " + patch::to_string(x));
        } 
        mTrayMgr->destroyWidget("back to select difficulty from extreme");
        setupDifficultyMenu();   
        return;
    }  
    for(int i = 1; i <= Level::numIntroLevels(); i++)
    {
        std::string name = "intro "+ patch::to_string(i);
        if(button->getName().compare(name) == 0 )
        {
            mTrayMgr->destroyWidget("menuLabel");
            for(int x = 1; x <= Level::numIntroLevels(); x++)
            {
                mTrayMgr->destroyWidget("intro " + patch::to_string(x));
            } 
            mTrayMgr->destroyWidget("back to select difficulty from intro");
            mDifficulty =1;
            mLevel = i; 
            createObjects();              
            mGameStart = true;        
            mTrayMgr->hideCursor();      
            setupGUI(gameMap->getName()); 
            return;   
        }
    }
    for(int i = 1; i <= Level::numMediumLevels(); i++)
    {
        std::string name = "medium "+ patch::to_string(i);
        if(button->getName().compare(name) == 0 )
        {
            mTrayMgr->destroyWidget("menuLabel");
            for(int x = 1; x <= Level::numMediumLevels(); x++)
            {
                mTrayMgr->destroyWidget("medium " + patch::to_string(x));
            } 
            mTrayMgr->destroyWidget("back to select difficulty from medium");
            mDifficulty =2;
            mLevel = i; 
            createObjects();              
            mGameStart= true;        
            mTrayMgr->hideCursor();      
            setupGUI(gameMap->getName()); 
            return;   
        }
    }
    for(int i = 1; i <= Level::numHardLevels(); i++)
    {
        std::string name = "hard "+ patch::to_string(i);
        if(button->getName().compare(name) == 0 )
        {
            mTrayMgr->destroyWidget("menuLabel");
            for(int x = 1; x <= Level::numHardLevels(); x++)
            {
                mTrayMgr->destroyWidget("hard " + patch::to_string(x));
            } 
            mTrayMgr->destroyWidget("back to select difficulty from hard");
            mDifficulty =3;
            mLevel = i; 
            createObjects();              
            mGameStart= true;        
            mTrayMgr->hideCursor();      
            setupGUI(gameMap->getName()); 
            return;   
        }
    }
    for(int i = 1; i <= Level::numExtremeLevels(); i++)
    {
        std::string name = "extreme "+ patch::to_string(i);
        if(button->getName().compare(name) == 0 )
        {
            mTrayMgr->destroyWidget("menuLabel");
            for(int x = 1; x <= Level::numExtremeLevels(); x++)
            {
                mTrayMgr->destroyWidget("extreme " + patch::to_string(x));
            } 
            mTrayMgr->destroyWidget("back to select difficulty from extreme");
            mDifficulty =4;
            mLevel = i; 
            createObjects();              
            mGameStart= true;        
            mTrayMgr->hideCursor();      
            setupGUI(gameMap->getName()); 
            return; 
        }
    }


    if(button->getName().compare("quit level") == 0 )
    {
        removeLevelMenu();
        deleteMap();
        mGameStart = false;
        setupMainMenu();
        return;
    }
    else if(button->getName().compare("resume level") == 0 )
    {
        removeLevelMenu();
        setupGUI(gameMap->getName());
        return;
    }


   
}
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