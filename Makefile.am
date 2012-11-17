#ACLOCAL_AMFLAGS = -I m4

if COND_TESTS
       MAYBE_TESTS = testing
endif
SUBDIRS = src  doc $(MAYBE_TESTS)

EXTRA_DIST = README.TXT LICENSE.TXT mingwbuild.sh Changelog.txt

dist-version:
	git log HEAD^1..HEAD |head -n3 > $@
clean-local:
	rm -rf doc/html doc/latex
