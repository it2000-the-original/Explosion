// Gestisce le operazioni da svolgere in seguito
// alla collisione tra due fixture (Corpi)

class Listener : public b2ContactListener {

    void BeginContact(b2Contact*);
};