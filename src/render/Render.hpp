#pragma once

class Logic;

class Render
{
	Logic* logic = nullptr;

public:
	Render() = default;
	Render(const Render &) = default;
	Render(Render &&) = default;
	Render &operator=(const Render &) = default;
	Render &operator=(Render &&) = default;
	
	void Init(Logic* logic);

	void Update(double dt);
};