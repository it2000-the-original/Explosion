
class Background {

private:

    Element* background;

    b2BodyDef backDef;

public:

    Background(std::string _background) {

        background = Engine::elements[_background];
        backDef.type = b2_kinematicBody;
    }

    void drawBackground() {

        int width =  background->width  * background->scale;
        int height = background->height * background->scale;
        int xrepeat = WW / width + 1;
        int yrepeat = WH / height + 1;

        for (int i = 0; i < yrepeat; i++) {

            drawLine(height / WS * (i + 0.5f), xrepeat, width);
        }
    }

    void drawLine(float ypos, int xrepeat, int width) {

        for (int i = 0; i < xrepeat; i++) {

            b2Vec2 pos = b2Vec2(width / WS * (i + 0.5f), ypos);
            auto& panel = Engine::manager.addEntity();
            panel.addComponent<Body>(backDef);
            panel.addComponent<Sprite>(background);
            panel.getComponent<Body>().body->SetTransform(pos, 0);
            Engine::manager.addToGrop(&panel, Gbackground);
        }
    }
};