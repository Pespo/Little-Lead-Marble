#include <Ogre.h>
#include <LinearMath/btVector3.h>
#include <LinearMath/btQuaternion.h>

inline btVector3 convert(const Ogre::Vector3 &V){
    return btVector3(V.x, V.y, V.z);
}

inline Ogre::Vector3 convert(const btVector3 &V){
	return Ogre::Vector3(V.getX(), V.getY(), V.getZ());
}

inline btQuaternion convert(const Ogre::Quaternion &V){
	return btQuaternion( V.x, V.y, V.z, V.w);
}

inline Ogre::Quaternion convert(const btQuaternion &V){
    return Ogre::Quaternion(V.getW(), V.getX(), V.getY(), V.getZ());
}
