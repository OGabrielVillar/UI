#pragma once

#include "Platform/OpenGL/OpenGLFramebuffer.h"

class EditorApp : public Hazel::Application {
 public:
	EditorApp(const std::string& name, Hazel::Window::Flags flags = Hazel::Window::Flags());
	virtual ~EditorApp() = default;

	virtual void OnInit() override;
	
	virtual bool OnEvent(const Hazel::Event& event) override;

	virtual void OnShutdown() override;

	virtual void OnUpdate() override;

	void InitShit();

	void TestShit();

private:// Shit
	Hazel::ShaderLibrary m_ShaderLibrary;
	Hazel::Reference<Hazel::Shader> m_TextureShader;
	Hazel::Reference<Hazel::VertexArray> m_TextureVA;

	Hazel::Reference<Hazel::Shader> m_Shader;
	Hazel::Reference<Hazel::VertexArray> m_VertexArray;

	Hazel::Ref<Hazel::Texture> m_Texture;
	Hazel::Ref<Hazel::Texture> m_Texture2;

	Hazel::Rect m_Rect = Hazel::Rect::XYWH(500.f,50.f,370.f,170.f);
	Hazel::vec2 m_TextureSize = { 500.f, 500.f };
	Hazel::vec2 m_TexturePosition = { 0.f, 0.f };
	bool m_IsMoving = false;
	//Hazel::Rect m_Rect = Hazel::Rect(50.f,50.f,370.f,170.f) / 50.f;
	Hazel::vec4 m_RectColor = { 0.9f, 0.75f, 0.8f, 1.f };

	Hazel::Scene m_Scene = m_Window->GetLayer();
	Hazel::Layer m_Viewport = { 500, 500, 3 };
	Hazel::Scene m_ViewportScene = Hazel::CreateReference<Hazel::Layer>(m_Viewport);

	std::vector<Hazel::Command> m_Commands;
	Hazel::TextureInterpolation m_Interpolation[2] = {Hazel::TextureInterpolation::Linear, Hazel::TextureInterpolation::Nearest};
	uint8_t m_InterpolationIndex = 0;

};
