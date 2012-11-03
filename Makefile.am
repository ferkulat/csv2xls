#ACLOCAL_AMFLAGS = -I m4
SUBDIRS = src testing doc
EXTRA_DIST = README.TXT LICENSE.TXT mingwbuild.sh

dist-version:
	git log HEAD^1..HEAD |head -n3 > $@
clean-local:
	rm -rf doc/html doc/latex
