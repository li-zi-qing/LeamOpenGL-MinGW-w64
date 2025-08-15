#ifndef UNIFORM_H
#define UNIFORM_H
#include <packGlm.h>
#include <string>
#include <glm/glm.hpp>

inline struct Uniform {
	struct Material : templateStruct {
		std::string path{"material"};
		packGlm<float> shininess{this->path + ".shininess"};
		packGlm<int> specular{this->path + ".specular"};
		packGlm<int> diffuse{this->path + ".diffuse"};
	} material{};
	struct SpotLight : templateStruct {
		std::string path{"spotLight"};
		packGlm<int> diffuse{this->path + ".diffuse"};
		packGlm<glm::vec3> specular{this->path + ".specular"};
		packGlm<glm::vec3> ambient{this->path + ".ambient"};
		packGlm<float> quadratic{this->path + ".quadratic"};
		packGlm<float> linear{this->path + ".linear"};
		packGlm<float> outerCutOff{this->path + ".outerCutOff"};
		packGlm<float> cutOff{this->path + ".cutOff"};
		packGlm<glm::vec3> direction{this->path + ".direction"};
		packGlm<float> constant{this->path + ".constant"};
		packGlm<glm::vec3> position{this->path + ".position"};
	} spotLight{};
	struct PointLight : templateStruct {
		std::string path{"pointLights"};
		packGlm<glm::vec3> diffuse{this->path + ".diffuse"};
		packGlm<glm::vec3> specular{this->path + ".specular"};
		packGlm<glm::vec3> ambient{this->path + ".ambient"};
		packGlm<float> quadratic{this->path + ".quadratic"};
		packGlm<float> linear{this->path + ".linear"};
		packGlm<float> constant{this->path + ".constant"};
		packGlm<glm::vec3> position{this->path + ".position"};
		explicit PointLight(const int& index) : path{"pointLights[" + std::to_string(index) + "]"}{}
		PointLight() = default;
	} pointLights[4];
	struct DirLight : templateStruct {
		std::string path{"dirLight"};
		packGlm<glm::vec3> diffuse{this->path + ".diffuse"};
		packGlm<glm::vec3> specular{this->path + ".specular"};
		packGlm<glm::vec3> ambient{this->path + ".ambient"};
		packGlm<glm::vec3> direction{this->path + ".direction"};
	} dirLight{};
	packGlm<glm::vec3> viewPos{"viewPos"};
	packGlm<glm::mat4> projection{"projection"};
	packGlm<glm::mat4> view{"view"};
	packGlm<glm::mat4> model{"model"};
	Uniform()
	{
		for(int i = 0; i < 4; i++)
		{
			pointLights[i] = PointLight(i);
		}
	}
} uniform;

#endif