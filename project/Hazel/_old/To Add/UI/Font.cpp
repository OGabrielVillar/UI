#include "pch.h"
#include "Font.h"

#include "Run/Log.h"

#include "MSDFData.h"

namespace Hazel {

	using namespace msdf_atlas;

	struct FontInput {
		const char* fontFilename;
		GlyphIdentifierType glyphIdentifierType;
		const char* charsetFilename;
		double fontScale;
		const char* fontName;
	};

	struct Configuration {
		ImageType imageType;
		msdf_atlas::ImageFormat imageFormat;
		YDirection yDirection;
		int width, height;
		double emSize;
		double pxRange;
		double angleThreshold;
		double miterLimit;
		void (*edgeColoring)(msdfgen::Shape&, double, unsigned long long);
		bool expensiveColoring;
		unsigned long long coloringSeed;
		GeneratorAttributes generatorAttributes;
	};

#define DEFAULT_ANGLE_THRESHOLD 3.0
#define DEFAULT_MITER_LIMIT 1.0
#define LCG_MULTIPLIER 6364136223846793005ull
#define LCG_INCREMENT 1442695040888963407ull
#define THREADS 8

	template <typename T, typename S, int N, GeneratorFunction<S, N> GEN_FN>
	static Reference<Texture> makeAtlas(const std::vector<GlyphGeometry>& glyphs, const FontGeometry& fontGeometry, const Configuration& config)
	{
		ImmediateAtlasGenerator<S, N, GEN_FN, BitmapAtlasStorage<T, N> > generator(config.width, config.height);
		generator.setAttributes(config.generatorAttributes);
		generator.setThreadCount(THREADS);
		generator.generate(glyphs.data(), glyphs.size());

		msdfgen::BitmapConstReference<T, N> bitmap = (msdfgen::BitmapConstReference<T, N>) generator.atlasStorage();
		TextureProperties props;
		props.GenerateMips = false;
		props.SamplerWrap = TextureWrap::Clamp;
		props.DebugName = "FontAtlas";
		Reference<Texture> texture = Texture::Create(ImageFormat::RGBA32F, bitmap.width, bitmap.height, bitmap.pixels, props);
		return texture;
	}

