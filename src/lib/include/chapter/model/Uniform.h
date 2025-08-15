#ifndef UNIFORM_H
#define UNIFORM_H
#include <packGlm.h>
#include <string>
#include <glm/glm.hpp>

inline struct Uniform {
	packGlm<float> shininess{"shininess"};
	packGlm<glm::vec3> viewPos{"viewPos"};
	struct Light : templateStruct {
		std::string path{"light"};
		packGlm<glm::vec3> diffuse{this->path + ".diffuse"};
		packGlm<glm::vec3> specular{this->path + ".specular"};
		packGlm<glm::vec3> ambient{this->path + ".ambient"};
		packGlm<glm::vec3> position{this->path + ".position"};
	} light{};
	packGlm<int> texture_specular1{"texture_specular1"};
	packGlm<int> texture_diffuse1{"texture_diffuse1"};
	packGlm<glm::vec4> lightColor{"lightColor"};
	packGlm<int> Texture{"Texture"};
	packGlm<glm::mat4> projection{"projection"};
	packGlm<glm::mat4> view{"view"};
	packGlm<glm::mat4> model{"model"};
} uniform;

#endif