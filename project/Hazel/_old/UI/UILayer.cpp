#include "pch.h"
#include "UILayer.h"
//
//#include "Components/HeritageComponent.h"
//#include "Components/LayoutComponent.h"
//#include "Components/FrameComponent.h"
//#include "Components/ButtonComponent.h"
//#include "Components/SliderComponent.h"
//#include "Components/InformationComponent.h"
//
//#include "Hazel/Debug/Profiler.h"
//
//namespace Hazel::UI {
//
//	static UILayer* worklayer = nullptr;
//
//	UILayer::UILayer(const std::string& name)
//	{
//
//
//		screen_element = m_registry.create();
//		//m_registry.emplace<LayoutComponent>(screen_element);
//
//		testFrame = m_registry.create();
//		auto& t_layout = m_registry.emplace<LayoutComponent>(testFrame);
//		auto& t_heritage = m_registry.emplace<HeritageComponent>(testFrame, screen_element);
//		auto& t_frame = m_registry.emplace<FrameComponent>(testFrame);
//		
//		t_layout.SetOffset( 0.5f, 0.5f );
//		t_layout.SetSize( 0.2f, 0.2f);
//		t_frame.SetColor( 0.5f, 0.2f, 0.5f );
//
//		m_UIRenderer2D = Ref<Renderer2D>::Create();
//		m_UIRenderer = Ref<SceneRenderer>::Create(m_UIScene);
//		m_UIRenderer->SetLineWidth(m_LineWidth);
//	}
//
//
//	void UILayer::OnUpdate(Timestep ts)
//	{
//		return;
//		//if (!m_UIRenderer->GetFinalPassImage())
//		//	return;
//		//
//		//m_UIRenderer2D->BeginScene(m_UICamera.GetViewProjection(), m_UICamera.GetViewMatrix());
//		//m_UIRenderer2D->SetTargetRenderPass(m_UIRenderer->GetExternalCompositeRenderPass());
//		//
//		//
//		//auto group = m_registry.group<LayoutComponent>(entt::get<FrameComponent>);
//		//for (auto element : group)
//		//{
//		//	auto [layoutComponent, frameComponent] = group.get<LayoutComponent, FrameComponent>(element);
//		//
//		//	if (frameComponent.IsVisible())
//		//		m_UIRenderer2D->DrawQuad(layoutComponent.GetTopLeft(), layoutComponent.GetSize(), frameComponent.GetVisual().Color);
//		//		;
//		//}
//		//
//		//m_UIRenderer2D->EndScene();
//	}
//
//	UI::Element& UILayer::CreateElement(const std::string& information)
//	{
//		auto element = Element{ m_registry.create(), m_registry };
//
//		if (!information.empty())
//		auto& idComponent = element.AddComponent<UI::InformationComponent>(information);
//
//		element.AddComponent<LayoutComponent>();
//
//		element.AddComponent<HeritageComponent>();
//
//		return element;
//	}
//
//}
