#include "Municion.h"
#include "Nivel.h"

Municion::Municion() {
	setTipoActor(TipoActor_Municion);
	tipoActorPropietario = TipoActor_None;
	setDireccion(Direccion_MAX);
	velocidad = velocidadMunicion;
	//setImagenMunicion(imagenMunicion, ColorConsola_Gris, ColorConsola_Negro);
}

void Municion::setImagenMunicion(unsigned char _simbolo, ColorConsola _colorImagen, ColorConsola _colorFondo) {
	DatosSimboloConsola imagenMunicion;
	imagenMunicion.simbolo = _simbolo;
	imagenMunicion.colorSimbolo = _colorImagen;
	imagenMunicion.colorFondo = _colorFondo;

	vector<DatosSimboloConsola> mid;
	//pair<int, DatosSimboloConsola> pid;

	//pid.first = 1;
	//pid.second = imagenMunicion;

	//mid.insert(imagenMunicion);

	pair<Direccion, vector<DatosSimboloConsola>> pAvatar;
	pAvatar.first = Direccion_MAX;
	pAvatar.second = mid;

	//getAvatar().insert(pAvatar);
}

void Municion::renderizar(SistemaRenderizacion* _sistemaRenderizacion)
{
	Actor::renderizar(_sistemaRenderizacion);
}

void Municion::actualizar(float _dt) {
	Actor::actualizar(_dt);
}

void Municion::intersectar(Actor* _actor) {
	//Destruirse a si mismo
	setEnergia(0);

	//Da�ar el objetivo
	_actor->hacerDano(1);
	if (_actor->getTipoActor() == TipoActor_TanqueEnemigo && _actor->getEnergia() <= 0) {
		getGameManager()->incrementarContadorEnemigosMuertos();
	//	gameManager->agregarEnemigoMuerto(DatosEnemigosMuertos{ _actor->getNumeroActor(), _actor->getTipoActor(), _actor->getX(), _actor->getY() });
	}
}