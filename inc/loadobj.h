#ifndef OBJLOAD_H
#define OBJLOAD_H
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

class objPoint {
private:
	// Coordinate vector of a point in (x, y, z)
	glm::vec3 coordinateVector;
	// Texture vector of a point in (u, v)
	glm::vec2 textureVector;
	// Normal vector of a point in (x, y, z)
	glm::vec3 normalVector;
	bool hasTextureVector;
	bool hasNormalVector;
public:
	objPoint();
	objPoint(const glm::vec3&, const glm::vec2&, const glm::vec3&);
	objPoint(const glm::vec3&);
	objPoint(const glm::vec3&, const glm::vec2&);
	objPoint(const glm::vec3&, const glm::vec3&);
	// Return whether the point has texture vector information or not
	bool isTextureVector() const;
	// Return whether the point has normal vector information or not
	bool isNormalVector() const;
	// Return CoordinateVector
	glm::vec3 getCoordinateVector() const;
	// Return TextureVector, please first use isTextureVector()
	// to check if TextureVector exists.
	glm::vec2 getTextureVector() const;
	// Return TextureVector, please first use isNormalVector()
	// to check if NormalVector exists.
	glm::vec3 getNormalVector() const;
};

class objTriangle {
public:
	// Points are connected to each other
	objPoint points[3];
public:
	objTriangle();
	objTriangle(const objPoint&, const objPoint&, const objPoint&) ;
};


class objRect {
public:
	// Points are connected to each other
	objPoint points[4];
public:
	objRect();
	objRect(const objPoint&, const objPoint&, const objPoint&, const objPoint&) ;
};

class objLine {
public:
	// Points are connected to each other
	objPoint points[2];
public:
	objLine();
	objLine(const objPoint&, const objPoint&) ;
};


class Model{
	public:
		std::vector<objTriangle> ts;
		std::vector<objRect> rs;
		std::vector<objLine> ls;
};

// Load a vector of triangles from obj file
// The second parameter tells if the obj file has texture and normal vector information
// the default setting is false.
// If it set to true, means it has such informations, which is (v, vt, vn)
// otherwise it is (v)
Model loadObj(const std::string);
#endif
