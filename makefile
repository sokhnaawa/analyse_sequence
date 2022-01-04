CC=gcc
CFLAGS=-Wall

build_all: transcription recherche translation scoresemilaire calculescore

test:
	 ./transcription

transcription: module_transcription.o
	$(CC)  module_transcription.o -o transcription

recherche: recherche_sequence.o
	$(CC)  recherche_sequence.o -o recherche

translation: translation.o
	$(CC)  translation.o -o translation

scoresemilaire: score_semilaire.o
	$(CC)  score_semilaire.o -o scoresemilaire

calculescore: calcule_score.o
	$(CC)  calcule_score.o -o calculescore

module_transcription.o: module_transcription/module_transcription.c  module_transcription/module_transcription.h
	gcc $(CFLAGS) -c module_transcription/module_transcription.c module_transcription/module_transcription.h

recherche_sequence.o: recherche_sequence/recherche_sequence.c  recherche_sequence/recherche_sequence.h
	gcc $(CFLAGS) -c recherche_sequence/recherche_sequence.c recherche_sequence/recherche_sequence.h

translation.o: traduction/translation.c  traduction/translation.h traduction/proteins.h
	gcc $(CFLAGS) -c traduction/translation.c traduction/translation.h

score_semilaire.o: score_semilaire/score_semilaire.c  score_semilaire/score_semilaire.h
	gcc $(CFLAGS) -c score_semilaire/score_semilaire.c score_semilaire/score_semilaire.h

calcule_score.o: calcule_score/calcule_score.c
	gcc $(CFLAGS) -c calcule_score/calcule_score.c

clean:
	rm -f *.o

mrproper: clean
	rm -f module_transciption transcription score_s recherche calculescore scoresemilaire