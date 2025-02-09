TARGET = bitacora

$(TARGET): 
	pdflatex -shell-escape $@.tex
	pdflatex -shell-escape $@.tex

	rm *.aux *.log *.out &
	rm -r _minted* &
