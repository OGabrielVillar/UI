#include "pch.h"
#include "Shader.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include "RendererAPI.h"

namespace Hazel 
{

	Reference<Shader> Shader::Create(const std::string& filepath)
	{
		switch(RendererAPI::Get())
		{	
			case RendererAPI::None:   HZ_ASSERT(false, "Shader::Create: RendererAP::None not suported!") return nullptr;
			case RendererAPI::OpenGL: return CreateReference<OpenGLShader>(filepath);
		}
		HZ_ASSERT(false, "Shader::Create: Unkown Renderer::API!")
		return nullptr;
	}

	Reference<Shader> Shader::Create(const std::string& name, const std::string& filepath)
	{
		switch(RendererAPI::Get())
		{	
			case RendererAPI::None:   HZ_ASSERT(false, "Shader::Create: RendererAP::None not suported!") return nullptr;
			case RendererAPI::OpenGL: return CreateReference<OpenGLShader>(name, filepath);
		}
		HZ_ASSERT(false, "Shader::Create: Unkown Renderer::API!")
		return nullptr;
	}

	Reference<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc,const std::string&  fragmentSrc)
	{
		switch(RendererAPI::Get())
		{	
			case RendererAPI::None:   HZ_ASSERT(false, "Shader::Create: RendererAP::None not suported!") return nullptr;
			case RendererAPI::OpenGL: return CreateReference<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}
		HZ_ASSERT(false, "Shader::Create: Unkown Renderer::API!")
		return nullptr;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		HZ_ASSERT(!Exists(name), "ShaderLibrary::Add: Shader already exist!");
		m_Shaders[name] = shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(name, filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		HZ_ASSERT(Exists(name), "ShaderLibrary::Get: Shader not found!");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name)
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

}
