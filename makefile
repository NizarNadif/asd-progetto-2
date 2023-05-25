run: got2.cpp input.txt
	@g++ got2.cpp -std=c++11 -o got2.out
	@./got2.out

debug: got2.cpp input.txt
	@g++ got2.cpp -D DEBUG -o got2.out
	@./got2.out

see: got2.cpp input.txt
	@g++ got2.cpp -D IMG -o got2.out
	@./got2.out
	@sfdp -Tpng graph.dot -o graph.png
	@rm -f graph.dot
	@rm -f got2.out

grader: got2.cpp input.txt
	@g++ -DEVAL -std=c++11 -O2 -pipe -o got2.out got2.cpp grader.cpp
	@./got2.out

clean:
	@rm -f *.png
	@rm -f *.out
	@rm -f output.txt

input.txt:
	@echo "manca il file di input!"
	@echo "ti faccio un favore creandone uno dummy..."
	@echo "6 7 0 1 2 0 2 3 1 2 3 4 4 2 3 5" > input.txt

got2.cpp:
	@echo "per caso hai rinominato il file cpp?"