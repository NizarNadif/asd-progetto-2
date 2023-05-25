# Progetto di algoritmi e strutture dati: seconda unità

In questo repository è presente il setup di un ambiente utile alla risoluzione del secondo progetto di [ASD](https://judge.science.unitn.it/slides/asd22/prog2.pdf).

## Codice
All'interno del file ```got2.cpp``` è stato scritto un primo setup del progetto, esso salva il grafo all'interno di una matrice e stampa una soluzione dummy (coppia di liste di archi, coppie di interi).

All'interno della funzione ```sol``` dovremmo implementare la nostra soluzione.

> _**Nota :**_ gli ```ifdef``` e ```endif``` in giro per il codice servono per poter implementare le funzionalità di alcuni dei comandi descritti nelle sezioni successive, in caso di modifiche sarebbe ottimo poter mantenere almeno la ```make see```, in quanto risulta molto utile per la comprensione delle nostre soluzioni.

## Comandi
Grazie ad un makefile è possibile eseguire diversi comandi, quali:
- ```make run``` esegue normalmente il programma;
- ```make grader``` esegue il programma facendo uso del ```grader```, supporto fornito per limitare il tempo di esecuzione dei nostri SWs;
- ```make clean``` rimuove i file non essenziali;
- ```make debug``` esegue il programma e stampa a console una piccola rappresentazione del grafo di partenza;
- ```make see``` esegue il programma e rappresenta graficamente il grafo (```graph.png```), evidenziando gli archi aggiunti e rimossi.

Il file ```input.txt``` è un prerequisito di quasi tutti i comandi, l'unico escluso è il ```make clean```.
> È presente una procedura che ne crea uno con i dati nel primo esempio, essa viene eseguita automaticamente quando il file è assente

### Visualizzazione grafica con ```make see```
#### Requisiti di sistema
Affinché questo comando possa essere eseguito è necessario aver previamente installato [Graphviz](https://graphviz.org/download/), la procedura non è tortuosa e dovrebbe andare a buon fine nei sistemi Unix - _non è stata testata su Windows_.
> per verificare che sia andata a buon fine potete eseguire ```sfdp --version``` o ```dot --version```, il primo è il comando da noi utilizzato.
#### Requisiti del codice
Come anticipato precedentemente, sarebbe ottimo poter mantenere le funzionalità del comando, questo necessità che:
1. _venga stampato l'header_: senza non sarebbe possibile creare l'immagine;
2. _vengano dichiarati i nodi_: senza questa procedura apparirebbero solo i nodi aventi almeno un arco ad essi associato;
> toglierli potrebbe anche rendere più facile la lettura del grafo, i nodi "solitari" non necessitano alcun tipo di trattamento, quindi potrebbero essere ignorati
3.  _vengano definiti gli archi iniziali_;
4. _vengano dichiarati gli archi da aggiungere e modificati quelli da rimuovere_.
5. _venga chiuso il grafo_.

## Prestazioni
Una critica movibile verso un setup simile riguarderebbe, molto probabilmente, l'aspetto delle prestazioni: state tranquilli, fino a quando non viene eseguito un comando di "debug", come il ```debug``` stesso o la ```see```, gli unici overhead presenti sono solo i controlli delle macro (le ```ifdef```); negli altri casi l'overhead è ignorabile, in quanto i comandi di debug non verranno mai eseguiti dal correttore online  e noi meri mortali possiamo aspettare un nonnulla in più.

## Riferimenti utili
- [Statement del progetto](testo.pdf)
- [Piattaforma](https://judge.science.unitn.it/arena/tasks/got2/submissions)
- [Ranking](https://judge.science.unitn.it/arena/ranking)