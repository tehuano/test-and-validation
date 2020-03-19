<<<<<<< HEAD
COMPILER=pdflatex
SPELLER=aspell -l es -t -c
BIBTEX=bibtex
REFERENCES=hsm_tb.bib # bibtex .bib files
MAIN_TEX=hsm_tb# hsm_tb .tex file
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
		$(COMPILER) $(MAIN_TEX).tex

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
=======
PDF_FILES = $(shell share/bin/allpdfs)
ALL_FILES = $(shell find -name '*.tex' -or -name '*.sty' -or -name '*.cls' -or -name '*.bib' -or -name '*.bst' -or -name '*.jpg' -or -name '*.png' -or -name '*.eps' | sed -e 's/ /\ /g')
MAKEFILES = $(shell share/bin/allmakefiles)

-include .configure

all: $(PDF_FILES)

clean:
	rm -rf */out .makefile

watch:
	share/bin/watch

watch-inotify:
	share/bin/watch-inotify

pull:
	git pull https://github.com/janzhou/latex-makefile

pull-develop:
	git pull https://github.com/janzhou/latex-makefile develop

multicore:
	make -j$(shell grep -c ^processor /proc/cpuinfo)

.makefile:
	mkdir -p .makefile

.makefile/%.makefile: .makefile share/makefile.sed
	sed -e "s/SED/$*/g" share/makefile.sed > $@

-include $(MAKEFILES)

echo:
	echo $(PDF_FILES)
>>>>>>> 2afefd05aa8a534e389925f4d7156bb332852ec8
