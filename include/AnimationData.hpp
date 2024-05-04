
namespace ani {

    struct AnimationData {

        AnimationData();
        AnimationData(int, int, float);

        int index;   // riga dello spritesheet
        int frames;  // numero di frame
        float speed; // durata in secondi di un singolo frame
    };
};