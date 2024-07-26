#pragma once
#include <SDL_ttf.h>
#include <string>

class Font {
public:
	Font() = default;
	~Font();

	bool Load(const std::string& name, int fontsize);

	friend class Text;

	_TTF_Font* GetFont() { return m_ttfFont; }

protected:
	_TTF_Font* m_ttfFont{ nullptr };
};