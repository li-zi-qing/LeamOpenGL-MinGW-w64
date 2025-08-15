#ifndef UNIFORM_H
#define UNIFORM_H
#include <packGlm.h>
#include <string>
#include <glm/glm.hpp>

inline struct Uniform {
	packGlm<int> texture1{"texture1"};
	packGlm<glm::vec3> color{"color"};
	packGlm<glm::mat4> projection{"projection"};
	packGlm<glm::mat4> view{"view"};
	packGlm<glm::mat4> model{"model"};
} uniform;

#endif