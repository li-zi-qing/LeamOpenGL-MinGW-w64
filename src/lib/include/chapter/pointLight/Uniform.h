#ifndef UNIFORM_H
#define UNIFORM_H
#include <packGlm.h>
#include <string>
#include <glm/glm.hpp>

inline struct Uniform {
	struct Light : templateStruct {
		std::string path{"light"};
		packGlm<float> quadratic{this->path + ".quadratic"};
		packGlm<float> linear{this->path + ".linear"};
		packGlm<glm::vec3> diffuse{this->path + ".diffuse"};
		packGlm<glm::vec3> specular{this->path + ".specular"};
		packGlm<glm::vec3> ambient{this->path + ".ambient"};
		packGlm<float> constant{this->path + ".constant"};
		packGlm<glm::vec3> position{this->path + ".position"};
	} light{};
	struct Material : templateStruct {
		std::string path{"material"};
		packGlm<float> shininess{this->path + ".shininess"};
		packGlm<int> specular{this->path + ".specular"};
		packGlm<int> diffuse{this->path + ".diffuse"};
	} material{};
	packGlm<glm::vec3> viewPos{"viewPos"};
	packGlm<glm::mat4> projection{"projection"};
	packGlm<glm::mat4> view{"view"};
	packGlm<glm::mat4> model{"model"};
} uniform;

#endif