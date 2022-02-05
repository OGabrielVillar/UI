#pragma once

#include "Hazel/Renderer/Texture.h"

#include <filesystem>

namespace Hazel {

	struct MSDFData;

	class Font : public Asset
	{
	public:
		Font(const std::filesystem::path& filepath);
		virtual ~Font();

		Reference<Texture> GetFontAtlas() const { return m_TextureAtlas; }
		const MSDFData* GetMSDFData() const { return m_MSDFData; }

		static void StaticInit();
		static Reference<Font> GetDefaultFont();

		static AssetType GetStaticType() { return AssetType::Font; }
		virtual AssetType GetAssetType() const override { return GetStaticType(); }
	private:
		std::filesystem::path m_FilePath;
		Reference<Texture> m_TextureAtlas;
		MSDFData* m_MSDFData = nullptr;
	};


}
