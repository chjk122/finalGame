/*
-----------------------------------------------------------------------------
Filename:    Assignment2.cpp
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

#include "Assignment2.h"
#include "GameObject.h"

//---------------------------------------------------------------------------
Assignment2::Assignment2(void)
{
}
//---------------------------------------------------------------------------
Assignment2::~Assignment2(void)
{
}

//---------------------------------------------------------------------------
void Assignment2::createScene(void)
{
    mSceneMgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));
    mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
    // mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0, 1.0, 1.0));
    Ogre::Light* pointLightTop = mSceneMgr->createLight("PointLight");
    pointLightTop->setType(Ogre::Light::LT_POINT);
    pointLightTop->setDiffuseColour(.7, .7, .7);
    // pointLightTop->setDiffuseColour(1, 1, 1);
    pointLightTop->setSpecularColour(.5, .5, .5);
    pointLightTop->setPosition(Ogre::Vector3(0, (500)/2 - 100, 0));

    // Ogre::Entity* ent;
    Ogre::SceneNode* node;
    Ogre::SceneNode* playerNode;

    // Ogre::String n,
    // Ogre::SceneManager* mgr,
    // Simulator* sim,
    // Ogre::SceneNode* node,
    // btScalar m,

    /*****  CONSTUCTING THE ROOM PLANES *****/
    // Wall* ground = new Wall("ground", mSceneMgr, mSimulator, node, 0., 5000, 5000, Ogre::Vector3::UNIT_Y, -251);
    // ground->create();
    Wall* roof = new Wall("roof", mSceneMgr, mSimulator, node, 0.,500, 500, Ogre::Vector3::NEGATIVE_UNIT_Y, -250);
    roof->create();
    Wall* posZ = new Wall("posZ", mSceneMgr, mSimulator, node, 0.,500, 500, Ogre::Vector3::NEGATIVE_UNIT_Z, -250);
    posZ->create();
    Wall* negZ = new Wall("negZ", mSceneMgr, mSimulator, node, 0.,500, 500, Ogre::Vector3::UNIT_Z, -250);
    negZ->create();
    Wall* posX = new Wall("posX", mSceneMgr, mSimulator, node, 0.,500, 500, Ogre::Vector3::NEGATIVE_UNIT_X, -250);
    posX->create();
    Wall* negX = new Wall("negX", mSceneMgr, mSimulator, node, 0.,500, 500, Ogre::Vector3::UNIT_X, -250);
    negX->create();

    // map->create();
 
    
    mCamera->setPosition(0, -170.0, +300.0);
    mCamera->pitch(Ogre::Degree(15.0));
    // negative z and this will be client v
    // mCamera->yaw(Ogre::Degree(180.0));

}
//---------------------------------------------------------------------------

void Assignment2::createFrameListener(void)
{
    BaseApplication::createFrameListener(); 
    //this code must be only here of in framerendering, error if in createscene
}

//---------------------------------------------------------------------------

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        Assignment2 app;

        try {
            app.go();
        } catch(Ogre::Exception& e)  {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occurred: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif

//---------------------------------------------------------------------------
