#ifndef MODEL_H
#define MODEL_H
#include<windows.h>
#include<GL/glut.h>

class model
{
    public:
        model();
        virtual ~model();

        void drawModel();

        float rotateModelX;

        float posModelX;
        float posModelY;

    protected:

    private:
};

#endif // MODEL_H
