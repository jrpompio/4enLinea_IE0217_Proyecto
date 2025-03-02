TARGET = bitacora

$(TARGET): 
	pdflatex -shell-escape $@.tex
#	pdflatex -shell-escape $@.tex
# la doble compilacion es necesaria para cuando se va a citar
	rm *.aux *.log *.out &
	rm -r _minted* &
