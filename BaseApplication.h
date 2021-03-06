/*
-----------------------------------------------------------------------------
Filename:    BaseApplication.h
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

#ifndef __BaseApplication_h_
#define __BaseApplication_h_

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
#include <btBulletDynamicsCommon.h>
#include "GameObject.h"
#include "Stats.h"
#include "Stopwatch.h"
#include "Map.h"
#include <sstream>
#include <vector>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
#  include <OIS/OISEvents.h>
#  include <OIS/OISInputManager.h>
#  include <OIS/OISKeyboard.h>
#  include <OIS/OISMouse.h>

#  include <OGRE/SdkTrays.h>
#  include <OGRE/SdkCameraMan.h>
#else
#  include <OISEvents.h>
#  include <OISInputManager.h>
#  include <OISKeyboard.h>
#  include <OISMouse.h>

#  include <SdkTrays.h>
#  include <SdkCameraMan.h>


#endif

#ifdef OGRE_STATIC_LIB
#  define OGRE_STATIC_GL
#  if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#    define OGRE_STATIC_Direct3D9
// D3D10 will only work on vista, so be careful about statically linking
#    if OGRE_USE_D3D10
#      define OGRE_STATIC_Direct3D10
#    endif
#  endif
#  define OGRE_STATIC_BSPSceneManager
#  define OGRE_STATIC_ParticleFX
#  define OGRE_STATIC_CgProgramManager
#  ifdef OGRE_USE_PCZ
#    define OGRE_STATIC_PCZSceneManager
#    define OGRE_STATIC_OctreeZone
#  else
#    define OGRE_STATIC_OctreeSceneManager
#  endif
#  include "OgreStaticPluginLoader.h"
#endif

//---------------------------------------------------------------------------

class BaseApplication : public Ogre::FrameListener, public Ogre::WindowEventListener, public OIS::KeyListener, public OIS::MouseListener, OgreBites::SdkTrayListener
{
public:
    BaseApplication(void);
    virtual ~BaseApplication(void);

    virtual void go(void);

protected:
    virtual bool setup();
    virtual bool configure(void);
    virtual void chooseSceneManager(void);
    virtual void createCamera(void);

    virtual void createObjects();
    virtual void createFrameListener(void);
    virtual void createScene(void) = 0; // Override me!
    virtual void destroyScene(void);
    virtual void createViewports(void);
    virtual void setupResources(void);
    virtual void createResourceListener(void);
    virtual void loadResources(void);
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
    virtual void deleteMap();

    virtual bool keyPressed(const OIS::KeyEvent &arg);
    virtual bool keyReleased(const OIS::KeyEvent &arg);
    virtual bool mouseMoved(const OIS::MouseEvent &arg);
    virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    virtual void buttonHit(OgreBites::Button* button);
    virtual void calcNextLevel();

    // Adjust mouse clipping area
    virtual void windowResized(Ogre::RenderWindow* rw);
    // Unattach OIS before window shutdown (very important under Linux)
    virtual void windowClosed(Ogre::RenderWindow* rw);
    virtual void setupMainMenu(void);
    virtual void removeMainMenu(void);
    virtual void setupAccountMenu(void);
    virtual void removeAccountMenu(void);
    virtual void setupHelpMenu(void);
    virtual void removeHelpMenu(void);
    virtual void setupControlMenu(void);
    virtual void removeControlMenu(void);
    virtual void setupInfoMenu(void);
    virtual void removeInfoMenu(void);
    virtual void setupCreateAccountMenu(void);
    virtual void removeCreateAccountMenu(void);
    virtual void setupLoginMenu(void);
    virtual void removeLoginMenu(void);
    virtual void setupLevelMenu(void);
    virtual void removeLevelMenu(void);
    virtual void setupDeathMenu(void);
    virtual void removeDeathMenu(void);
    virtual void setupGUI(std::string name);
    virtual void removeGUI(void);
    virtual void setupDifficultyMenu(void);
    virtual void removeDifficultyMenu(void);
    virtual void setupLevelSelect(int diff);
    virtual void removeLevelSelect(int diff);
    virtual void setupSoundMenu(void);
    virtual void removeSoundMenu(void);

    Ogre::Root*                 mRoot;
    Ogre::Camera*               mCamera;
    Ogre::SceneManager*         mSceneMgr;
    Ogre::RenderWindow*         mWindow;
    Ogre::String                mResourcesCfg;
    Ogre::String                mPluginsCfg;

    Ogre::OverlaySystem*        mOverlaySystem;

    // OgreBites
    OgreBites::InputContext     mInputContext;
    OgreBites::SdkTrayManager*	mTrayMgr;
    OgreBites::SdkCameraMan*    mCameraMan;     	// Basic camera controller
    OgreBites::ParamsPanel*     mDetailsPanel;   	// Sample details panel
    OgreBites::Label*           mMenuLabel;
    // std::vector<OgreBites::Button *>       mButtonLevels;
    OgreBites::Button*          mButtonBack;

    OgreBites::Label*           mLevelName;
    OgreBites::ProgressBar*     mPlayerHp;
    OgreBites::Label*           mNumDeaths;
    int                         mDeathCounter;
    OgreBites::Label*           mTime;
    
    bool                        mCursorWasVisible;	// Was cursor visible before dialog appeared?
    bool                        mShutDown;
    bool                        mMusic;

    //OIS Input devices

    OIS::InputManager*          mInputManager;
    OIS::Mouse*                 mMouse;
    OIS::Keyboard*              mKeyboard;
    Mix_Music*                  music;
    Mix_Music*                  music2;

    Player*                     player;
    Map*                        gameMap;
    Stats*                      mStats;
    Stopwatch*                  mStopwatch;

    Ogre::Real                  mGameState;
    int                         mDifficulty;
    int                         mOldDifficulty;
    int                         mLevel;
    bool                        mGameStart;
    bool                        mInMenu;

    OgreBites::Button*          mUsernameButton;
    OgreBites::Button*          mPasswordButton;
    std::string                 mUsername;
    std::string                 mPassword;
    bool                        mTypingUsername;
    bool                        mTypingPassword;
    bool                        mCanRespawn;


    // Added for Mac compatibility
    Ogre::String                 m_ResourcePath;

#ifdef OGRE_STATIC_LIB
    Ogre::StaticPluginLoader m_StaticPluginLoader;
#endif
};

//---------------------------------------------------------------------------

#endif // #ifndef __BaseApplication_h_

//---------------------------------------------------------------------------