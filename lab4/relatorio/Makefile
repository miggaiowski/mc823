all: pdf

latex:
	latex -interaction=nonstopmode relatorio.tex
	bibtex relatorio
	latex -interaction=nonstopmode relatorio.tex
	latex -interaction=nonstopmode relatorio.tex
	pdffonts relatorio.pdf

pdf:
	pdflatex -interaction=nonstopmode relatorio.tex
	bibtex relatorio
	pdflatex -interaction=nonstopmode relatorio.tex
	pdflatex -interaction=nonstopmode relatorio.tex

ps:
	dvips relatorio.dvi

rtf: latex
	latex2rtf -a relatorio.aux -b bibliography.bib -i brazil -o relatorio.rtf relatorio.tex

html: latex
	latex2html -html_version 4.0,latin1,unicode relatorio.tex

cleanall: clean
	rm -f *.toc *.lof *.blg *.bbl
	[ -d relatorio/ ] && rm -rf relatorio/ || exit 0

clean:
	rm -f *.log *.aux *.dvi *bbl relatorio.pdf *.ps relatorio.rtf