	Font::Font(const std::filesystem::path& filepath)
		: m_FilePath(filepath), m_MSDFData(new MSDFData())
	{
		int result = 0;
		FontInput fontInput = { };
		Configuration config = { };
		fontInput.glyphIdentifierType = GlyphIdentifierType::UNICODE_CODEPOINT;
		fontInput.fontScale = -1;
		config.imageType = ImageType::MSDF;
		config.imageFormat = msdf_atlas::ImageFormat::BINARY_FLOAT;
		config.yDirection = YDirection::BOTTOM_UP;
		config.edgeColoring = msdfgen::edgeColoringInkTrap;
		const char* imageFormatName = nullptr;
		int fixedWidth = -1, fixedHeight = -1;
		config.generatorAttributes.config.overlapSupport = true;
		config.generatorAttributes.scanlinePass = true;
		double minEmSize = 0;
		double rangeValue = 2.0;
		TightAtlasPacker::DimensionsConstraint atlasSizeConstraint = TightAtlasPacker::DimensionsConstraint::MULTIPLE_OF_FOUR_SQUARE;
		config.angleThreshold = DEFAULT_ANGLE_THRESHOLD;
		config.miterLimit = DEFAULT_MITER_LIMIT;
		config.imageType = ImageType::MTSDF;

		std::string fontFilepath = m_FilePath.string();
		fontInput.fontFilename = fontFilepath.c_str();

		config.emSize = 40;

		// Load fonts
		bool anyCodepointsAvailable = false;
		{
			class FontHolder {
				msdfgen::FreetypeHandle* ft;
				msdfgen::FontHandle* font;
				const char* fontFilename;
			public:
				FontHolder() : ft(msdfgen::initializeFreetype()), font(nullptr), fontFilename(nullptr) { }
				~FontHolder() {
					if (ft) {
						if (font)
							msdfgen::destroyFont(font);
						msdfgen::deinitializeFreetype(ft);
					}
				}
				bool load(const char* fontFilename) {
					if (ft && fontFilename) {
						if (this->fontFilename && !strcmp(this->fontFilename, fontFilename))
							return true;
						if (font)
							msdfgen::destroyFont(font);
						if ((font = msdfgen::loadFont(ft, fontFilename))) {
							this->fontFilename = fontFilename;
							return true;
						}
						this->fontFilename = nullptr;
					}
					return false;
				}
				operator msdfgen::FontHandle* () const {
					return font;
				}
			} font;

			if (!font.load(fontInput.fontFilename))
				HZ_ASSERT(false);
			if (fontInput.fontScale <= 0)
				fontInput.fontScale = 1;

			// Load character set
			fontInput.glyphIdentifierType = GlyphIdentifierType::UNICODE_CODEPOINT;
			Charset charset;

			// From ImGui
			static const uint32_t charsetRanges[] =
			{
				0x0020, 0x00FF, // Basic Latin + Latin Supplement
				0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
				0x2DE0, 0x2DFF, // Cyrillic Extended-A
				0xA640, 0xA69F, // Cyrillic Extended-B
				0,
			};

			for (int range = 0; range < 8; range += 2)
			{
				for (int c = charsetRanges[range]; c <= charsetRanges[range + 1]; c++)
					charset.add(c);
			}

			// Load glyphs
			m_MSDFData->FontGeometry = FontGeometry(&m_MSDFData->Glyphs);
			int glyphsLoaded = -1;
			switch (fontInput.glyphIdentifierType)
			{
				case GlyphIdentifierType::GLYPH_INDEX:
					glyphsLoaded = m_MSDFData->FontGeometry.loadGlyphset(font, fontInput.fontScale, charset);
					break;
				case GlyphIdentifierType::UNICODE_CODEPOINT:
					glyphsLoaded = m_MSDFData->FontGeometry.loadCharset(font, fontInput.fontScale, charset);
					anyCodepointsAvailable |= glyphsLoaded > 0;
					break;
			}

			if (glyphsLoaded < 0)
				HZ_ASSERT(false);
			HZ_APP_TRACE("Loaded geometry of {0} out of {1} glyphs", glyphsLoaded, (int)charset.size());
			// List missing glyphs
			if (glyphsLoaded < (int)charset.size())
			{
				HZ_APP_WARN("Missing {0} {1}", (int)charset.size() - glyphsLoaded, fontInput.glyphIdentifierType == GlyphIdentifierType::UNICODE_CODEPOINT ? "codepoints" : "glyphs");
			}

			if (fontInput.fontName)
				m_MSDFData->FontGeometry.setName(fontInput.fontName);
		}

		// Determine final atlas dimensions, scale and range, pack glyphs
		{
			double pxRange = rangeValue;
			bool fixedDimensions = fixedWidth >= 0 && fixedHeight >= 0;
			bool fixedScale = config.emSize > 0;
			TightAtlasPacker atlasPacker;
			if (fixedDimensions)
				atlasPacker.setDimensions(fixedWidth, fixedHeight);
			else
				atlasPacker.setDimensionsConstraint(atlasSizeConstraint);
			atlasPacker.setPadding(config.imageType == ImageType::MSDF || config.imageType == ImageType::MTSDF ? 0 : -1);
			// TODO: In this case (if padding is -1), the border pixels of each glyph are black, but still computed. For floating-point output, this may play a role.
			if (fixedScale)
				atlasPacker.setScale(config.emSize);
			else
				atlasPacker.setMinimumScale(minEmSize);
			atlasPacker.setPixelRange(pxRange);
			atlasPacker.setMiterLimit(config.miterLimit);
			if (int remaining = atlasPacker.pack(m_MSDFData->Glyphs.data(), m_MSDFData->Glyphs.size()))
			{
				if (remaining < 0)
				{
					HZ_ASSERT(false);
				}
				else
				{
					HZ_ERROR("Error: Could not fit {0} out of {1} glyphs into the atlas.", remaining, (int)m_MSDFData->Glyphs.size());
					HZ_ASSERT(false);
				}
			}
			atlasPacker.getDimensions(config.width, config.height);
			HZ_ASSERT(config.width > 0 && config.height > 0);
			config.emSize = atlasPacker.getScale();
			config.pxRange = atlasPacker.getPixelRange();
			if (!fixedScale)
				HZ_APP_TRACE("Glyph size: {0} pixels/EM", config.emSize);
			if (!fixedDimensions)
				HZ_APP_TRACE("Atlas dimensions: {0} x {1}", config.width, config.height);
		}
		

		// Edge coloring
		if (config.imageType == ImageType::MSDF || config.imageType == ImageType::MTSDF)
		{
			if (config.expensiveColoring) {
				Workload([&glyphs = m_MSDFData->Glyphs, &config](int i, int threadNo) -> bool
				{
					unsigned long long glyphSeed = (LCG_MULTIPLIER * (config.coloringSeed ^ i) + LCG_INCREMENT) * !!config.coloringSeed;
					glyphs[i].edgeColoring(config.edgeColoring, config.angleThreshold, glyphSeed);
					return true;
				}, m_MSDFData->Glyphs.size()).finish(THREADS);
			}
			else
			{
				unsigned long long glyphSeed = config.coloringSeed;
				for (GlyphGeometry& glyph : m_MSDFData->Glyphs)
				{
					glyphSeed *= LCG_MULTIPLIER;
					glyph.edgeColoring(config.edgeColoring, config.angleThreshold, glyphSeed);
				}
			}
		}

		bool floatingPointFormat = true;
		Reference<Texture> texture;
		switch (config.imageType)
		{
			case ImageType::MSDF:
				if (floatingPointFormat)
					texture = makeAtlas<float, float, 3, msdfGenerator>(m_MSDFData->Glyphs, m_MSDFData->FontGeometry, config);
				else
					texture = makeAtlas<byte, float, 3, msdfGenerator>(m_MSDFData->Glyphs, m_MSDFData->FontGeometry, config);
				break;
			case ImageType::MTSDF:
				if (floatingPointFormat)
					texture = makeAtlas<float, float, 4, mtsdfGenerator>(m_MSDFData->Glyphs, m_MSDFData->FontGeometry, config);
				else
					texture = makeAtlas<byte, float, 4, mtsdfGenerator>(m_MSDFData->Glyphs, m_MSDFData->FontGeometry, config);
				break;
		}

		m_TextureAtlas = texture;
	}

	Font::~Font()
	{
		delete m_MSDFData;
	}

	static Reference<Font> s_DefaultFont;
	
	void Font::StaticInit()
	{
		s_DefaultFont = CreateReference<Font>("Resources/Fonts/opensans/OpenSans-Regular.ttf");
	}

	Reference<Font> Font::GetDefaultFont()
	{
		return s_DefaultFont;
	}

}
