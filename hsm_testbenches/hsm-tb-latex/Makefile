COMPILER=pdflatex
SPELLER=aspell -l es -t -c
BIBTEX=bibtex
REFERENCES=bibliography.bib
MAIN_TEX=hsm_tb
BIB_AUX=hsm_tb.aux # .aux files
WC=texcount
# get just the text word count (no headings, citations, etc)
WC_AFTER=| grep text | head -1 | cut -d ' ' -f 4 
# file to store word count
WC_FILE=wordcount

all: 
		make bibtex
		make $(WC_FILE)
		make compile
		$(SPELLER) $(MAIN_TEX).tex

compile: $(MAIN_TEX).tex
		$(COMPILER) --shell-escape $(MAIN_TEX).tex

printwordcount:
		@make $(WC_FILE)
		cat $(WC_FILE)

$(WC_FILE): $(MAIN_TEX).tex
		@$(WC) $(MAIN_TEX).tex $(WC_AFTER) > $(WC_FILE)

bibtex: $(REFRENCES)
		make compile
		$(BIBTEX) $(BIB_AUX)
		make compile

clean:
	rm -rf *.aux *.lof *.log *.lot *.toc *.bbl *.blg *pdf

view:
	xdg-open $(MAIN_TEX).pdf
