#pragma once

class Grid
{
public:
	Grid(class Context* context);
	virtual ~Grid();

	void Create
	(
		const int& w,
		const int& h,
		const int& spacing,
		const D3DXCOLOR& color = D3DXCOLOR(0, 1, 0, 1)
	);

	void Update();
	void Render();

private:
	class Context* context;
	class LineRender* lineRender;

	int width;
	int height;
	int spacing;
};