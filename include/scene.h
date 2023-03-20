#ifndef SCENE_H
#define SCENE_H

#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>

class scene
{
    public:
        scene();
        virtual ~scene();
        int drawScene();
        int initScene();
        void resizeSceneWin(GLsizei, GLsizei);

        int winMsg(HWND, UINT, WPARAM, LPARAM);

    protected:

    private:
};

#endif // SCENE_H
