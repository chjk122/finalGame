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
    mOverlaySystem(0)
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

    // Position it at 500 in Z direction
    mCamera->setPosition(Ogre::Vector3(0,0,80));
    // Look back along -Z
    mCamera->lookAt(Ogre::Vector3(0,0,-300));
    mCamera->setNearClipDistance(5);

    mCameraMan = new OgreBites::SdkCameraMan(mCamera);   // Create a default camera controller
}

//*-----------------------------------menu setup ------------------------------*//
void BaseApplication::setupMainMenu(void)
{
    mButton1 = mTrayMgr->createButton(OgreBites::TL_CENTER, "start", "Start Game", 220);
    mButton2 = mTrayMgr->createButton(OgreBites::TL_CENTER, "sound", "Sound Option", 220);
    mButton3 = mTrayMgr->createButton(OgreBites::TL_CENTER, "credit", "Credit Page", 220);
}

void BaseApplication::setupDifficultyMenu(void)
{
    mMenuLabel->setCaption("Select Difficulty");
    mButton1 = mTrayMgr->createButton(OgreBites::TL_CENTER, "intro", "Intro level", 220);
    mButton2 = mTrayMgr->createButton(OgreBites::TL_CENTER, "back", "Back to Main Menu", 220);
}

void BaseApplication::setupIntroLevelSelect(void)
{

}
//---------------------------------------------------------------------------

void BaseApplication::createObjects(int a)
{
    Ogre::SceneNode* node;
    Ogre::SceneNode* playerNode;
    if(a != 0)
    {
        delete gameMap;
    }
    //name doesnt mater rakans code is boosted
    player = new Player("playerNode", mSceneMgr, playerNode, 10., Ogre::Vector3(-25.,-250.,225.));
    player->level = a;
    std::vector<std::string> v;
    std::vector<std::string> e;
    if(a ==1)
    {
        v.push_back("xxxxxxx");  //y, q, e, z
        v.push_back("xwwwwwx");
        v.push_back("xwxwxwx");
        v.push_back("xwxwxwx");
        v.push_back("xlxwxvx");
        v.push_back("xlxwxdx");
        v.push_back("xsxkxfx");

        e.push_back("abxxabx"); 
        e.push_back("cdxxcdx");
        e.push_back("xxxxxxx");
        e.push_back("xxxxxxx");
        e.push_back("abxxabx");
        e.push_back("cdxxcdx");
        e.push_back("xxxxxxx");

    }
    else if(a==0)
    {

        v.push_back("xxxxxxxxxxxx");
        v.push_back("x+++wwwvkxfx");
        v.push_back("xixxwxxxxx+x");
        v.push_back("xixxwxxxxx+x");
        v.push_back("xixx+xxxxx+x");
        v.push_back("xivv+llllx+x");
        v.push_back("x++++++++pdx");
        v.push_back("xivv++llxxpx");
        v.push_back("xixx+++xxx+x");
        v.push_back("xixxxx+xxx+x");
        v.push_back("xsxc+++++++x");
        v.push_back("xxxxxxxxxxxx");

        e.push_back("abxxababxxab"); 
        e.push_back("cdxxcdcdxxcd");
        e.push_back("xxxxxxxxxxxx");
        e.push_back("xxxxxxxxxxxx");
        e.push_back("abxxababxxab");
        e.push_back("cdxxcdcdxxcd");
        e.push_back("xxxxxxxxxxxx");
        e.push_back("abxxababxxab"); 
        e.push_back("cdxxcdcdxxcd");
        e.push_back("xxxxxxxxxxxx");
        e.push_back("xxxxxxxxxxxx");
        e.push_back("abxxababxxab");
        e.push_back("cdxxcdcdxxcd");
        e.push_back("xxxxxxxxxxxx");

    }
    else 
    {
        v.push_back("xxxxxxxxxxxx");
        v.push_back("x+++wwwvkxfx");
        v.push_back("xixxwxxxxx+x");
        v.push_back("xixxwxxxxx+x");
        v.push_back("xixx+xxxxx+x");
        v.push_back("xivv+llllx+x");
        v.push_back("x++++++++pdx");
        v.push_back("xivv++llxxpx");
        v.push_back("xixx+++xxx+x");
        v.push_back("xixxxx+xxx+x");
        v.push_back("xsxc+++++++x");
        v.push_back("xxxxxxxxxxxx");

    //enemy key (y,u,a,b,c,d,l,r,h,i,j,k)
    // y (starts top goes down)
        //other version is u starts down goes top
    //a (starts top left goes top right bottom right bottom left)
        //b top right bottom right bottom left top left
        //c bottom right bottom left top left top right
        //d bottom left top left goes top right bottom
    //l starts left goes right
        //r starts right goes left
    //h goes up to next h and telports back to first h
        //i goes right to next i and telports back to first i
        //j goes down to next j and telports back to first j
        //k goes left to next k and telports back to first k
        e.push_back("abxxababxxab"); 
        e.push_back("cdxxcdcdxxcd");
        e.push_back("xxxxxxxxxxxx");
        e.push_back("xxxxxxxxxxxx");
        e.push_back("abxxababxxab");
        e.push_back("cdxxcdcdxxcd");
        e.push_back("xxxxxxxxxxxx");
        e.push_back("abxxababxxab"); 
        e.push_back("cdxxcdcdxxcd");
        e.push_back("xxxxxxxxxxxx");
        e.push_back("xxxxxxxxxxxx");
        e.push_back("abxxababxxab");
        e.push_back("cdxxcdcdxxcd");
        e.push_back("xxxxxxxxxxxx");
    }

    gameMap = new Map(player, mSceneMgr, Ogre::Vector3(-225.0,-250.0, -225.0), v, e);
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

     mTrayMgr->showCursor();            
    setupMainMenu();

    return true;
};
//---------------------------------------------------------------------------
bool scored = false;
int points = 0;
bool gameIsOver = false;
bool gameStart = false;

bool wisDown = false;
bool disDown = false;
bool sisDown = false;
bool aisDown = false;
bool BaseApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    double progressStepValue = evt.timeSinceLastFrame*.8;
    if(mWindow->isClosed())
        return false;

    if(mShutDown)
        return false;

    // Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();
    if(player->level == 1)
    {
        createObjects(1);
    }

    if(gameStart)
    {
        Ogre::SceneNode* tem = mSceneMgr->getSceneNode("playerNode");    
        Ogre::Vector3 position = tem->getPosition();
        mCamera->setPosition(position.x , 300, position.z+100);
        if(wisDown)
        {
            bool result = false;
            result = gameMap->move(0);
            if(result)
                std::cout << " moving up: true"  << std::endl;
        }
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
        mShutDown = true;
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
    if(button->getName().compare("start") == 0 )        
    {       
        mTrayMgr->destroyWidget("start");       
        mTrayMgr->destroyWidget("sound");       
        mTrayMgr->destroyWidget("credit");      
        //setupDifficultyMenu();        
        gameStart= true;        
        mTrayMgr->hideCursor(); 
        createObjects(0);        
    }       
    else if(button->getName().compare("intro") == 0 )       
    {       
        mTrayMgr->destroyWidget("intro");       
        mTrayMgr->destroyWidget("back");        
        //mTrayMgr->destroyWidget("menuLabel");     
        //createObjects();      
        //gameStart = true;     
        mTrayMgr->hideCursor();     
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