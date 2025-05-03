#include "Game.h"
#include "Box2DHelper.h"
#include <iostream>


Game::Game(int ancho, int alto, std::string titulo) :
	cannon(sf::Vector2f(10, 90)),
	m_mousePos(0, 0)
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

	float wndWidth = wnd->getView().getSize().x;

	b2Body* groundBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, wndWidth, 10);
	groundBody->SetTransform(b2Vec2(wndWidth / 2, 100.0f), 0.0f);

	b2Body* ceilingVody = Box2DHelper::CreateRectangularStaticBody(phyWorld, wndWidth, 10);
	ceilingVody->SetTransform(b2Vec2(wndWidth / 2, 0.0f), 0.0f);

	b2Body* leftWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 10, 100);
	leftWallBody->SetTransform(b2Vec2(0.0f, 50.0f), 0.0f);

	b2Body* rightWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 10, 100);
	rightWallBody->SetTransform(b2Vec2(wndWidth, 50.0f), 0.0f);


	b2Body* staticObstacle1 = Box2DHelper::CreateRectangularStaticBody(phyWorld, 20, 10);
	staticObstacle1->SetTransform(b2Vec2(wndWidth / 2, 50.0f), 0.0f);

	b2Body* staticObstacle2 = Box2DHelper::CreateRectangularStaticBody(phyWorld, 20, 10);
	staticObstacle2->SetTransform(b2Vec2((wndWidth / 4) * 3, 40.0f), 0.0f);

	b2Body* staticObstacle3 = Box2DHelper::CreateRectangularStaticBody(phyWorld, 20, 20);
	staticObstacle3->SetTransform(b2Vec2((wndWidth / 5) * 4, 70.0f), 0.0f);


	b2Body* dynamicObstacle1 = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 5, 15, 1.0f, 1.0f, 1.0f);
	dynamicObstacle1->SetTransform(b2Vec2((wndWidth / 4) * 3, 30.0f), 0.0f);

	b2Body* dynamicObstacle2 = Box2DHelper::CreateCircularDynamicBody(phyWorld, 2.5f, 1.0f, 1.0f, 1.0f);
	dynamicObstacle2->SetTransform(b2Vec2((wndWidth / 4) * 3, 20.0f), 0.0f);

	b2Body* dynamicObstacle3 =  Box2DHelper::CreateCircularDynamicBody(phyWorld, 5, 1.0f, 1.0f, 1.0f);
	dynamicObstacle3->SetTransform(b2Vec2(wndWidth / 2, 45.0f), 0.0f);
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
	Vector2f position = wnd->mapPixelToCoords(sf::Mouse::getPosition(*wnd));
	m_mousePos.x = position.x;
	m_mousePos.y = position.y;
	Event evt;
	while (wnd->pollEvent(evt))
	{
		switch (evt.type)
		{
		case Event::Closed:
			wnd->close();
			break;
		case Event::MouseButtonPressed:
			b2Vec2 direction = m_mousePos - cannon.GetPosition();
			if (direction.x < 0) direction.x = 0;
			if (direction.y > 0) direction.y = 0;
			//float strength = direction.Length();
			RagDoll* ragdoll = new RagDoll(phyWorld, cannon.GetProjectileExitPosition(), 1);
			ragdoll->ApplyForce(direction);
			ragdolls.push_back(ragdoll);

			break;
		}
	}
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
	cannon.Update(m_mousePos);
}

void Game::DrawGame()
{
	/*
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
	*/
	cannon.Draw(wnd);
}

Game::~Game(void) {}