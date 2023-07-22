#include "Camera.h"

// HW2: You can add more helper functions if you want!

glm::mat3 rotation(const float degrees,const glm::vec3 axis){
    const float angle = degrees * M_PI/180.0f; // convert to radians
    
    // HW2: implement a 3D rotation matrix for the given angle and axis.
    glm::mat3 iden = glm::mat3(1.0f);
    glm::mat3 aX = glm::transpose(glm::mat3(0, -axis[2], axis[1],
        axis[2], 0, -axis[0],
        -axis[1], axis[0], 0));
    glm::mat3 rotMat = (glm::cos(angle) * iden) + ((1 - glm::cos(angle)) * glm::outerProduct(axis, axis)) + (glm::sin(angle) * aX);

    return rotMat; 
}

void Camera::rotateRight(const float degrees){
    // HW2: Update the class members "eye," "up"
    glm::vec3 c3 = glm::normalize(eye - target);
    glm::vec3 c2 = glm::normalize(up - ((glm::dot(up, c3) * c3)));
    glm::vec3 c1 = glm::cross(c2, c3);

    glm::mat3 rotate = rotation(degrees, c2);
    glm::vec3 newC3 = rotate * (eye - target);
    eye = newC3 + target;
}
void Camera::rotateUp(const float degrees){
    // HW2: Update the class members "eye," "up"
    glm::vec3 c3 = glm::normalize(eye - target);
    glm::vec3 c2 = glm::normalize(up - ((glm::dot(up, c3) * c3)));
    glm::vec3 c1 = glm::cross(c2, c3);

    glm::mat3 rotate = rotation(-degrees, c1);
    glm::vec3 newVec = rotate * (eye - target);
    eye = newVec + target;
    up = rotate * up;
    up = glm::normalize(up);

}
void Camera::computeMatrices(){
    // Note that glm matrix column majored.
    // That is, A[i] is the ith column of A,
    // and A_{ij} in math notation is A[j][i] in glm notation.
    
    // HW2: Update the class member "view" for the view matrix using "eye," "target," "up."
    glm::vec3 c3 = glm::normalize(eye - target);
    glm::vec3 c2 = glm::normalize(up - ((glm::dot(up, c3) * c3)));
    glm::vec3 c1 = glm::cross(c2, c3);

    glm::mat4 c = glm::mat4(c1[0], c2[0], c3[0], eye[0],
        c1[1], c2[1], c3[1], eye[1],
        c1[2], c2[2], c3[2], eye[2],
        0, 0, 0, 1);
    c = glm::transpose(c);
    view = glm::inverse(c);
    
    // HW2: Update the class member "proj" for the perspective matrix using the class members "aspect," "fovy," "nearDist," "farDist."
    float fovy_rad = fovy * M_PI/180.0f; // remember to convert degrees to radians.
    proj = glm::mat4(1 / (aspect * glm::tan(fovy_rad/2)), 0, 0, 0,
        0, 1 / glm::tan(fovy_rad/2), 0, 0,
        0, 0, -((farDist + nearDist) / (farDist - nearDist)), -((2 * farDist * nearDist) / (farDist - nearDist)),
        0, 0, -1, 0);
    proj = glm::transpose(proj);
    
}

void Camera::reset(){
    eye = eye_default;// position of the eye
    target = target_default;  // look at target
    up = up_default;      // up vector
    fovy = fovy_default;  // field of view in degrees
    aspect = aspect_default; // aspect ratio
    nearDist = near_default; // nearDist clipping distance
    farDist = far_default; // farDist clipping distance
}