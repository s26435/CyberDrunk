#ifndef UNTITLED_CAMERA_H
#define UNTITLED_CAMERA_H

class Camera {
public:
    static double x, y;
    static void follow(float targetX, float targetY, double deltaTime) {
        float lerpSpeed = 6.0f;
        Camera::x += (targetX - Camera::x) * lerpSpeed * deltaTime;
        Camera::y += (targetY - Camera::y) * lerpSpeed * 3 * deltaTime;
        if (Camera::y < 100)
        {
            Camera::y = 100;
        }

    }
};

#endif //UNTITLED_CAMERA_H








