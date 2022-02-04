#pragma once

#include "Hazel/Core/core.h"

namespace Notion::text {

	struct font
	{
		font(const std::string& ttfpath_in) 
		{
			std::ifstream ifs(ttfpath_in, std::ifstream::binary | std::ifstream::ate);
			size_t fsize = ifs.tellg();
			unsigned char* ttf_buffer = new unsigned char[fsize];
			fread(ttf_buffer, 1, fsize, fopen(ttfpath_in.c_str(), "rb"));
			if(!stbtt_InitFont(&font_info, ttf_buffer, stbtt_GetFontOffsetForIndex(ttf_buffer, 0)))
				assert("Font Construction Error: InitFontError");
		}

		void print_codepoint(int codepoint_in, int size_in)
		{
			int w = 0, h = 0;
			unsigned char* bitmap = stbtt_GetCodepointBitmap(&font_info, 0.f, stbtt_ScaleForPixelHeight(&font_info, size_in), codepoint_in, &w, &h, 0, 0);
			for (int j = 0; j < h; ++j) {
				for (int i = 0; i < w; ++i)
					putchar(" .:ioVM@"[bitmap[j * w + i] >> 5]);
				putchar('\n');
			}
		}

		void write_codepoint_in_lines(int codepoint_in, int size_in, std::vector<std::string> lines_in)
		{
			int w = 0, h = 0;
			unsigned char* bitmap = stbtt_GetCodepointBitmap(&font_info, 0.f, stbtt_ScaleForPixelHeight(&font_info, size_in), codepoint_in, &w, &h, 0, 0);

			int height_dif = h - lines_in.size();
			for (size_t l = 0; l < height_dif; l++)
				lines_in.push_back("");

			int lines_amount = lines_in.size();
			for (int j = 0; j < h; ++j) {
				for (int i = 0; i < w; ++i)
					lines_in[j].push_back(" .:ioVM@"[bitmap[j * w + i] >> 5]);
			}
		}

		void print_string(const std::string& str_in, int size_in)
		{
			std::vector<std::string> lines;
			for (char c : str_in)
				write_codepoint_in_lines(c, size_in, lines);

			for (size_t i = 0; i < size_in; i++) {
				std::cout << lines[i];
				putchar('\n');
			}

		}

		stbtt_fontinfo font_info;
		//stbtt__bitmap bitmap_raw;
	};

}
