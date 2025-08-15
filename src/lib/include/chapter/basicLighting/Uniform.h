#ifndef UNIFORM_H
#define UNIFORM_H
#include <packGlm.h>
#include <string>
#include <glm/glm.hpp>

inline struct Uniform {
	packGlm<glm::vec3> objectColor{"objectColor"};
	packGlm<glm::vec3> viewPos{"viewPos"};
	packGlm<glm::vec3> lightColor{"lightColor"};
	packGlm<glm::vec3> lightPos{"lightPos"};
	packGlm<glm::mat4> projection{"projection"};
	packGlm<glm::mat4> view{"view"};
	packGlm<glm::mat4> model{"model"};
} uniform;

#endif