#ifndef NAUGHTYSDL_HPP
#define NAUGHTYSDL_HPP

#include "Application.hpp"
#include "Vector.hpp"

static Application* APP_MAIN = nullptr;

void Naughty_Init (const std::string& header, const unsigned int& width, const unsigned int& height);

const int Naughty_Run (InputProcessor* input = new InputProcessor);

void Naughty_MountRenderable (IRenderNode& node);

const Vector2D <unsigned int> Naughty_CurrentResolution ();

#define Naughty_MainRenderer APP_MAIN->renderer()

#endif // NAUGHTYSDL_HPP
