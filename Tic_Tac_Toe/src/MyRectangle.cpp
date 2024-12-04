#include "MyRectangle.h"
#include "Renderer.h"





MyRectangle::MyRectangle()
{
}

MyRectangle::MyRectangle(float width, float height, const std::string& vertexPath, const std::string& fragPath, const std::string& texturePath, glm::vec3 trans)
	:m_Model(1.0f),
	m_Pos(trans),
	m_Translate(0.0f, 0.0f, 0.0f)
{

	float vertices[] = {
		// positions																		// texture coords
		1.0f * width + trans.x, 1.0f * height + trans.y, 0.0f + trans.z, 1.0f, 1.0f, // top right
		1.0f * width + trans.x, 0.0f * height + trans.y, 0.0f + trans.z, 1.0f, 0.0f, // bottom right
		0.0f * width + trans.x, 0.0f * height + trans.y, 0.0f + trans.z, 0.0f, 0.0f, // bottom left
		0.0f * width + trans.x, 1.0f * height + trans.y, 0.0f + trans.z, 0.0f, 1.0f // top left
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3 // second triangle
	};
	/*std::cout << "Vertices:\n";
	for (int i = 0; i < 4; i++) {
		std::cout << vertices[i * 5] << ", " << vertices[i * 5 + 1] << ", " << vertices[i * 5 + 2] << std::endl;
	}*/

	m_VBO = std::make_unique<VBO>(vertices, sizeof(vertices));
	VBOLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);
	m_VAO = std::make_unique<VAO>();
	m_VAO->AddBuffer(*m_VBO, layout);
	m_Texture = std::make_unique<Texture>(texturePath);
	m_Shader = std::make_unique<Shader>(vertexPath, fragPath);

	m_EBO = std::make_unique<EBO>(indices, 6);
	m_Shader->Bind();
	m_Texture->Bind();
	updateUniforms();
	m_VAO->Unbind();
	m_Shader->Unbind();

}

MyRectangle::~MyRectangle()
{
}

void MyRectangle::draw()
{
	m_VAO->Bind();
	m_Texture->Bind();
	m_Shader->Bind();
	updateUniforms();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void MyRectangle::updateUniforms()
{
	m_Shader->Bind();
	m_Texture->Bind();
	m_Shader->setUniformMat4f("model", m_Model);
	m_Shader->setUniformMat4f("projection", m_Proj);
	m_Shader->SetUniform1i("texture1", 0);
}

void MyRectangle::Translate(glm::vec3& translate)
{
	m_Model = glm::translate(m_Model, -m_Translate);
	m_Translate = translate;
	m_Model = glm::translate(m_Model, m_Translate);

}

void MyRectangle::SetProj(glm::mat4 proj)
{
	m_Proj = proj;
}

void MyRectangle::SetView(glm::mat4 view)
{

}
