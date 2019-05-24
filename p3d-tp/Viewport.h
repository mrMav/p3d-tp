#pragma once

class Viewport {

public:

	Viewport(int w, int h) { m_width = w; m_height = h;	}
	~Viewport() { };

	int Width() { return m_width; }
	int Height() { return m_height; }

	float AspectRatio() { return static_cast<float>(m_width) / static_cast<float>(m_height); }

private:

	int m_width;

	int m_height;

};