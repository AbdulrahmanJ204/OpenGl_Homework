#pragma once
#include <VBO.h>
#include <Shader.h>
#include <EBO.h>
#include <VAO.h>
#include <memory>
#include <Texture.h>

#include<glm/glm.hpp>	
#include<glm/gtc/matrix_transform.hpp>

class MyRectangle
{

public:
	MyRectangle();
	MyRectangle(float width, float height, const std::string& vertexPath, const std::string& fragPath , const std::string& texturePath, glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f));
	
	// Allow moving
	MyRectangle(MyRectangle&&) noexcept = default;
	MyRectangle& operator=(MyRectangle&&) noexcept = default;
	~MyRectangle();
	void draw();
	void updateUniforms();

	void Translate(glm::vec3& translate);
	//void Scale(glm::vec3& scale);
	//void Scale(float scale);
	//
	void SetProj(glm::mat4 proj);
	void SetView(glm::mat4 view);
	inline void setTransform(glm::mat4 transform) {
		m_Model = transform;
	}
	inline glm::vec3 getPos() const { return m_Pos; }
	
private:
	std::unique_ptr< VAO >m_VAO;
	std::unique_ptr< VBO >m_VBO;
	std::unique_ptr< EBO >m_EBO;
	std::unique_ptr< Shader >m_Shader;
	std::unique_ptr< Texture >m_Texture;
	
	glm::mat4 m_Proj, m_Model;

	glm::vec3 m_Translate , m_Pos;

	

};

