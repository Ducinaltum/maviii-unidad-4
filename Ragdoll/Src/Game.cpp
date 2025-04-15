#include "Game.h"
#include "Box2DHelper.h"
#include <iostream>

Game::Game(int ancho, int alto, std::string titulo)
{
	wnd = new RenderWindow(VideoMode(ancho, alto), titulo);
	wnd->setVisible(true);
	fps = 60;
	wnd->setFramerateLimit(fps);
	frameTime = 1.0f / fps;
	SetZoom(100.0f, (float)ancho / (float)alto);
	InitPhysics();
}

void Game::SetZoom(float height, float ratio)
{
	View camara;
	float width = height * ratio;
	camara.setSize(width, height);
	camara.setCenter(width / 2, height / 2);
	wnd->setView(camara);
}

void Game::InitPhysics()
{
	phyWorld = new b2World(b2Vec2(0.0f, 9.8f));

	debugRender = new SFMLRenderer(wnd);
	debugRender->SetFlags(UINT_MAX);
	phyWorld->SetDebugDraw(debugRender);


	b2Body* groundBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 100, 10);
	groundBody->SetTransform(b2Vec2(50.0f, 100.0f), 0.0f);

	b2Body* leftWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 10, 100);
	leftWallBody->SetTransform(b2Vec2(0.0f, 50.0f), 0.0f);

	b2Body* rightWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 10, 100);
	rightWallBody->SetTransform(b2Vec2(100.0f, 50.0f), 0.0f);

	controlBody = Box2DHelper::CreateCircularDynamicBody(phyWorld, 5, 1.0f, 0.5, 0.1f);
	controlBody->SetTransform(b2Vec2(50.0f, 50.0f), 0.0f);
}


void Game::Loop()
{
	while (wnd->isOpen())
	{
		wnd->clear(clearColor);
		DoEvents();
		CheckCollitions();
		UpdatePhysics();
		DrawGame();
		wnd->display();
	}
}

void Game::DoEvents()
{
	Event evt;
	while (wnd->pollEvent(evt))
	{
		switch (evt.type)
		{
		case Event::Closed:
			wnd->close();
			break;
		case Event::MouseButtonPressed:
			// Crear un cuerpo dinámico triangular en la posición del ratón
			b2Body* body = Box2DHelper::CreateTriangularDynamicBody(phyWorld, b2Vec2(0.0f, 0.0f), 10.0f, 1.0f, 4.0f, 0.1f);
			// Transformar las coordenadas según la vista activa
			Vector2f pos = wnd->mapPixelToCoords(Vector2i(evt.mouseButton.x, evt.mouseButton.y));
			body->SetTransform(b2Vec2(pos.x, pos.y), 0.0f);
			break;
		}
	}

	// Controlar el movimiento del cuerpo de control con el teclado
	// Segun la numeracion usada, cuando mas cerca de cero mas 
	// lento es el desplazamiento sobre ese eje
	controlBody->SetAwake(true);
	if (Keyboard::isKeyPressed(Keyboard::Left))
		controlBody->SetLinearVelocity(b2Vec2(-30.0f, 0.0f));
	if (Keyboard::isKeyPressed(Keyboard::Right))
		controlBody->SetLinearVelocity(b2Vec2(30.0f, 0.0f));
	if (Keyboard::isKeyPressed(Keyboard::Down))
		controlBody->SetLinearVelocity(b2Vec2(0.0f, 30.0f));
	if (Keyboard::isKeyPressed(Keyboard::Up))
		controlBody->SetLinearVelocity(b2Vec2(0.0f, -30.0f));
}

void Game::CheckCollitions()
{
	// Implementación de la comprobación de colisiones
}

void Game::UpdatePhysics()
{
	phyWorld->Step(frameTime, 8, 8);
	phyWorld->ClearForces();
	phyWorld->DebugDraw();
}

void Game::DrawGame()
{
	// Dibujar el suelo
	sf::RectangleShape groundShape(sf::Vector2f(500, 5));
	groundShape.setFillColor(sf::Color::Red);
	groundShape.setPosition(0, 95);
	wnd->draw(groundShape);

	// Dibujar las paredes
	sf::RectangleShape leftWallShape(sf::Vector2f(10, alto)); // Alto de la ventana
	leftWallShape.setFillColor(sf::Color::Blue);
	leftWallShape.setPosition(100, 0); // X = 100 para que comience donde termina el suelo
	wnd->draw(leftWallShape);

	sf::RectangleShape rightWallShape(sf::Vector2f(10, alto)); // Alto de la ventana
	rightWallShape.setFillColor(sf::Color::Cyan);
	rightWallShape.setPosition(90, 0); // X = 90 para que comience donde termina el suelo
	wnd->draw(rightWallShape);

	// Dibujar el cuerpo de control (círculo)
	sf::CircleShape controlShape(5);
	controlShape.setFillColor(sf::Color::Magenta);
	controlShape.setPosition(controlBody->GetPosition().x - 5, controlBody->GetPosition().y - 5);
	wnd->draw(controlShape);
}

Game::~Game(void) {}