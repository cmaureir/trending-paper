#NOMBRE=$(shell grep -H \\documentclass *.tex | cut -d: -f1 | cut -d. -f1)
NOMBRE=article
SHELL=/bin/bash
BIBINPUTS=./bib/
LATEX=latex

all: $(NOMBRE).tex src/*.tex
	export BIBINPUT=$(BIBINPUTS)
	@echo "   Making pdf for first time..."
	$(LATEX) -halt-on-error $(NOMBRE).tex
	@echo "   Making bibtex..."
	BIBINPUTS=$(BIBINPUTS) bibtex $(NOMBRE)
	@echo "   Re-making dvi for satisfying references..."
	$(LATEX) $(NOMBRE).tex
	$(LATEX) $(NOMBRE).tex

pdf:
	dvipdf $(NOMBRE).dvi

ps:
	dvips $(NOMBRE).dvi

clean:
	-rm -f $(NOMBRE).{aux,toc,log,tmp,dvi,idx,ilg,ind,out,bbl,blg,lol,lof,lot} .my_log include/*.aux

distclean: clean
	-rm -f $(NOMBRE).pdf

x: $(NOMBRE).pdf
	-xpdf $(NOMBRE).pdf

e: $(NOMBRE).pdf
	-evince $(NOMBRE).pdf &


.PHONY: all clean distclean images ps pdf
