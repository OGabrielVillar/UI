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
	Hazel::Project m_Project;
	Hazel::Ref<Hazel::CameraEntity> m_ViewportCamera;
	Hazel::Ref<Hazel::CameraEntity> m_Camera;

	Hazel::Entity m_UILayer = m_Project.CreateUILayer();

	Hazel::ShaderLibrary m_ShaderLibrary;
	Hazel::Reference<Hazel::Shader> m_TextureShader;
	Hazel::Reference<Hazel::VertexArray> m_TextureVA;

	Hazel::Ref<Hazel::Texture> m_Texture;
	Hazel::Ref<Hazel::Texture> m_Texture2;

	Hazel::Rect m_Rect = Hazel::Rect::XYWH(500.f,50.f,370.f,170.f);
	Hazel::vec2 m_TextureSize = { 500.f, 500.f };
	Hazel::vec2 m_TexturePosition = { 0.f, 0.f };
	bool m_IsMoving = false;
	Hazel::vec4 m_RectColor = { 0.9f, 0.75f, 0.8f, 1.f };
	
	Hazel::Ref<Hazel::Entity> m_Viewport;
	Hazel::Ref<Hazel::Canvas> m_ViewportCanvas = Hazel::CreateReference<Hazel::Canvas>(500, 500, 3);
	Hazel::Ref<Hazel::Entity> m_Scene;
	Hazel::Ref<Hazel::Entity> m_ViewportScene;

	Hazel::TextureInterpolation m_Interpolation[2] = {Hazel::TextureInterpolation::Linear, Hazel::TextureInterpolation::Nearest};
	uint8_t m_InterpolationIndex = 0;

};
