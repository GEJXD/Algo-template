template.pdf: template.tex main
	./main
	xelatex template.tex
	xelatex template.tex

template.tex: main

main: main.cpp
	cc main.cpp -o main

clean:
	rm template.* main
