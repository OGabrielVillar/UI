#pragma once

#include <string>
#include <glm/glm.hpp>

#include "Graphics/Renderer/Shader.h"

namespace Hazel 
{
	// TODO: REMOVE!
	typedef unsigned int GLenum;

	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc,const std::string&  fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		
		virtual const std::string& GetName() const override;

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& vector);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& vector);
		void UploadUniformInt(const std::string& name, int value);
	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& sources);
	private:
		uint32_t m_RendererID = 0;
		std::string m_Name;
	};

}
