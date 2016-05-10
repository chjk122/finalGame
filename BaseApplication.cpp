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
    mOldDifficulty(0),
    mDifficulty(0),
    mLevel(1),
    mGameStart(false),
    mInMenu(false),
    mMusic(true),
    mDeathCounter(0),
    mStats(),
    mStopwatch(),
    mUsername(""),
    mPassword(""),
    mTypingUsername(false),
    mTypingPassword(false),
    mCanRespawn(false)
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
    delete player;
    delete gameMap;
    delete mStats;
    delete mStopwatch;

    // Remove ourself as a Window listener
    Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
    windowClosed(mWindow);
    delete mRoot;
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
    mMenuLabel = mTrayMgr->createLabel(OgreBites::TL_CENTER, "menuLabel", "Cubester's Maze", 250);
    mTrayMgr->moveWidgetToTray(mMenuLabel, OgreBites::TL_TOP, 0);
    mTrayMgr->createLabel(OgreBites::TL_CENTER, "label", "Main Menu", 250);
    mTrayMgr->createButton(OgreBites::TL_CENTER, "account", "Account Info", 250);
    mTrayMgr->createButton(OgreBites::TL_CENTER, "start", "Start Game", 250);
    mTrayMgr->createButton(OgreBites::TL_CENTER, "help", "Help", 250);
    mTrayMgr->createButton(OgreBites::TL_CENTER, "sound", "Sound Option", 250);
    mTrayMgr->createButton(OgreBites::TL_CENTER, "credit", "Credit Page", 250);
    mTrayMgr->createButton(OgreBites::TL_CENTER, "quit", "Quit Game", 250);
    mTrayMgr->showCursor();  
}

