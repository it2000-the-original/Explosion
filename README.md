# Explosion
È il nome che ho voluto dare a questo semplice progetto con lo scopo di partecipazione alla sfida di programmazione di PizzaGameDev e, ho interpretato la descrizione della sfida come un esplosione dove vengono scagliati dei detriti, per fare questo, ho scelto il genere dello spaceshooter, infatti questo progetto si inspira esplicitamente ad Asteroids. Nel codice tutti i commenti sono scritti in italiano e spiegano al meglio possibile il funzionamento del mio algoritmo. Tale programma non è un gioco completo ma bensì una base che e possibile estendere per portare avanti progetti di ogni tipo, per compilarlo, è necessario usare cmake insieme alle necessarie dipendenze (sfml e box2d). I sorgenti sono sotto licenza GPL e possono essere copiati, modificati e redistribuiti a proprio piacimento. L'algoritmo per l'esplosione funziona con una classe che si occupa di gestire lo sprite che simula l'esplosione insieme a tutti gli sprite che simulano i detriti scagliati da questa.
## L'esplosione
Non è altro che un'entità che dispone di un componente che gli permette di eseguire un'animazione attraverso uno spritesheet e un componente che distrugge il resto dell'entità in seguito alla conclusione dell'animazione, una cosa veramente semplice
## I detriti
La questione dei detriti è un po più complessa, infatti i detriti sono suddivisi in vari livelli ed ogni livello, contiene detriti più leggeri dei precedenti, tali detriti sono definiti attraverso una serie di stringhe testuali che corrisponsono agli ID dei detriti corrispondenti. Il caricamento dei detriti avviene in questo modo: viene prima definito un numero di detriti da spawnare e, per ogni livello, questo numero aumenterà esponenzialmente, per esempio se vengono caricati 2 detriti del primo livello, verrano poi caricati 4 detriti del secondo livello, poi 8, poi 9 ecc.. per questo, per il caricamento di ogni detrito di un livello qualsiasi, il detrito di tale livello viene scelto in modo casuale tra quelli menzionati per il livello seguente poi, al detrito viene applicato un impulso angolare e lineare in una direzione qualsiasi e alla fine, al detrito viene aggiunto un componente di autodistruzione che lo distrugge entro 2 secondi.

Ve lo ricordo, se volete rivedere l'effetto non avete bisogno di chiudere e riaprire il programma, potete semplicemente premere il tasto "M" per caricare un nuovo asteroide in una posizione casuale. Poi i restanti comandi sono i soliti, W S D A per spostarsi e Space per sparare.

**Attenzione! Gli sprite sono gestiti attraverso git-lfs, per cui se volete clonare il repository dovrete avere git-lfs installato**

E qui alcuni screenshot:

![Screenshot from 2024-05-06 15-25-15](https://github.com/it2000-the-original/Explosion/assets/93731405/d342a5ad-8318-42c4-8546-b3a647118b36)

![Screenshot from 2024-05-06 15-26-00](https://github.com/it2000-the-original/Explosion/assets/93731405/d545bec3-f5b1-4e65-9cef-9f015438f63c)

![Screenshot from 2024-05-06 15-26-41](https://github.com/it2000-the-original/Explosion/assets/93731405/e6f0d883-a51f-4bed-a039-2952d086af48)
