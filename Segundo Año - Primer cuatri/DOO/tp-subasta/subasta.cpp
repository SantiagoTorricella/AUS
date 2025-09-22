/*
Todo lo llamo desde subasta
                                     Monto       Ofertante                  
                                       ▲             ▲                      
                                       │             │                      
                           [items]     │             │                      
                             │         │             │                      
                             │         └──────┬──────┘                      
                             │                │                             
┌──────────────┐             ▼                │                             
│              │      ┌─────────────┐         │                             
│   Subasta    ├─────►│    LOTES    ◄──────┐  │                             
│              │      └──────┬──────┘      │  │                             
└──────────────┘             │             │  │                             
                             │             │  │                             
                             │             │Oferta => La mas elevada        
                             │             │          se registra en el lote
                       ┌─────┼─────┐       │                                
                       ▼     │     ▼       │                                
                    Nombre   │  Numero     │                                
                             │       ┌───────────┐                          
                             ▼       │  Persona  │                          
                        Guarda la    └─────┬─────┘                          
                        oferta mas         │                                
                          grande           │                                
                                           ▼                                
                                        Nombre                              
*/

#include <iostream>
#include <vector>
#include <string>
#include <limits>

class Persona
{

  private:
    std::string nombre;


  public:
    Persona(std::string nombre)
    {
      this->nombre = nombre;
    }

  std::string getNombre()
  {
  return nombre;
  };



};

class Oferta
{

  private:
    int monto;
    Persona* ofertante;

  public:
    Oferta(int monto, Persona* ofertante)
    {
      this->monto = monto;
      this->ofertante = ofertante;
    }

    int getMonto()
    {
      return monto;
    };

    Persona* getOfertante()
    {
      return ofertante;
    };

};

class Lote
{

  private:
    int numero;                     
    std::string nombre;
    Oferta* ofertaMasAlta = nullptr;

  public:
    Lote(int numero, std::string nombre)
    {
      this->numero = numero;
      this->nombre = nombre;
    }

  int getNumero()
  {
    return numero;
  }

  std::string getNombre()
  {
    return nombre;
  }

  Oferta* getOfertaMasAlta()
  {
    return ofertaMasAlta;
  }

  void recibirOferta(Oferta* oferta)
  {
    if(ofertaMasAlta == nullptr  || oferta->getMonto() > ofertaMasAlta->getMonto()) 
    {
    delete ofertaMasAlta;  // borro la oferta anterior pq ya no me sirve dado que hay otra mas alta
    ofertaMasAlta = oferta;
    }
    else delete oferta; // deleteo la oferta nueva, pq no me va a servir para nada en el futuro
  }

};

class Subasta 
{

  private:
    std::vector<Lote *> lotes;
    std::vector<Persona *>personas;

  public:
    Subasta() = default;

    void agregarLote(Lote* lote)
    {
      lotes.push_back(lote);
    }

    void agregarPersona(Persona* persona)
    {
      personas.push_back(persona);
    }

     std::vector<Lote *> getLotes()
    {
      return lotes;
    }

    std::vector<Persona *> getPersonas()
    {
      return personas;
    }

  // destructor --> Elimino los lotes y personas que creamos dinamicamente
   ~Subasta() 
    {

        for (Lote* lote : lotes) 
        {
            delete lote;
        }

        for(Persona* persona : personas)
        {
          delete persona;
        }

    }
};