void BaseApplication::removeMainMenu(void)
{
    mTrayMgr->destroyWidget("label");
    mTrayMgr->destroyWidget("menuLabel");
    mTrayMgr->destroyWidget("account");
    mTrayMgr->destroyWidget("start");
    mTrayMgr->destroyWidget("help");        
    mTrayMgr->destroyWidget("sound");       
    mTrayMgr->destroyWidget("credit");
    mTrayMgr->destroyWidget("quit");  
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

void BaseApplication::setupHelpMenu(void)
{
    mMenuLabel = mTrayMgr->createLabel(OgreBites::TL_TOP, "menuLabel", "Cubester's Maze", 250);
    mTrayMgr->createLabel(OgreBites::TL_CENTER, "label", "Help Menu", 250);
    mTrayMgr->createButton(OgreBites::TL_CENTER, "control", "Controls", 250);
    mTrayMgr->createButton(OgreBites::TL_CENTER, "info", "Info", 250);
    mTrayMgr->createButton(OgreBites::TL_CENTER, "helpToMain", "Back To Main Menu", 250);
}

void BaseApplication::removeHelpMenu(void)
{
    mTrayMgr->destroyWidget("menuLabel");
    mTrayMgr->destroyWidget("label");
    mTrayMgr->destroyWidget("control");
    mTrayMgr->destroyWidget("info");
    mTrayMgr->destroyWidget("helpToMain");
}

void BaseApplication::setupControlMenu(void)
{
    mMenuLabel = mTrayMgr->createLabel(OgreBites::TL_TOP, "menuLabel", "Cubester's Maze", 250);
    mTrayMgr->createLabel(OgreBites::TL_CENTER, "label1", "W/Arrow up key for moving up\nS/Arrow down key for moving down\nA/Arrow left key for moving left\nD/Arrow right key for moving right\nEsc key for pause the game or quit\nSpace to respawn when dead", 400);
    OgreBites::Label *will = mTrayMgr->createLabel(OgreBites::TL_CENTER, "label2", "S/Arrow down key for moving down", 400);
    will->hide();
    will = mTrayMgr->createLabel(OgreBites::TL_CENTER, "label3", "A/Arrow left key for moving left", 400);
    will->hide();
    will = mTrayMgr->createLabel(OgreBites::TL_CENTER, "label4", "A/Arrow left key for moving left", 400);
    will->hide();
    mTrayMgr->createButton(OgreBites::TL_CENTER, "back from control", "Back", 400);
}

void BaseApplication::removeControlMenu(void)
{
    mTrayMgr->destroyWidget("menuLabel");
    mTrayMgr->destroyWidget("label1");
    mTrayMgr->destroyWidget("label2");
    mTrayMgr->destroyWidget("label3");
    mTrayMgr->destroyWidget("label4");
    mTrayMgr->destroyWidget("back from control");
}

void BaseApplication::setupInfoMenu(void)
{
    mMenuLabel = mTrayMgr->createLabel(OgreBites::TL_TOP, "menuLabel", "Cubester's Maze", 250);
    mTrayMgr->createLabel(OgreBites::TL_CENTER, "label1", std::string("DAMAGE TILES\n") +
                                                          std::string("Poison: 2 Hp/Tile removed on Cure Tile\n")+
                                                          std::string("Lava: 5 Hp/Tile removed in water or wears off\n")+
                                                          std::string("Spike: Deals 39 Hp\n")+
                                                          std::string("SPECIAL TILES\n")+
                                                          std::string("Ice: Slide on it\n")+
                                                          std::string("Water: Drown when bubbles is 0\n")+
                                                          std::string("Cure: Removes Poison\n")+
                                                          std::string("Door: Needs a key to open\n")+
                                                          std::string("Key: Gives one key\n"), 400);
    OgreBites::Label *will = mTrayMgr->createLabel(OgreBites::TL_CENTER, "label2", "S/Arrow down key for moving down", 400);
    will->hide();
    will = mTrayMgr->createLabel(OgreBites::TL_CENTER, "label3", "A/Arrow left key for moving left", 400);
    will->hide();
    will = mTrayMgr->createLabel(OgreBites::TL_CENTER, "label4", "A/Arrow left key for moving left", 400);
    will->hide();
    will = mTrayMgr->createLabel(OgreBites::TL_CENTER, "label5", "A/Arrow left key for moving left", 400);
    will->hide();
    will = mTrayMgr->createLabel(OgreBites::TL_CENTER, "label6", "A/Arrow left key for moving left", 400);
    will->hide();
    mTrayMgr->createButton(OgreBites::TL_CENTER, "back from info", "Back", 400);
}

void BaseApplication::removeInfoMenu(void)
{
    mTrayMgr->destroyWidget("menuLabel");
    mTrayMgr->destroyWidget("label1");
    mTrayMgr->destroyWidget("label2");
    mTrayMgr->destroyWidget("label3");
    mTrayMgr->destroyWidget("label4");
    mTrayMgr->destroyWidget("label5");
    mTrayMgr->destroyWidget("label6");
    mTrayMgr->destroyWidget("back from info");
}

void BaseApplication::setupAccountMenu(void)
{
    mMenuLabel = mTrayMgr->createLabel(OgreBites::TL_CENTER, "accoutLabel", "Account Info", 250);
    if(mUsername != "")
        mMenuLabel->setCaption("Hello " + mUsername);
    mTrayMgr->moveWidgetToTray(mMenuLabel, OgreBites::TL_CENTER, 0);
    mButtonBack = mTrayMgr->createButton(OgreBites::TL_CENTER, "create", "New Account", 250);
    if(mUsername != "")
    {
        mButtonBack->hide();
    }
    mButtonBack = mTrayMgr->createButton(OgreBites::TL_CENTER, "login", "Log In", 250);
    if(mUsername != "")
    {
        mButtonBack->hide();
    }
    mButtonBack = mTrayMgr->createButton(OgreBites::TL_CENTER, "logout", "Log Out", 250);
    if(mUsername == "")
    {
        mButtonBack->hide();
    }
    mTrayMgr->createButton(OgreBites::TL_CENTER, "backfromsetup", "Back", 250);
    mTrayMgr->showCursor();
}

void BaseApplication::removeAccountMenu(void)
{
    mTrayMgr->destroyWidget("accoutLabel");
    mTrayMgr->destroyWidget("create");
    mTrayMgr->destroyWidget("login");
    mTrayMgr->destroyWidget("logout");
    mTrayMgr->destroyWidget("backfromsetup");
}

void BaseApplication::setupCreateAccountMenu(void)
{
    mMenuLabel = mTrayMgr->createLabel(OgreBites::TL_CENTER, "createAccoutLabel", "Click Then Type", 250);
    mTrayMgr->moveWidgetToTray(mMenuLabel, OgreBites::TL_CENTER, 0);
    mUsernameButton = mTrayMgr->createButton(OgreBites::TL_CENTER, "create uname", "Enter Username", 250);
    mPasswordButton = mTrayMgr->createButton(OgreBites::TL_CENTER, "create pass", "Enter Password", 250);
    mTrayMgr->createButton(OgreBites::TL_CENTER, "confirm account", "Create Account", 250);
    mTrayMgr->createButton(OgreBites::TL_CENTER, "back from create account", "Back", 250);
    mTrayMgr->showCursor();
}

void BaseApplication::removeCreateAccountMenu(void)
{
    mTrayMgr->destroyWidget("createAccoutLabel");
    mTrayMgr->destroyWidget("create uname");
    mTrayMgr->destroyWidget("create pass");
    mTrayMgr->destroyWidget("confirm account");
    mTrayMgr->destroyWidget("back from create account");
}

void BaseApplication::setupLoginMenu(void)
{
    mMenuLabel = mTrayMgr->createLabel(OgreBites::TL_CENTER, "loginLabel", "Click Then Type", 250);
    mTrayMgr->moveWidgetToTray(mMenuLabel, OgreBites::TL_CENTER, 0);
    mUsernameButton = mTrayMgr->createButton(OgreBites::TL_CENTER, "login uname", "Enter Username", 250);
    mPasswordButton = mTrayMgr->createButton(OgreBites::TL_CENTER, "login pass", "Enter Password", 250);
    mTrayMgr->createButton(OgreBites::TL_CENTER, "login to account", "Login", 250);
    mTrayMgr->createButton(OgreBites::TL_CENTER, "back from login", "Back", 250);
    mTrayMgr->showCursor();
}

void BaseApplication::removeLoginMenu(void)
{
    mTrayMgr->destroyWidget("loginLabel");
    mTrayMgr->destroyWidget("login uname");
    mTrayMgr->destroyWidget("login pass");
    mTrayMgr->destroyWidget("login to account");
    mTrayMgr->destroyWidget("back from login");
}

void BaseApplication::setupSoundMenu(void)
{
    mTrayMgr->createLabel(OgreBites::TL_CENTER, "label", "Sound Option", 250);
    mTrayMgr->createButton(OgreBites::TL_CENTER, "on", "All Sound ON", 250);
    mTrayMgr->createButton(OgreBites::TL_CENTER, "off", "All Sound OFF", 250);
    mTrayMgr->createButton(OgreBites::TL_CENTER, "bgm on", "Background Sound ON", 250);
    mTrayMgr->createButton(OgreBites::TL_CENTER, "bgm off", "Background Sound OFF", 250);
    mTrayMgr->createButton(OgreBites::TL_CENTER, "effect on", "Sound Effect ON", 250);
    mTrayMgr->createButton(OgreBites::TL_CENTER, "effect off", "Sound Effect OFF", 250);
    mTrayMgr->createButton(OgreBites::TL_CENTER, "sound to main", "Back To Main Menu", 250);
}

void BaseApplication::removeSoundMenu(void)
{
    mTrayMgr->destroyWidget("label");
    mTrayMgr->destroyWidget("on");
    mTrayMgr->destroyWidget("off");
    mTrayMgr->destroyWidget("bgm on");
    mTrayMgr->destroyWidget("bgm off");
    mTrayMgr->destroyWidget("effect on");
    mTrayMgr->destroyWidget("effect off");
    mTrayMgr->destroyWidget("sound to main");
}

void BaseApplication::setupDifficultyMenu(void)
{
    mMenuLabel = mTrayMgr->createLabel(OgreBites::TL_CENTER, "menuLabel", "Select Difficulty", 250);
    mTrayMgr->createButton(OgreBites::TL_CENTER, "intro", "Intro level", 250);
    mTrayMgr->createButton(OgreBites::TL_CENTER, "medium", "Medium level", 250);
    mTrayMgr->createButton(OgreBites::TL_CENTER, "hard", "Hard level", 250);
    mTrayMgr->createButton(OgreBites::TL_CENTER, "extreme", "Extreme level", 250);
    mTrayMgr->createButton(OgreBites::TL_CENTER, "back to main menu", "Back to Main Menu", 250);
}

void BaseApplication::removeDifficultyMenu(void)
{
    mTrayMgr->destroyWidget("intro"); 
    mTrayMgr->destroyWidget("medium"); 
    mTrayMgr->destroyWidget("hard"); 
    mTrayMgr->destroyWidget("extreme"); 
    mTrayMgr->destroyWidget("back to main menu");  
    mTrayMgr->destroyWidget("menuLabel");
}

void BaseApplication::setupLevelSelect(int diff)
{
    mMenuLabel = mTrayMgr->createLabel(OgreBites::TL_CENTER, "menuLabel", "Select Level", 250);
    for(int x = 1; x <= Level::numLevels(diff); x++)
    {
        mTrayMgr->createButton(OgreBites::TL_CENTER, Level::difficultyName(diff) + " " + patch::to_string(x), Level::getName(diff,x), 250);
    }
    mTrayMgr->createButton(OgreBites::TL_CENTER, "back to select difficulty " + Level::difficultyName(diff), "Back to Select Difficulty", 250);
}

void BaseApplication::removeLevelSelect(int diff)
{
    mTrayMgr->destroyWidget("menuLabel");
    for(int x = 1; x <= Level::numLevels(diff); x++)
    {
       mTrayMgr->destroyWidget(Level::difficultyName(diff) + " "  + patch::to_string(x));
    }
    mTrayMgr->destroyWidget("back to select difficulty " + Level::difficultyName(diff)); 
}


void BaseApplication::setupGUI(std::string levelName)
{
    mLevelName = mTrayMgr->createLabel(OgreBites::TL_TOP, "levelName", levelName, 500);
    mLevelName->show();
    mPlayerHp = mTrayMgr->createProgressBar(OgreBites::TL_TOP, "hpBar", "100/100", 200, 20);
    mPlayerHp->show();
    mNumDeaths = mTrayMgr->createLabel(OgreBites::TL_TOP, "deaths", "0 deaths", 220);
    mNumDeaths->show();
    mTime = mTrayMgr->createLabel(OgreBites::TL_TOP, "time", "0 seconds", 220);
    mTime->show();

    /************************************select menu Gui ****************************************************/
    mTrayMgr->moveWidgetToTray(mPlayerHp, OgreBites::TL_TOP, 0);
    mTrayMgr->moveWidgetToTray(mLevelName, OgreBites::TL_TOP, 0);

    mTrayMgr->moveWidgetToTray(mTime, OgreBites::TL_TOPRIGHT, 0);
    mTrayMgr->moveWidgetToTray(mNumDeaths, OgreBites::TL_TOPRIGHT, 0);
}

void BaseApplication::removeGUI()
{
    mTrayMgr->destroyWidget("levelName");
    mTrayMgr->destroyWidget("hpBar");
    mTrayMgr->destroyWidget("deaths");
    mTrayMgr->destroyWidget("time");
}

void BaseApplication::setupDeathMenu(void)
{
    removeGUI();
    mInMenu = true;
    mMenuLabel = mTrayMgr->createLabel(OgreBites::TL_TOP, "menuLabel", "You Died (Sapce to respawn)", 320);
    mTrayMgr->createButton(OgreBites::TL_TOP, "better", "Retry", 320);
    mTrayMgr->createButton(OgreBites::TL_TOP, "surrender", "Quit Level", 320);
}

void BaseApplication::removeDeathMenu(void)
{
    mInMenu = false;
    mTrayMgr->destroyWidget("menuLabel");
    mTrayMgr->destroyWidget("better");
    mTrayMgr->destroyWidget("surrender");
}
//---------------------------------------------------------------------------

void BaseApplication::createObjects()
{
    Ogre::SceneNode* node;
    Ogre::SceneNode* playerNode;
    //name doesnt mater rakans code is boosted
    player = new Player("playerNode", mSceneMgr, playerNode, 10., Ogre::Vector3(-25.,-250.,225.)); 
    gameMap = new Map(player, mSceneMgr, Ogre::Vector3(-225.0,-250.0, -225.0), mDifficulty, mLevel);
    if(mDifficulty >=3 && mDifficulty<=4)
    {
        if(mOldDifficulty != mDifficulty &&(mOldDifficulty!=3))
        {
            music = Mix_LoadMUS("Music/0/bgm.mp3");
            Mix_PlayMusic(music,-1);
        }
    }
    else 
    {
            if(mOldDifficulty == 3 || mOldDifficulty ==4)
            {
                music = Mix_LoadMUS("Music/0/bgm2.mp3");
                Mix_PlayMusic(music,-1);
            }
    }
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
    music = Mix_LoadMUS("Music/0/bgm2.mp3");
    Mix_PlayMusic(music,-1);
    Mix_VolumeMusic(50);
    Mix_Volume(-1, 110);
          
    setupMainMenu();
    mStats = new Stats();
    mStopwatch = new Stopwatch();

    return true;
};
//---------------------------------------------------------------------------
void BaseApplication::calcNextLevel()
{
    mOldDifficulty = mDifficulty;
    mLevel++;
    if(mDifficulty == 0)
    {
        mDifficulty++;
        mLevel = 1;
    }
    if(mLevel > Level::numLevels(mDifficulty)) //num intro levels
    {
        mLevel = 1;
        mDifficulty++;
    }
    // if(mDifficulty == 5 && mLevel > 1) //num credit levels
    // {
    //     mLevel = 1;
    //     mDifficulty++;
    // }
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
bool levelLoaded = false;
bool countDeath = false;
bool soundeffect = true;
bool bgm = true;
bool BaseApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    if(mWindow->isClosed())
        return false;

    //run save code then shut down

    if(mShutDown)
    {
        if(mStats->isLoggedIn())
        {
            mStats->save();
        }
        return false;
    }
    // Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();
    if(!mMusic)
    {
        Mix_PauseMusic();
        Mix_Volume(-1, 0);
        if(bgm)
        {
             Mix_ResumeMusic();
        }
        if(soundeffect)
        {
             Mix_Volume(-1, 110);
        }
    }
    else if(mMusic)
    {
        Mix_ResumeMusic();
        Mix_Volume(-1, 110);
        if(!bgm)
        {
             Mix_PauseMusic();
        }
        if(!soundeffect)
        {
             Mix_Volume(-1, 0);
        }
    }
    if(mGameStart && !mInMenu)
    {
        if(player->levelFinished)
        {
            if(mStats->isLoggedIn())
            {
                mStats->update(mDifficulty, mLevel, mDeathCounter, mStopwatch->elapsedTime(), true);
            }
            calcNextLevel();
            deleteMap();
            createObjects();
            mLevelName->setCaption(gameMap->getName());
            mStopwatch->reset();
            mDeathCounter = 0;
            mNumDeaths->setCaption(patch::to_string(mDeathCounter) + " deaths");
            //SAVE AND LOAD
        }

        mPlayerHp->setProgress((player->health)/100.0);
        mPlayerHp->setCaption("current HP is " + patch::to_string(player->health) + "/100");
        mTime->setCaption(patch::to_string(int(mStopwatch->elapsedTime() / 100.0 ) / 10.0) + " seconds");
        // float(int(floatValue * 10 + 0.5)) / 10;
        mPlayerHp->setCaption(" " + patch::to_string(player->health) + "/100");
        Ogre::SceneNode* tem = mSceneMgr->getSceneNode("playerNode");    
        Ogre::Vector3 position = tem->getPosition();
        mCamera->setPosition(position.x , 300, position.z+200);
        if(gameMap->isPlayerAlive())
        {
            if(wisDown)
                gameMap->move(0);
            else if(disDown)
                gameMap->move(1);
            else if(sisDown)
                gameMap->move(2);
            else if(aisDown)
                gameMap->move(3);
            if(!mStopwatch->isRunning() && (sisDown || wisDown || disDown || aisDown))
            {
                mStopwatch->start();
            }
        }
        else
        {
            setupDeathMenu();  
            mTrayMgr->showCursor();
            mCanRespawn = true;
        }
        gameMap->simulate(evt.timeSinceLastFrame);  
        // mSimulator->stepSimulation(evt.timeSinceLastFrame, music2);
    }
    else if (!mGameStart) //should be the loadinglevel
    {
        if(!levelLoaded)
        {
            mDifficulty = 0;
            mLevel = 0;
            mOldDifficulty =0;
            createObjects();       
            levelLoaded = true;   
            Ogre::SceneNode* tem = mSceneMgr->getSceneNode("playerNode");    
            Ogre::Vector3 position = tem->getPosition();
            mCamera->setPosition(position.x , 300, position.z+300);        
        }
        else
        {
            gameMap->simulate(evt.timeSinceLastFrame);
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
string letterFromKey(int keyTyped)
{
    if(keyTyped == OIS::KC_A)
        return "a";
    if(keyTyped == OIS::KC_B)
        return "b";
    if(keyTyped == OIS::KC_C)
        return "c";
    if(keyTyped == OIS::KC_D)
        return "d";
    if(keyTyped == OIS::KC_E)
        return "e";
    if(keyTyped == OIS::KC_F)
        return "f";
    if(keyTyped == OIS::KC_G)
        return "g";
    if(keyTyped == OIS::KC_H)
        return "h";
    if(keyTyped == OIS::KC_I)
        return "i";
    if(keyTyped == OIS::KC_J)
        return "j";
    if(keyTyped == OIS::KC_K)
        return "k";
    if(keyTyped == OIS::KC_L)
        return "l";
    if(keyTyped == OIS::KC_M)
        return "m";
    if(keyTyped == OIS::KC_N)
        return "n";
    if(keyTyped == OIS::KC_O)
        return "o";
    if(keyTyped == OIS::KC_P)
        return "p";
    if(keyTyped == OIS::KC_Q)
        return "q";
    if(keyTyped == OIS::KC_R)
        return "r";
    if(keyTyped == OIS::KC_S)
        return "s";
    if(keyTyped == OIS::KC_T)
        return "t";
    if(keyTyped == OIS::KC_U)
        return "u";
    if(keyTyped == OIS::KC_V)
        return "v";
    if(keyTyped == OIS::KC_W)
        return "w";
    if(keyTyped == OIS::KC_X)
        return "x";
    if(keyTyped == OIS::KC_Y)
        return "y";
    if(keyTyped == OIS::KC_Z)
        return "z";
    if(keyTyped == OIS::KC_0)
        return "0";
    if(keyTyped == OIS::KC_1)
        return "1";
    if(keyTyped == OIS::KC_2)
        return "2";
    if(keyTyped == OIS::KC_3)
        return "3";
    if(keyTyped == OIS::KC_4)
        return "4";
    if(keyTyped == OIS::KC_5)
        return "5";
    if(keyTyped == OIS::KC_6)
        return "6";
    if(keyTyped == OIS::KC_7)
        return "7";
    if(keyTyped == OIS::KC_8)
        return "8";
    if(keyTyped == OIS::KC_9)
        return "9";
    if(keyTyped == OIS::KC_BACK)
        return ".";
    return "";
}
bool BaseApplication::keyPressed( const OIS::KeyEvent &arg )
{
    if(mTypingUsername)
    {
        string newLetter = letterFromKey(arg.key);
        if(newLetter == ".")
        {
            mUsername = mUsername.substr(0, mUsername.length() - 1);
        }
        else
            mUsername += newLetter;
        mUsernameButton->setCaption(mUsername);

        return true;
    }
    if(mTypingPassword)
    {
        string newLetter = letterFromKey(arg.key);
        if(newLetter == ".")
        {
            mPassword = mPassword.substr(0, mPassword.length() - 1);
        }
        else
            mPassword += newLetter;
        mPasswordButton->setCaption(mPassword);

        return true;
    }



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
    else if(arg.key == OIS::KC_END)
    {
        mShutDown = true;
    }
    else if(arg.key == OIS::KC_RETURN)
    {

    }
    else if(arg.key == OIS::KC_SPACE)
    {
        if(mCanRespawn)
        {
            mCanRespawn = false;
            removeDeathMenu();
            setupGUI(gameMap->getName());
            gameMap->respawn();
            mDeathCounter += 1;
            if(mDeathCounter == 1)
            {
                mNumDeaths->setCaption(patch::to_string(mDeathCounter) + " death");
            }
            else
            {
                mNumDeaths->setCaption(patch::to_string(mDeathCounter) + " deaths");
            }
            mTrayMgr->hideCursor();
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
            mStopwatch->pause();
        }
        else if(mInMenu)
        {
            removeLevelMenu();
            setupGUI("");
            mStopwatch->unpause();
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
    //over kill for now
    mTypingPassword = false;
    mTypingUsername = false;

    if(button->getName().compare("account") == 0)        
    {
        removeMainMenu();
        setupAccountMenu();      
        return;
    }
        if(button->getName().compare("create") == 0)
        {
            removeAccountMenu();
            setupCreateAccountMenu();
            return;
        }
            if(button->getName().compare("create uname") == 0)
            {
                mTypingUsername = true;
                mUsername = "";
                mUsernameButton->setCaption(mUsername);
                return;
            }
            if(button->getName().compare("create pass") == 0)
            {
                mTypingPassword = true;
                mPassword = "";
                mPasswordButton->setCaption(mPassword);
                return;
            }
            if(button->getName().compare("confirm account") == 0)
            {
                if(mUsername == "")
                {
                    mMenuLabel->setCaption("Please Enter a Username");
                    return;
                }
                if(mPassword == "")
                {
                    mMenuLabel->setCaption("Please Enter a Password");
                    return;
                }
                if(mStats->createAccount(mUsername, mPassword))
                {
                    mStats->save();
                    removeCreateAccountMenu();
                    setupMainMenu();
                }   
                else
                {
                    mMenuLabel->setCaption("Username is Taken :(");
                }

                return;
            }
            if(button->getName().compare("back from create account") == 0)
            {
                if(!mStats->isLoggedIn())
                {
                    mUsername = "";
                    mPassword = "";
                }
                removeCreateAccountMenu();
                setupAccountMenu();
                return;
            }
        if(button->getName().compare("login") == 0)
        {
            removeAccountMenu();
            setupLoginMenu();
            return;
        }
            if(button->getName().compare("login uname") == 0)
            {
                mTypingUsername = true;
                mUsername = "";
                mUsernameButton->setCaption(mUsername);
                return;
            }
            if(button->getName().compare("login pass") == 0)
            {
                mTypingPassword = true;
                mPassword = "";
                mPasswordButton->setCaption(mPassword);
                return;
            }
            if(button->getName().compare("login to account") == 0)
            {
                if(mUsername == "")
                {
                    mMenuLabel->setCaption("Please Enter a Username");
                    return;
                }
                if(mPassword == "")
                {
                    mMenuLabel->setCaption("Please Enter a Password");
                    return;
                }
                if(mStats->login(mUsername, mPassword))
                {
                    removeLoginMenu();
                    setupMainMenu();
                }   
                else
                {
                    mMenuLabel->setCaption("Failed to Log in :(");
                }

                return;
            }
            if(button->getName().compare("back from login") == 0)
            {
                if(!mStats->isLoggedIn())
                {
                    mUsername = "";
                    mPassword = "";
                }
                removeLoginMenu();
                setupAccountMenu();
                return;
            }
        if(button->getName().compare("logout") == 0)
        {
            mStats->logout();
            mUsername = "";
            mPassword = "";
            removeAccountMenu();
            setupAccountMenu();
            return;
        }
        if(button->getName().compare("backfromsetup") == 0)
        {
            removeAccountMenu();
            setupMainMenu();
            return;
        }
    if(button->getName().compare("start") == 0)        
    {
        removeMainMenu();
        setupDifficultyMenu();      
        return;
    }       
    else if(button->getName().compare("sound") == 0 )
    {  
        removeMainMenu();
        setupSoundMenu();  
        return;
    }
    else if(button->getName().compare("help") == 0 )
    {  
        removeMainMenu();
        setupHelpMenu();  
        return;
    }
        else if(button->getName().compare("helpToMain") == 0 )
        {  
            removeHelpMenu();
            setupMainMenu();  
            return;
        }
        else if(button->getName().compare("control") == 0 )
        {  
            removeHelpMenu();
            setupControlMenu();  
            return;
        }
            else if(button->getName().compare("back from control") == 0 )
            {  
                removeControlMenu();
                setupHelpMenu();  
                return;
            }
        else if(button->getName().compare("info") == 0)
        {
            removeHelpMenu();
            setupInfoMenu();
            return;
        }
            else if(button->getName().compare("back from info") == 0 )
            {  
                removeInfoMenu();
                setupHelpMenu();  
                return;
            }
    else if(button->getName().compare("credit") == 0)
    {
        removeMainMenu(); 
        deleteMap(); // delete loading level
        mDifficulty = 5;
        mLevel = 1; 
        createObjects();              
        mGameStart= true;        
        mTrayMgr->hideCursor();      
        setupGUI(gameMap->getName()); 
        return;

    }
    else if(button->getName().compare("quit") == 0)
    {
        removeMainMenu();
        if(mStats->isLoggedIn())
        {
            mStats->save();
        }
        mShutDown = true;
    }
    else if(button->getName().compare("on") == 0 )
    {
        mMusic = true;
        bgm = true;
        soundeffect =true;        
        return;
    }
    else if(button->getName().compare("off") == 0 )
    {  
        mMusic = false;
        bgm = false;
        soundeffect =false;       
        return;
    }
    else if(button->getName().compare("bgm on") == 0 )
    {
        bgm = true;        
        return;
    }
    else if(button->getName().compare("bgm off") == 0 )
    {  
        bgm = false;       
        return;
    }
    else if(button->getName().compare("effect on") == 0 )
    {
        soundeffect = true;        
        return;
    }
    else if(button->getName().compare("effect off") == 0 )
    {  
        soundeffect = false;       
        return;
    }
    else if(button->getName().compare("sound to main") == 0 )
    {
        removeSoundMenu();         
        setupMainMenu();
        return;
    }
    for(int x = 1; x <= Level::numDifficulties(); x++)
    {
        // for clicking on the difficulty and loading the levels
        if(button->getName().compare(Level::difficultyName(x)) == 0 )       
        {       
            removeDifficultyMenu();
            setupLevelSelect(x);
            return;
        }
        // for clicking back to select difficulty
        if(button->getName().compare("back to select difficulty " + Level::difficultyName(x)) == 0)
        {
            removeLevelSelect(x);
            setupDifficultyMenu();   
            return;
        }
    }
    if(button->getName().compare("back to main menu") == 0 )
    {
        removeDifficultyMenu();
        setupMainMenu(); 
        return;
    }
    for(int x = 1; x <= Level::numDifficulties(); x++)
    {
        for(int y = 1; y <= Level::numLevels(x); y++)
        {
            std::string name = Level::difficultyName(x) + " " + patch::to_string(y);
            if(button->getName().compare(name) == 0)
            {
                removeLevelSelect(x);
                deleteMap();
                mDifficulty =x;
                mLevel = y; 
                createObjects();              
                mGameStart = true;        
                mTrayMgr->hideCursor();      
                setupGUI(gameMap->getName()); 
                return;   
            }
        }
    }


    if(button->getName().compare("quit level") == 0 )
    {
        removeLevelMenu();
        deleteMap();
        mGameStart = false;
        setupMainMenu();
        levelLoaded = false;
        music = Mix_LoadMUS("Music/0/bgm2.mp3");
        Mix_PlayMusic(music,-1);
        if(mStats->isLoggedIn())
        {
            mStats->update(mDifficulty, mLevel, mDeathCounter, mStopwatch->elapsedTime(), false);
        }
        mStopwatch->reset();
        mDeathCounter = 0;
        return;
    }
    else if(button->getName().compare("resume level") == 0 )
    {
        removeLevelMenu();
        setupGUI(gameMap->getName());
        mStopwatch->unpause();
        return;
    }
    else if(button->getName().compare("surrender") == 0 )
    {
        removeDeathMenu();
        deleteMap();
        mGameStart = false;
        setupMainMenu();
        levelLoaded = false;
        music = Mix_LoadMUS("Music/0/bgm2.mp3");
        Mix_PlayMusic(music,-1);
        if(mStats->isLoggedIn())
        {
            mStats->update(mDifficulty, mLevel, mDeathCounter+1, mStopwatch->elapsedTime(), false);
        }
        mStopwatch->reset();
        mDeathCounter = 0;
        //SAVE AND LOAD
        return;
    }
    else if(button->getName().compare("better") == 0 )
    {
        mCanRespawn = false;
        removeDeathMenu();
        setupGUI(gameMap->getName());
        gameMap->respawn();
        mDeathCounter += 1;
        if(mDeathCounter == 1)
        {
            mNumDeaths->setCaption(patch::to_string(mDeathCounter) + " death");
        }
        else
        {
            mNumDeaths->setCaption(patch::to_string(mDeathCounter) + " deaths");
        }
        mTrayMgr->hideCursor();
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