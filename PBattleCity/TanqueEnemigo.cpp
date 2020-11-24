#include "TanqueEnemigo.h"
#include "Utilitarios.h"
#include "Pared.h"

TanqueEnemigo::TanqueEnemigo()
{
	tipoActor = TipoActor_TanqueEnemigo;
	analizarTiempo = tiempoAnalisisIAEnemiga;
	analizarTemporizador = getRandomFloat(0.0, analizarTiempo);
	ultimoAnalisisX = 0.0;
	ultimoAnalisisY = 0.0;

	energia = energiaEnemigo;
	velocidad = velocidadEnemigo;

	setColor(ColorConsola_CelesteOscuro, ColorConsola_Celeste);
}

TanqueEnemigo::~TanqueEnemigo()
{
	gameManager->incrementarContadorEnemigosMuertos();
}

void TanqueEnemigo::analizar()
{
	float x = 0.0;
	float y = 0.0;
	calcularPosicionCeldaFrontal(&x, &y);

	float xDelta = 0.0;
	float yDelta = 0.0;

	switch (direccion) {
		case Direccion_Izquierda: xDelta = -1.0; break;
		case Direccion_Derecha: xDelta = 1.0; break;
		case Direccion_Arriba: yDelta = -1.0; break;
		case Direccion_Abajo: yDelta = 1.0; break;
	}

	//Encontrar actores cercanos y distancia
	Actor* actor = 0;
	int distancia = 0;

	do {
		actor = gameManager->detectarColisiones(x, y, 1, 1, 0);

		x += xDelta;
		y += yDelta;
		++distancia;
	} while (actor == 0);

	//Codigo para defenderse disparando
	//Atacar disparando

	//Cambio de direccion aleatorio
	if (0 == rand() % 5) {
		//Cambia la direccion aleatoriamente
		moverDireccionRandom();
		return;
	}

	switch (actor->getTipoActor()) {
	case TipoActor_Pared:
		if (((Pared*)actor)->getInvulnerable() == false)
		{
			//disparar();
			return;
		}
		break;
	}

	//Cambio de direccion
	if (distancia == 1 || ((int)ultimoAnalisisX == (int)getX() && (int)ultimoAnalisisY == (int)getY())) {
		//Se mueve en una direccion aleatoria
		moverDireccionRandom();
		return;
	}

	ultimoAnalisisX = getX();
	ultimoAnalisisY = getY();

}


void TanqueEnemigo::moverDireccionRandom()
{
	Direccion direccionAnterior = getDireccion();
	Direccion direccionNueva;

	do {
		direccionNueva = (Direccion)(rand() % ((int)Direccion_MAX));

	} while (direccionAnterior == direccionNueva);

	mover(direccionNueva);
}

void TanqueEnemigo::actualizar(float _dt)
{
	Tanque::actualizar(_dt);

	analizarTemporizador += _dt;
	if (analizarTemporizador >= analizarTiempo) {
		analizarTemporizador = 0;
		analizar();
	}
}