int main() {
    Subasta subasta;
    int opcion;

    do {
        std::cout << "\n=== MENU DE SUBASTA ===\n";
        std::cout << "1. Agregar persona\n";
        std::cout << "2. Agregar lote\n";
        std::cout << "3. Realizar oferta\n";
        std::cout << "4. Ver mejores ofertas\n";
        std::cout << "5. Ver todos los lotes\n";
        std::cout << "6. Ver todas las personas\n";
        std::cout << "7. Salir\n\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
        case 1: {
            std::string nombre;
            std::cout << "Ingrese nombre de la persona: ";
            std::cin.ignore();
            std::getline(std::cin, nombre);
            subasta.agregarPersona(new Persona(nombre));
            std::cout << "Persona agregada con ID: " << subasta.getPersonas().size() - 1 << "\n";
            break;
        }

        case 2: {
            int numero;
            std::string nombreLote;

            std::cout << "Ingrese numero de lote: ";
            
            while (!(std::cin >> numero)) {
                std::cout << "Entrada invalida. Ingrese un numero entero: ";
                std::cin.clear(); // limpio el error
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // aca limpio el buffer por el /n del input numerico
            }

            std::cout << "Ingrese nombre del lote: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // aca hago lo mismo que en la validacion de arriba
            std::getline(std::cin, nombreLote);

            subasta.agregarLote(new Lote(numero, nombreLote));
            std::cout << "Lote agregado.\n";
            break;
            }

        case 3: {
            if (subasta.getPersonas().empty() || subasta.getLotes().empty()) {
                std::cout << "Debe haber al menos una persona y un lote para ofertar.\n";
                break;
            }

            std::cout << "\nPersonas disponibles:\n";
            for (size_t i = 0; i < subasta.getPersonas().size(); ++i) {
                std::cout << i << ") " << subasta.getPersonas()[i]->getNombre() << "\n";
            }

            int personaIndex;
            std::cout << "Seleccione el indice de la persona: ";
            std::cin >> personaIndex;

            std::cout << "\nLotes disponibles:\n";
            for (size_t i = 0; i < subasta.getLotes().size(); ++i) {
                std::cout << i << ") " << subasta.getLotes()[i]->getNombre() 
                          << " (ID: " << subasta.getLotes()[i]->getNumero() << ")\n";
            }

            int loteIndex;
            std::cout << "Seleccione el indice del lote: ";
            std::cin >> loteIndex;

            int monto;
            std::cout << "Ingrese monto de la oferta: ";
            std::cin >> monto;

            Oferta* nueva = new Oferta(monto, subasta.getPersonas()[personaIndex]);
            subasta.getLotes()[loteIndex]->recibirOferta(nueva);

            std::cout << "Oferta registrada.\n";
            break;
        }

        case 4: {
            if (subasta.getLotes().empty()) {
                std::cout << "No hay lotes registrados.\n";
                break;
            }

            std::cout << "\n=== MEJORES OFERTAS POR LOTE ===\n";
            for (Lote* lote : subasta.getLotes()) {
                std::cout << "Lote: " << lote->getNombre() << " (ID: " << lote->getNumero() << ")\n";
                Oferta* oferta = lote->getOfertaMasAlta();
                if (oferta)
                    std::cout << "  Mejor oferta: $" << oferta->getMonto() 
                              << " por " << oferta->getOfertante()->getNombre() << "\n";
                else
                    std::cout << "  Aun no hay ofertas.\n";
            }
            break;
        }

        case 5:
         {
            if (subasta.getLotes().empty()) {
                std::cout << "No hay lotes registrados.\n";
            } else {
                std::cout << "\n=== LOTES REGISTRADOS ===\n";
                for (size_t i = 0; i < subasta.getLotes().size(); ++i) {
                    std::cout << i << ") " << subasta.getLotes()[i]->getNombre()
                              << " (ID: " << subasta.getLotes()[i]->getNumero() << ")\n";
                }
            }
            break;
        }
            

            case 6: {
            if (subasta.getPersonas().empty()) { 
                std::cout << "No hay personas registradas.\n";
            } else {
                std::cout << "\n=== PERSONAS REGISTRADAS ===\n";
                for (size_t i = 0; i < subasta.getPersonas().size(); ++i) {
                    std::cout << i << ") " << subasta.getPersonas()[i]->getNombre() << "\n";
                }
            }
            break;
        }

        case 7: 
            std::cout << "Saliendo del programa...\n";
            opcion = 7; 
            break;
       

        default:
            std::cout << "Opcion invalida.\n";
        }


    } while (opcion != 7);

    return 0;
}